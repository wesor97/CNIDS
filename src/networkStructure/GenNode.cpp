/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 24, 2014
*
* Purpose: Implementation file for class GenNode
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class GenNode
*/

#include "GenNode.h"


using namespace networkStructure;

// Constructor method
GenNode::GenNode(Element* element0, unsigned int n) : SimpleNode(n){
  element = element0;
}

//Accessor method. Returns a pointer to the element contained in the node
Element* GenNode::getElement(){
  return element;
}

// Destructor
GenNode::~GenNode(){
  delete element;       // Deleting the element
}