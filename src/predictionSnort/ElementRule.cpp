/*
 * ElementRule.cpp
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#include "ElementRule.h"
using namespace preventionSnort;

ElementRule::ElementRule(string protocol0, string sourceAddress0,
		list<string> sourcePort0, string destinyAddress0,
		list<string> destinyPort0, bool bidirectional0,
		multimap<string, string> options0, list<string> reference0) :
		Element() {
	protocol = protocol0;
	sourcePort = sourcePort0;
	destinyPort = destinyPort0;
	sourceAddress = sourceAddress0;
	destinyAddress = destinyAddress0;
	options = options0;
	bidirectional = bidirectional0;
	comprobar=true;
	reference=reference0;
}
ElementRule::ElementRule(bool comprobar0) :
		Element() {
	comprobar=comprobar0;
	bidirectional = false;
}
list<string> ElementRule::getReference(){
	return reference;
}
string ElementRule::getSid(){
	string devolver;
	multimap<string,string>::iterator it;
	it= options.begin();
	while(it.operator !=(options.end())){
		if(it.operator ->()->first.compare("sid")==0){
			string aux (it.operator->()->second);
			devolver.replace(0,aux.size(),aux);
		}
		it.operator ++();
	}
	return devolver;
}

string ElementRule::getGid(){
	string devolver;
       	bool comprobar=false;
	multimap<string,string>::iterator it;
	it= options.begin();
	while(it.operator !=(options.end())){
		if(it.operator ->()->first.compare("gid")==0){
			string aux (it.operator->()->second);
			devolver.replace(0,aux.size(),aux);
                        comprobar=true;
		}
		it.operator ++();
	}
        if(!comprobar)
        	devolver.replace(0,1,"1");
	return devolver;
}

string ElementRule::getService(){
	string devolucion;
        bool control=false;
	multimap<string,string>::iterator it;
	it= options.begin();
	while(it.operator !=(options.end())){
		if(it.operator ->()->first.compare("service")==0){
			string aux (it.operator->()->second);
			devolucion.replace(0,aux.size(),aux);
		}
		it.operator ++();
	}
	return devolucion;
}
bool ElementRule::getComprobar(){
	return comprobar;
}
string ElementRule::getProtocol() {
	return protocol;
}
list<string> ElementRule::getSourcePort() {
	return sourcePort;
}
list<string> ElementRule::getDestinyPort() {
	return destinyPort;
}
string ElementRule::getSourceAddress() {
	return sourceAddress;
}
string ElementRule::getDestinyAddress() {
	return destinyAddress;
}

multimap<string, string> ElementRule::getOptions() {
	return options;
}
bool ElementRule::getBidirectional() {
	return bidirectional;
}
ElementRule::~ElementRule() {

}

