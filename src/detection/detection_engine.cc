//--------------------------------------------------------------------------
// Copyright (C) 2016-2018 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

// detection_engine.h author Russ Combs <rucombs@cisco.com>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "detection_engine.h"

#include "actions/act_replace.h"
#include "events/sfeventq.h"
#include "filters/sfthreshold.h"
#include "framework/endianness.h"
#include "helpers/ring.h"
#include "latency/packet_latency.h"
#include "main/modules.h"
#include "main/snort.h"
#include "main/snort_config.h"
#include "main/snort_debug.h"
#include "main/thread.h"
#include "managers/inspector_manager.h"
#include "packet_io/active.h"
#include "parser/parser.h"
#include "profiler/profiler_defs.h"
#include "protocols/packet.h"
#include "stream/stream.h"
#include "utils/stats.h"

#include "context_switcher.h"
#include "detection_util.h"
#include "detect.h"
#include "detect_trace.h"
#include "fp_config.h"
#include "fp_detect.h"
#include "ips_context.h"
#include "ips_context_data.h"
#include "regex_offload.h"

static THREAD_LOCAL RegexOffload* offloader = nullptr;

using namespace snort;

//--------------------------------------------------------------------------
// basic de
//--------------------------------------------------------------------------

void DetectionEngine::thread_init()
{ offloader = new RegexOffload(SnortConfig::get_conf()->offload_threads); }

void DetectionEngine::thread_term()
{ delete offloader; }

DetectionEngine::DetectionEngine()
{
    context = Snort::get_switcher()->interrupt();
    context->file_data = { nullptr, 0 };
    reset();
}

DetectionEngine::~DetectionEngine()
{
    if ( context == Snort::get_switcher()->get_context() )
    {
        // finish_packet is called here so that we clear wire packets at the right time
        finish_packet(context->packet, true);
    }
}

void DetectionEngine::reset()
{
    IpsContext* c = Snort::get_switcher()->get_context();
    c->alt_data.len = 0;  // FIXIT-H need context::reset()
}

IpsContext* DetectionEngine::get_context()
{ return Snort::get_switcher()->get_context(); }

SF_EVENTQ* DetectionEngine::get_event_queue()
{ return Snort::get_switcher()->get_context()->equeue; }

Packet* DetectionEngine::get_current_packet()
{ return Snort::get_switcher()->get_context()->packet; }

void DetectionEngine::set_encode_packet(Packet* p)
{ Snort::get_switcher()->get_context()->encode_packet = p; }

Packet* DetectionEngine::get_encode_packet()
{ return Snort::get_switcher()->get_context()->encode_packet; }

// we need to stay in the current context until rebuild is successful
// any events while rebuilding will be logged against the current packet
// however, rebuild is always in the next context, not current.
Packet* DetectionEngine::set_next_packet(Packet* parent)
{
    static THREAD_LOCAL Active shutdown_active;
    static THREAD_LOCAL IpsAction* shutdown_action = nullptr;

    wait_for_context();
    IpsContext* c = Snort::get_switcher()->get_next();
    if ( parent ) // FIXIT-L parent can probably be determined by busy queue
    {
        c->snapshot_flow(parent->flow);
        c->packet_number = parent->context->packet_number;
    }
    else
        c->packet_number = get_packet_number();

    Packet* p = c->packet;

    p->pkth = c->pkth;
    p->data = c->buf;
    p->pkt = c->buf;

    // normal rebuild
    if ( parent )
    {
        p->active = parent->active;
        p->action = parent->action;
    }
    
    // processing but parent is already gone (flow cache flush etc..)
    else if ( Snort::get_switcher()->get_context() )
    {
        p->active = get_current_packet()->active;
        p->action = get_current_packet()->action;
    }
    
    // shutdown, so use a dummy so null checking is not needed everywhere
    else
    {
        p->action = &shutdown_action;
        p->active = &shutdown_active;
        shutdown_active.reset();
    }

    p->reset();
    return p;
}

void DetectionEngine::finish_inspect_with_latency(Packet* p)
{
    DetectionEngine::set_check_tags();

    // By checking tagging here, we make sure that we log the
    // tagged packet whether it generates an alert or not.

    if ( p->has_ip() )
        check_tags(p);

    InspectorManager::probe(p);
}

