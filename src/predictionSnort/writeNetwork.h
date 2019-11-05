/*
 * writeNetwork.h
 *
 *  Created on: 22 mar. 2019
 *      Author: miguel
 */

#ifndef WRITENETWORK_H_
#define WRITENETWORK_H_
#include "../networkStructure/Network.h"
using namespace networkStructure;
namespace preventionSnort {

class writeNetwork {
protected:
	const char* nameFile;
	Network* net;
public:
	writeNetwork(Network* g);
	void writeFile();
	virtual ~writeNetwork();
};

} /* namespace preventionSnort */

#endif /* WRITENETWORK_H_ */
