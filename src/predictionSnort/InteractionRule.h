/*
 * InteractionRule.h
 *
 *  Created on: 6 mar. 2019
 *      Author: werselio
 */

#ifndef INTERACTIONRULE_H_
#define INTERACTIONRULE_H_
#include "../networkStructure/Interaction.h"
#include "string"
using namespace std;
using namespace networkStructure;
namespace preventionSnort {
	class InteractionRule: public Interaction {
		protected:
			string reference;
		public:
			InteractionRule(double w, string reference);
			string getReference();

			virtual ~InteractionRule();
	};
}
#endif /* INTERACTIONRULE_H_ */
