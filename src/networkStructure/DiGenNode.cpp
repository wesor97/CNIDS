/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 8, 2014
*
* Purpose: Implementation file for class DiGenNode
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class DiGenNode
*/


#include "DiGenNode.h"

using namespace networkStructure;

// Constructor method
DiGenNode::DiGenNode(Element* element0, unsigned int n) : DiNode(n){
  element = element0;
}

//Accessor method. Returns a pointer to the element contained in the node
Element* DiGenNode::getElement(){
  return element;
}

// Destructor
DiGenNode::~DiGenNode(){
  delete element;       // Deleting the element
}