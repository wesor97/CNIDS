/*
 * ElementRule.h
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#ifndef NODERULE_H_
#define NODERULE_H_
#include "../networkStructure/Element.h"
#include "../networkStructure/GenNode.h"
#include "string"
#include "list"
#include "map"
using namespace std;
using namespace networkStructure;
namespace preventionSnort {

	class NodeRule : public GenNode {
		protected:
	      //Cabecera
	      int sid;
	      int gid;
		public:
	      	  NodeRule(Element* element, unsigned int n, int sid, int gid);
	          //Getter y setters
	          int getSid();
		  int getGid();
	          
		virtual ~NodeRule();
	};
}
#endif /* ELEMENTRULE_H_ */