void DetectionEngine::finish_inspect(Packet* p, bool inspected)
{
    log_events(p);

    if ( p->active )
        p->active->apply_delayed_action(p);

    p->context->post_detection();

    // clear closed sessions here after inspection since non-stream
    // inspectors may depend on flow information
    // this also handles block pending state
    Stream::check_flow_closed(p);

    if ( inspected and !p->context->next() ) 
        InspectorManager::clear(p);

    clear_events(p);
}

void DetectionEngine::finish_packet(Packet* p, bool flow_deletion)
{
    ContextSwitcher* sw = Snort::get_switcher();

    log_events(p);
    clear_events(p);
    p->release_helpers();

    // clean up any failed rebuilds
    if ( sw->idle_count() )
    {
        const IpsContext* c = sw->get_next();
        c->packet->release_helpers();
    }

    if ( flow_deletion or p->is_rebuilt() )
        sw->complete();

    // FIXIT-H enable for daqng
#if 0
    if ( !p->is_rebuilt() )
    {
        sw->stop();
        queue for daq msg finalize
    }
#endif
}

uint8_t* DetectionEngine::get_buffer(unsigned& max)
{
    max = IpsContext::buf_size;
    return Snort::get_switcher()->get_context()->buf;
}

uint8_t* DetectionEngine::get_next_buffer(unsigned& max)
{
    max = IpsContext::buf_size;
    return Snort::get_switcher()->get_next()->buf;
}

DataBuffer& DetectionEngine::get_alt_buffer(Packet* p)
{
    assert(p);
    return p->context->alt_data;
}

void DetectionEngine::set_file_data(const DataPointer& dp)
{ Snort::get_switcher()->get_context()->file_data = dp; }

DataPointer& DetectionEngine::get_file_data(IpsContext* c)
{ return c->file_data; }

void DetectionEngine::set_data(unsigned id, IpsContextData* p)
{ Snort::get_switcher()->get_context()->set_context_data(id, p); }

IpsContextData* DetectionEngine::get_data(unsigned id)
{ return Snort::get_switcher()->get_context()->get_context_data(id); }

IpsContextData* DetectionEngine::get_data(unsigned id, IpsContext* context)
{
    if ( context )
        return context->get_context_data(id);

    ContextSwitcher* sw = Snort::get_switcher();

    if ( !sw )
        return nullptr;

    return sw->get_context()->get_context_data(id);
}

void DetectionEngine::add_replacement(const std::string& s, unsigned off)
{ 
    Replacement r;

    r.data = s;
    r.offset = off;
    Snort::get_switcher()->get_context()->rpl.emplace_back(r); 
}

bool DetectionEngine::get_replacement(std::string& s, unsigned& off)
{ 
    if ( Snort::get_switcher()->get_context()->rpl.empty() )
        return false;

    auto rep = Snort::get_switcher()->get_context()->rpl.back();

    s = rep.data;
    off = rep.offset;

    Snort::get_switcher()->get_context()->rpl.pop_back();
    return true;
}

void DetectionEngine::clear_replacement()
{
    Snort::get_switcher()->get_context()->rpl.clear();
}

void DetectionEngine::disable_all(Packet* p)
{ p->context->active_rules = IpsContext::NONE; }

bool DetectionEngine::all_disabled(Packet* p)
{ return p->context->active_rules == IpsContext::NONE; }

void DetectionEngine::disable_content(Packet* p)
{
    if ( p->context->active_rules == IpsContext::CONTENT )
        p->context->active_rules = IpsContext::NON_CONTENT;

    trace_logf(detection, TRACE_PKT_DETECTION,
        "Disabled content detect, packet %" PRIu64"\n", p->context->packet_number);
}

void DetectionEngine::enable_content(Packet* p)
{ p->context->active_rules = IpsContext::CONTENT; }

bool DetectionEngine::content_enabled(Packet* p)
{ return p->context->active_rules == IpsContext::CONTENT; }

IpsContext::ActiveRules DetectionEngine::get_detects(Packet* p)
{ return p->context->active_rules; }

void DetectionEngine::set_detects(Packet* p, IpsContext::ActiveRules ar)
{ p->context->active_rules = ar; }

