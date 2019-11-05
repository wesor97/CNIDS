/*
 * ElementRule.h
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#ifndef ELEMENTRULE_H_
#define ELEMENTRULE_H_
#include "../networkStructure/Element.h"
#include "string"
#include "list"
#include "map"
using namespace std;
using namespace networkStructure;
namespace preventionSnort {

	class ElementRule : public Element {
		protected:
	      //Cabecera
	      string protocol;
	      list<string> sourcePort;
	      list<string> destinyPort;
	      string sourceAddress;
	      string destinyAddress;
	      bool bidirectional;
	      bool comprobar;
	      //Cuerpo
	      multimap<string,string> options;
	      list<string>reference;

		public:
	      	  ElementRule(string protocol, string sourceAddress,list<string> sourcePort, string destinyAddress,list<string> destinyPort,bool bidirectional,multimap<string,string>options,list<string>reference);
	      	  ElementRule(bool comprobar);
	          //Getter y setters
	          string getProtocol();
	          list<string> getSourcePort();
	          list<string> getDestinyPort();
	          string getSourceAddress();
	          string getDestinyAddress();
	          bool getComprobar();
	          multimap<string,string> getOptions();
	          bool getBidirectional();
	          string getSid();
                  string getGid();
		  string getService();
	          list<string>getReference();
		virtual ~ElementRule();
	};
}
#endif /* ELEMENTRULE_H_ */
