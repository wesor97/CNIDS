/*
 * AlertNetwork.cpp
 *
 *  Created on: 23 may. 2019
 *      Author: miguel
 */

#include "AlertNetwork.h"
#include "stdio.h"
#include "fstream"
#include "stdlib.h"
#include "string.h"
#include "ElementRule.h"
#include "log/text_log.h"
#include "NodeRule.h"
using namespace std;
using namespace snort;
namespace preventionSnort {

AlertNetwork::AlertNetwork(TextLog* log1)
{
    log=log1;
}

bool AlertNetwork::compare_nodes(Node* n1,Node* n2){
    bool comprobar=false;
    Iterator <Edge>* iter;
    Edge* e;
    Node* aux;
    char ser1[50];
    char ser2[50];
    iter=n1->iteratorEdges();
    while(!iter->isDone()){
        e=iter->current();
        aux=e->getOpposite(n1);
        if(aux->equals(n2)){
            comprobar=true;
        }
        iter->next();
    }
    /*if(!comprobar){
        ElementRule e1=n1->getElement();
        ElementRule e2=n2->getElement();
        string service1=e1.getService();
        string service2=e2.getService();
        if(service1.compare(service2)==0)
            comprobar=true;
    }*/
    return comprobar;
}

Node* AlertNetwork::get_Node(int sid, int gid, Network* g)
{
    Node* node;
    bool continuar=true;
    Iterator<Node>* iter=g->iteratorNodes();
    while(!iter->isDone() && continuar){
        node=iter->current();
        NodeRule* n = dynamic_cast<NodeRule*>(node);
	int sid1 = n->getSid();
	int gid1 = n->getGid();
	
	if(sid==sid1 && gid==gid1)
            continuar=false;
        iter->next();
    }
    if(continuar)
        node=nullptr;
    return node;

}

void AlertNetwork::make_log(int sid, int gid,Network* g)
{
    //comprobamos que exista el id dentro de la red
    Iterator<Node> *q;
    bool aniadido=false;
    Node* aux;
    //Como busco dentro de la red el nodo con sid pasado como argumento si este no está lo suprime. Por tanto hay que incluir los builtin en la red compleja.
    //int id=
    Node* node=get_Node(sid,gid,g);
    if(node!=nullptr){
        if(visitedNodes.size()==0){
            pair<int,int> p;
            p.first=sid;
            p.second=gid;
            visitedNodes.push_back(p);
            print_to_file(sid,gid);
        }            
        else{
            for(pair<int,int> p1 : visitedNodes){
                aux=get_Node(p1.first,p1.second,g);
                if(node->getKey()==aux->getKey()){
                    aniadido=true;
                }
                else if(compare_nodes(node,aux)){
		    ElementRule e=node->getElement();
                    int sid1=atoi(e.getSid().c_str());
		    int gid1=atoi(e.getGid().c_str());
                    print_to_file(sid1,gid1);
                }
            }
            if(!aniadido) {
                pair<int,int>p;
		p.first=sid;
		p.second=gid;
                visitedNodes.push_back(p);
                print_to_file(sid,gid);
            }
        }
    }	
}
void AlertNetwork::print_to_file(int sid,int gid) {
    ofstream fo;
    char name[500];
    sprintf(name,"%d-%d",gid,sid);
    char content[10000];  
    fo.open(name, ios::app);
    if (fo.is_open()) {
        TextLog_FileLog(log,content);
        fo << content << endl;
    }
    fo.close();
}

AlertNetwork::~AlertNetwork() {
	// TODO Auto-generated destructor stub
}

} /* namespace preventionSnort */
