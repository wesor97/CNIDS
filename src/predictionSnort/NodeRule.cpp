/*
 * InteractionRule.cpp
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#include "NodeRule.h"
using namespace preventionSnort;

//InteractionRule::
NodeRule::NodeRule(Element* e, unsigned int key, int sid0,int gid0) : GenNode (e, key){
	sid=sid0;
	gid=gid0;
}
int NodeRule::getSid(){
	return sid;
}
int NodeRule::getGid(){
	return gid;
}


NodeRule::~NodeRule(){
  //delete reference;
}

