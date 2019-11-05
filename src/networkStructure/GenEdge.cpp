/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 25, 2014
*
* Purpose: Implementation file for class GenEdge
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class GenEdge
*/

#include "GenEdge.h"

using namespace networkStructure;

// Constructor method
GenEdge::GenEdge(Node *n1, Node *n2, Interaction *inter0, unsigned int key0) :
         SimpleEdge (n1, n2, key0){
  inter=inter0;
}

// Access method. Returns the edge's key
unsigned int GenEdge::getKey(){
  return key;
}

// Access method. Returns the edge's interaction
Interaction* GenEdge::getInteraction(){
  return inter;
}

// Destructor method
GenEdge::~GenEdge(){
  delete inter;
}