void DetectionEngine::set_check_tags(bool enable)
{ Snort::get_switcher()->get_context()->check_tags = enable; }

bool DetectionEngine::get_check_tags()
{ return Snort::get_switcher()->get_context()->check_tags; }

//--------------------------------------------------------------------------
// offload / onload
//--------------------------------------------------------------------------

void DetectionEngine::do_offload(Packet* p)
{
    ContextSwitcher* sw = Snort::get_switcher();

    assert(p == p->context->packet);
    assert(p->context == sw->get_context());

    trace_logf(detection, TRACE_DETECTION_ENGINE, "%" PRIu64 " de::offload %" PRIu64 " (r=%d)\n",
        p->context->packet_number, p->context->context_num, offloader->count());

    sw->suspend();

    p->context->conf = SnortConfig::get_conf();
    p->set_offloaded();

    offloader->put(p);
    pc.offloads++;
}

bool DetectionEngine::offload(Packet* p)
{
    ContextSwitcher* sw = Snort::get_switcher();

    bool depends_on_suspended = p->flow ? p->flow->context_chain.front() : sw->non_flow_chain.front();
    bool can_offload = offloader->available();
    bool should_offload = p->dsize >= SnortConfig::get_conf()->offload_limit;

    if ( can_offload and should_offload )
    {
        do_offload(p);
        return true;
    }

    if ( depends_on_suspended )
    {
        fp_partial(p);
        sw->suspend();
        return true;
    }

    assert(p->flow ? !p->flow->is_suspended() : true);
    fp_full(p);
    return false;
}

void DetectionEngine::idle()
{
    if (offloader)
    {
        while ( offloader->count() )
        {
            trace_logf(detection,
                TRACE_DETECTION_ENGINE,  "(wire) %" PRIu64 " de::sleep\n", get_packet_number());

            const struct timespec blip = { 0, 1 };
            nanosleep(&blip, nullptr);
            onload();
        }
        trace_logf(detection,  TRACE_DETECTION_ENGINE, "(wire) %" PRIu64 " de::idle (r=%d)\n",
            get_packet_number(), offloader->count());

        offloader->stop();
    }
}

void DetectionEngine::onload(Flow* flow)
{
    while ( flow->is_suspended() )
    {
        trace_logf(detection,
            TRACE_DETECTION_ENGINE, "(wire) %" PRIu64 " de::sleep\n", get_packet_number());

        resume_ready_suspends(flow->context_chain); // FIXIT-M makes onload reentrant-safe
        onload();
    }
    assert(!offloader->on_hold(flow));
}

void DetectionEngine::onload()
{
    for( Packet* p; offloader->count() and offloader->get(p); )
    {
        trace_logf(detection, TRACE_DETECTION_ENGINE, "%" PRIu64 " de::onload %" PRIu64 " (r=%d)\n",
            p->context->packet_number, p->context->context_num, offloader->count());
        
        p->clear_offloaded();
        
        IpsContextChain& chain = p->flow ? p->flow->context_chain : Snort::get_switcher()->non_flow_chain;
        
        resume_ready_suspends(chain);
    }
}

void DetectionEngine::resume_ready_suspends(IpsContextChain& chain)
{
    while ( chain.front() and !chain.front()->packet->is_offloaded() )
        resume(chain.front()->packet);
}

void DetectionEngine::resume(Packet* p)
{
    trace_logf(detection, TRACE_DETECTION_ENGINE, "%" PRIu64 " de::resume %" PRIu64 " (r=%d)\n",
        p->context->packet_number, p->context->context_num, offloader->count());

    Snort::get_switcher()->resume(p->context);
    
    fp_complete(p);
    finish_inspect_with_latency(p); // FIXIT-L should latency be evaluated here?
    finish_inspect(p, true);
    finish_packet(p);
}

void DetectionEngine::wait_for_context()
{
    ContextSwitcher* sw = Snort::get_switcher();

    if ( !sw->idle_count() )
    {
        pc.context_stalls++;
        do
        {
            onload();
        } while ( !sw->idle_count() );
    }
}

//--------------------------------------------------------------------------
// detection / inspection
//--------------------------------------------------------------------------

