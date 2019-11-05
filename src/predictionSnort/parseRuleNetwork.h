/*
 * parseRuleNetwork.h
 *
 *  Created on: 18 mar. 2019
 *      Author: miguel
 */

#ifndef PARSERULENETWORK_H_
#define PARSERULENETWORK_H_
#include "ElementRule.h"
#include "../networkStructure/Network.h"
#include "../predictionSnort/NodeRule.h"
namespace preventionSnort {

class parseRuleNetwork {
private:
	const char* nameFile;
public:
	parseRuleNetwork(const char* nameFile);
	list<string> readPorts(char* ports);
		void parseHeader(string frase, string*protocol, string *sourceAddress,
				list<string> *sourcePort, string *destinyAddress,
				list<string> *destinyPort, bool *bidireccional);
		string parseKey(char* token);
		string parseValue(char*token);
		multimap<string, string> parseOptions(string frase, list<string> *references);
		ElementRule parseLine(string frase);
		list<ElementRule> parseRules();
		list<string>relacion_cve(list<string>l1,list<string>l2);
		Node* get_Node(int sid,int gid, Network* g);
		Network* construir_red(list<ElementRule> list_elements);
	virtual ~parseRuleNetwork();
};

} /* namespace preventionSnort */

#endif /* PARSERULENETWORK_H_ */
