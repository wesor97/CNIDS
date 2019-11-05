/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: January 21, 2014
*
* Purpose: Implementation file for class SimpleEdge
*
******************************************************************************/

/**
 * @file
 * Implementation file for class SimpleEdge
*/

#include "SimpleEdge.h"
#include "Node.h"


using namespace networkStructure;

// Constructor method
SimpleEdge::SimpleEdge(Node *n1, Node *n2, unsigned int key0){
  origin=n1;
  destiny=n2;
  key=key0;
}

// Access method. Returns the first (origin) node of the edge
Node* SimpleEdge::getOrigin(){
  return origin;
}

// Access method. Returns the second (destiny) node of the edge
Node* SimpleEdge::getDestiny(){
  return destiny;
}

// Access method. Returns the edge key
unsigned int SimpleEdge::getKey(){
  return key;
}

// Access method. Returns the edge interaction
Interaction* SimpleEdge::getInteraction(){
  return nullptr;
}

// Mutator method. Updates the first node of the edge
void SimpleEdge::setOrigin(Node *node){
  origin=node;
}

// Mutator method. Updates the second node of the edge
void SimpleEdge::setDestiny(Node *node){
  destiny=node;
}

// Method returning a reference to the node opposite to the one given
Node* SimpleEdge::getOpposite (Node *node){
  if (node->equals(origin))
    return destiny;
  else if (node->equals(destiny))
    return origin;
  else
    return nullptr; // Reference to nullptr (C++11)
}

// Compares two edges
bool SimpleEdge::equals(Edge *edge){
  if (edge == nullptr) return false;
  return (key == edge->getKey());
}

// Destructor method
SimpleEdge::~SimpleEdge(){}