bool DetectionEngine::detect(Packet* p, bool offload_ok)
{
    assert(p);
    Profile profile(detectPerfStats);

    if ( !p->ptrs.ip_api.is_valid() )
        return false;

    if ( p->packet_flags & PKT_PASS_RULE )
        return false;

    if ( PacketLatency::fastpath() )
        return false;

    // FIXIT-M restrict detect to current ip layer
    // Currently, if a rule is found on any IP layer, we perform the detect routine
    // on the entire packet. Instead, we should only perform detect on that layer!!
    switch ( p->type() )
    {
    case PktType::PDU:
    case PktType::IP:
    case PktType::TCP:
    case PktType::UDP:
    case PktType::ICMP:
    case PktType::FILE:
        if ( offload_ok and p->flow )
            return offload(p);

        fp_full(p);
        break;

    default:
        break;
    }
    return false;
}

bool DetectionEngine::inspect(Packet* p)
{
    bool inspected = false;
    {
        PacketLatency::Context pkt_latency_ctx { p };

        if ( p->ptrs.decode_flags & DECODE_ERR_FLAGS )
        {
            if ( SnortConfig::inline_mode() and
                SnortConfig::checksum_drop(p->ptrs.decode_flags & DECODE_ERR_CKSUM_ALL) )
            {
                p->active->drop_packet(p);
            }
        }
        else
        {
            enable_content(p);
            p->alt_dsize = 0;  // FIXIT-H should be redundant

            InspectorManager::execute(p);
            inspected = true;

            if ( !all_disabled(p) )
            {
                if ( detect(p, true) )
                    return false; // don't finish out offloaded packets
            }
        }
        finish_inspect_with_latency(p);
    }
    finish_inspect(p, inspected);
    return true;
}

//--------------------------------------------------------------------------
// events
//--------------------------------------------------------------------------

// Return 0 if no OTN since -1 return indicates queue limit reached.
// See fpFinalSelectEvent()
int DetectionEngine::queue_event(const OptTreeNode* otn)
{
    RuleTreeNode* rtn = getRtnFromOtn(otn);

    if ( !rtn )
    {
        // If the rule isn't in the current policy,
        // don't add it to the event queue.
        return 0;
    }

    SF_EVENTQ* pq = get_event_queue();
    EventNode* en = (EventNode*)sfeventq_event_alloc(pq);

    if ( !en )
        return -1;

    en->otn = otn;
    en->rtn = rtn;

    if ( sfeventq_add(pq, en) )
        return -1;

    return 0;
}

int DetectionEngine::queue_event(unsigned gid, unsigned sid, Actions::Type type)
{
    OptTreeNode* otn = GetOTN(gid, sid);

    if ( !otn )
        return 0;

    SF_EVENTQ* pq = get_event_queue();
    EventNode* en = (EventNode*)sfeventq_event_alloc(pq);

    if ( !en )
        return -1;

    en->otn = otn;
    en->rtn = nullptr;  // lookup later after ips policy selection
    en->type = type;

    if ( sfeventq_add(pq, en) )
        return -1;

    return 0;
}

static int log_events(void* event, void* user)
{
    if ( !event || !user )
        return 0;

    EventNode* en = (EventNode*)event;

    if ( !en->rtn )
    {
        en->rtn = getRtnFromOtn(en->otn);

        if ( !en->rtn )
            return 0;  // not enabled
    }

    fpLogEvent(en->rtn, en->otn, (Packet*)user);
    sfthreshold_reset();

    return 0;
}

/*
**  We return whether we logged events or not.  We've add a eventq user
**  structure so we can track whether the events logged were rule events
**  or preprocessor/decoder events.  The reason being that we don't want
**  to flush a TCP stream for preprocessor/decoder events, and cause
**  early flushing of the stream.
*/
int DetectionEngine::log_events(Packet* p)
{
    Profile profile(eventqPerfStats);
    SF_EVENTQ* pq = p->context->equeue;
    sfeventq_action(pq, ::log_events, (void*)p);
    return 0;
}

void DetectionEngine::clear_events(Packet* p)
{
    SF_EVENTQ* pq = p->context->equeue;
    pc.log_limit += sfeventq_reset(pq);
}
