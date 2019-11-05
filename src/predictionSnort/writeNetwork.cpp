/*
 * writeNetwork.cpp
 *
 *  Created on: 22 mar. 2019
 *      Author: Werselio José Escribano Ortega
 */

#include "writeNetwork.h"
#include "../networkStructure/Iterator.h"
#include "fstream"
#include "InteractionRule.h"
using namespace std;
using namespace networkStructure;
namespace preventionSnort {

writeNetwork::writeNetwork( Network* g) {
	nameFile = "snort_complex_network.edges";
	net = g;
	writeFile();
}
void writeNetwork::writeFile() {
	Iterator<Node> *q;
	Iterator<Edge> *j;
	ofstream fo;
	fo.open(nameFile, ios::out);
	printf("%d\n",net->getNEdges());
	q = net->iteratorNodes();
	Node *n, *m;
	Edge *e;
	int control=0;
	if (fo.is_open()) {
		fo << "Source " << "Target " << "Label" << endl;
		while (!q->isDone()) {
			n = q->current();
			int key = n->getKey();
			j = n->iteratorEdges();
			while (!j->isDone()) {
				e = j->current();
				m = e->getOpposite(n);
				int key2 = m->getKey();
				if(e->getKey()>=control){
					fo << key << " " << key2 << " " << e->getKey() << endl;
					control++;
				}
				j->next();
			}
			q->next();
		}
		fo.close();
	}
}
writeNetwork::~writeNetwork() {

}

} /* namespace preventionSnort */
