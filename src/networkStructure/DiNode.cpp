/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 8, 2014
*
* Purpose: Implementation file for class DiNode
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class DiNode
*/


#include "DiNode.h"

using namespace networkStructure;

// Constructor method
DiNode::DiNode(unsigned int n): SimpleNode(n){
  inList=new S_List_Map<Edge>;  // Creating in the heap the in edges list
}

// Access method. Returns the node total degree
unsigned int DiNode::getK(){
  return adjList->size()+inList->size();
}

// Access method. Returns the in degree of the node
unsigned int DiNode::getKIn(){
  return inList->size();
}

// Access method. Returns the out degree of the node
unsigned int DiNode::getKOut(){
  return adjList->size();
}

// Access method. Returns an iterator to the beginning of the out edge list
Iterator<Edge> * DiNode::iteratorEdges(){
  return adjList->iterator();
}

// Access method. Returns an iterator to the beginning of the in edge list
Iterator<Edge> * DiNode::iteratorInEdges(){
  return inList->iterator();
}

// Adds an edge to the in and out edges adjacency lists
void DiNode::addEdge(Edge *edge){
  if (edge->getDestiny()->equals(this)){ // Is an "in" edge
    inList->add(edge);
    return;
  }
  if (edge->getOrigin()->equals(this)){ // Is an "out" edge
    adjList->add(edge);
  }
}

// Erases an edge from the adjacency list
void DiNode::eraseEdge (Edge *edge){
    if (edge->getDestiny()->equals(this)) { // Is an "in" edge
    inList->erase(edge->getKey());
    return;
  }
  if (edge->getOrigin()->equals(this)) { // Is an "out" edge
    adjList->erase(edge->getKey());
  }
}

// Erases an edge from the in and out adjacency lists
void DiNode::eraseEdge (unsigned int key0){
  Edge *edge=adjList->find(key0);
  if (edge != nullptr) { // Is an "out" edge
    adjList->erase(key0);
  } else {               // Is an "in" edge or is not an edge of the node
    inList->erase(key0);
  }
}

// Destructor
DiNode::~DiNode(){
  inList->eraseAll();
}

