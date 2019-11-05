/*
 * InteractionRule.cpp
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#include "InteractionRule.h"
using namespace preventionSnort;

//InteractionRule::
InteractionRule::InteractionRule(double w, string reference0) : Interaction (w){
	reference=reference0;
}
string InteractionRule::getReference(){
	return reference;
}


InteractionRule::~InteractionRule(){
  //delete reference;
}

