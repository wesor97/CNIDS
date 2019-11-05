/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 24, 2014
*
* Purpose: Implementation file for class Node
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class Node
*/

#include "SimpleNode.h"

using namespace networkStructure;

// Constructor method
SimpleNode::SimpleNode(unsigned int n){
  key = n;
  adjList=new S_List_Map<Edge>; // Creating in the heap the Edge list
}

//Accessor method. Returns a pointer to the element contained in the node
Element* SimpleNode::getElement(){
  return nullptr;
}

// Access method. Returns the key of the node
unsigned int SimpleNode::getKey(){
  return key;
}

// Access method. Returns the degree of the node
unsigned int SimpleNode::getK(){
  return adjList->size();
}

// Access method. Returns the in degree of the node
unsigned int SimpleNode::getKIn(){
  return adjList->size();
}
// Access method. Returns the node out degree
unsigned int SimpleNode::getKOut(){
  return adjList->size();
}

// Access method. Returns an iterator to the beginning of the edge list
Iterator<Edge> * SimpleNode::iteratorEdges(){
  return adjList->iterator();
}

// Access method. Returns an iterator to the beginning of the edge list
Iterator<Edge> * SimpleNode::iteratorInEdges(){
  return adjList->iterator();
}

// Compares two nodes
bool SimpleNode::equals(Node *node){
  if (node == nullptr) return false;
  return (key == node->getKey());
}

// Adds an edge to the adjacency list
void SimpleNode::addEdge(Edge *edge){
  if (edge->getDestiny()->equals(this) || edge->getOrigin()->equals(this)) {
    adjList->add(edge);
  }
}

// Erases an edge from the adjacency list
void SimpleNode::eraseEdge (Edge *edge){
  adjList->erase(edge->getKey());
}

// Erases an edge from the adjacency list (overload)
void SimpleNode::eraseEdge (unsigned int key){
  adjList->erase(key);
}

// Erases all edges from the adjacency list
void SimpleNode::eraseAllEdges (){
  adjList->eraseAll();
}

// Destructor
SimpleNode::~SimpleNode(){
  adjList->eraseAll();  // Deleting the edges of the adjacency list
  delete adjList;       // Deleting the adjacency list
}