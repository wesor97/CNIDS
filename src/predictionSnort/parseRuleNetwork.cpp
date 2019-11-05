/*
 * parseRuleNetwork.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: miguel
 */

#include "parseRuleNetwork.h"
#include "string.h"
#include "stdlib.h"
#include "fstream"
#include "../networkStructure/S_Net_InCore.h"
#include "../predictionSnort/NodeRule.h"
#include "InteractionRule.h"
using namespace std;
using namespace networkStructure;
namespace preventionSnort {

parseRuleNetwork::parseRuleNetwork(const char* nameFile0) {
	nameFile = nameFile0;
}

list<string> parseRuleNetwork::readPorts(char* ports) {
	list<string> sourcePort;
	char* ptrptr[1000000];
	if (ports[0] != 91) {
		string aux(ports);

		sourcePort.push_back(aux);
	} else {
		const char* coma = ",";
		char cad[strlen(ports) + 1];
		strcpy(cad, ports);
		char* port = strtok_r(cad, coma, ptrptr);
		while (port != NULL) {
			if (port[0] != 93) {
				string aux(port);
				sourcePort.push_back(aux);
			}
			port = strtok_r(NULL, coma, ptrptr);
		}
	}
	return sourcePort;
}
void parseRuleNetwork::parseHeader(string frase, string *protocol,
		string *sourceAddress, list<string> *sourcePort, string *destinyAddress,
		list<string> *destinyPort, bool *bidireccional) {
	int truncar = frase.find("(", 0);
	char* cstr = new char[frase.size() + 1];
	strcpy(cstr, frase.c_str());
	cstr[truncar] = '\0';
	const char* c = " ";
	if (cstr[0] == 35) {
		cstr[0] = ' ';
	}
	int control = 0;
	char* token = strtok(cstr, c);
	*bidireccional = false;
	while (token != NULL) {
		switch (control) {
		case 1: {
			string aux1(token);
			protocol->replace(0, aux1.size(), aux1);
		}
			break;
		case 2: {
			string aux2(token);
			sourceAddress->replace(0, aux2.size(), aux2);
		}
			break;
		case 3: {
			*sourcePort = readPorts(token);
		}
			break;
		case 4: {
			if (token[0] == 60)
				*bidireccional = true;
		}
			break;
		case 5: {
			string aux4(token);
			destinyAddress->replace(0, aux4.size(), aux4);
		}
			break;
		case 6: {
			*destinyPort = readPorts(token);
		}
			break;
		}
		control++;
		token = strtok(NULL, c);
	}

}

string parseRuleNetwork::parseKey(char* token) {
	char* pkpk[1000000];
	char* token1 = strtok_r(token, ": ", pkpk);
	string aux(token1);
	while (token1 != NULL) {
		token1 = strtok_r(NULL, ":", pkpk);
	}

	return aux;
}
string parseRuleNetwork::parseValue(char* token) {
	char* pvpv[1000000];
	char*token1 = strtok_r(token, ":", pvpv);
	int control = 0;
	string aux;
	while (token1 != NULL) {
		if (control == 1) {
			string var(token1);
			aux.replace(0, var.size(), var);
		}
		control++;
		token1 = strtok_r(NULL, ":", pvpv);
	}
	return aux;
}

multimap<string, string> parseRuleNetwork::parseOptions(string frase,
		list<string>*references) {
	char options[frase.size() + 1];
	string key;
	multimap<string, string> values;
	strcpy(options, frase.c_str());
	const char* c = ";";
	char* token1 = strtok(options, c);
	while (token1 != NULL) {
		char opcion[10000];
		char opcion1[10000];
		strcpy(opcion, token1);
		strcpy(opcion1, token1);
		string key = parseKey(opcion);
		string value = parseValue(opcion1);
		if (key.compare("reference") == 0
				&& value.find("cve") != string::npos) {
			references->push_back(value);
		} else {
			if (value[0] == 34 && value[value.size() - 1] == 34)
				value = value.substr(1, value.size() - 2);
			values.insert(pair<string, string>(key, value));
		}

		token1 = strtok(NULL, c);
	}
	return values;
}
ElementRule parseRuleNetwork::parseLine(string frase) {
	if (frase.size() > 0) {
		if (frase.find("sid:") != string::npos) {
			int divide = frase.find("(");
			string options = frase.substr(divide + 2);
			string protocol;
			string sourceAddress;
			string destinyAddress;
			list<string> sourcePort;
			list<string> destinyPort;
			list<string> references;
			bool bidireccional;
			parseHeader(frase, &protocol, &sourceAddress, &sourcePort,
					&destinyAddress, &destinyPort, &bidireccional);
			multimap<string, string> optionsValues = parseOptions(options,
					&references);
			ElementRule element(protocol, sourceAddress, sourcePort,
					destinyAddress, destinyPort, bidireccional, optionsValues,
					references);
			return element;
		} else {
			ElementRule element(false);
			return element;
		}
	} else {
		ElementRule element(false);
		return element;
	}
}

list<ElementRule> parseRuleNetwork::parseRules() {
	ifstream ficheroEntrada;
	string frase;
	list<ElementRule> lista;
	ficheroEntrada.open(nameFile);
	while (!ficheroEntrada.eof()) {
		getline(ficheroEntrada, frase);
		ElementRule bien = parseRuleNetwork::parseLine(frase);
		if (bien.getComprobar() == true) {
			lista.push_back(bien);
		}
	}
	ficheroEntrada.close();
	return lista;
}
list<string> parseRuleNetwork::relacion_cve(list<string> l1, list<string> l2) {
	list<string> aristas;
	for (string s : l1) {
		for (string r : l2) {
			if (s.compare(r) == 0) {
				aristas.push_back(s);
			}
		}
	}
	return aristas;
}

Node* parseRuleNetwork::get_Node(int sid,int gid, Network* g){
    bool continuar=true;
    Iterator<Node>* iter=g->iteratorNodes();
    while(!iter->isDone()){
        Node* node = iter->current();

        NodeRule* n = dynamic_cast<NodeRule*>(node);
	int sid1 = n->getSid();
	int gid1 = n->getGid();

	if(sid == sid1 && gid == gid1){
	    return node;
	}
        iter->next();
    }
        return nullptr;
}

Network* parseRuleNetwork::construir_red(list<ElementRule> list_elements) {
	Network *g = new S_Net_InCore();
        int id=1;
	while (!list_elements.empty()) {
		ElementRule item = list_elements.front();
		list_elements.pop_front();
		int sid=atoi(item.getSid().c_str());
		int gid=atoi(item.getGid().c_str());
		if (item.getReference().size() == 0) {
			Node* naux = get_Node(sid,gid, g);
			if(naux==nullptr){							
				naux = new NodeRule(&item, id,sid,gid);
				id++;
				g->addNode(naux);
			}

		} else {
			bool insertado = false;
			Node* n1=get_Node(sid,gid, g);
			if(n1==nullptr){							
				n1 = new NodeRule(&item, id,sid,gid);
				id++;
				g->addNode(n1);
			}
			for (ElementRule item1 : list_elements) {
				int sid1 = atoi(item1.getSid().c_str());
				int gid1 = atoi(item1.getGid().c_str());
				Node* n2=get_Node(sid1,gid1,g);
				if(n2==nullptr){							
					n2 = new NodeRule(&item1, id,sid1,gid1);
					id++;
					g->addNode(n2);
				}
				list<string> lista_j = item1.getReference();
				
				if (item1.getReference().size() != 0) {
					list<string> cve_item = relacion_cve(item.getReference(),
							item1.getReference());
					if (cve_item.size() != 0) {
						insertado = true;
						if (item.getSid().compare(item1.getSid()) != 0 || item.getGid().compare(item1.getGid()) !=0 ) {
							while (!cve_item.empty()) {
								Interaction *intr;
								string cve = cve_item.front();
								cve_item.pop_front();
								intr = new InteractionRule(1, cve);
								g->addEdge(n1->getKey(), n2->getKey(), intr);
							}
						}
					}
				}
			}
		}
	}
	return g;
}

parseRuleNetwork::~parseRuleNetwork() {
	// TODO Auto-generated destructor stub
}

} /* namespace preventionSnort */
