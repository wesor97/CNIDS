/*
 * AlertNetwork.h
 *
 *  Created on: 23 may. 2019
 *      Author: miguel
 */

#ifndef ALERTNETWORK_H_
#define ALERTNETWORK_H_

#include "networkStructure/Node.h"
#include "log/text_log.h"
#include "networkStructure/Network.h"
#include "list"
using namespace networkStructure;
using namespace std;

namespace preventionSnort {

static list<pair<int,int>> visitedNodes;

class AlertNetwork {
private:
    TextLog* log;
public:
    AlertNetwork(TextLog* log);
    bool compare_nodes(Node* n1,Node* n2);
    void make_log(int sid,int gid,Network* g);
    void print_to_file(int sid,int gid);
    Node* get_Node(int sid, int gid, Network* g);
    virtual ~AlertNetwork();
};

} /* namespace preventionSnort */

#endif /* ALERTNETWORK_H_ */
