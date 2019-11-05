/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 8, 2014
*
* Purpose: Implementation file for class S_DiNet_InCore
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class S_DiNet_InCore
*/

#include "S_DiNet_InCore.h"
#include "DiNode.h"
#include "SimpleEdge.h"
#include "GenEdge.h"
#include <iostream>
#include <cstdlib>


using namespace networkStructure;

// Constructor method
S_DiNet_InCore::S_DiNet_InCore(){
  // In C++ the default constructor of the base class is called here
}

// Constructor method
S_DiNet_InCore::S_DiNet_InCore(unsigned int n, unsigned int m):
                S_Net_InCore(n, m){
}

// Adds a node given through an integer
Node* S_DiNet_InCore::addNode(unsigned int n) {
  return lNodes->add(new DiNode(n));
}

// Adds an edge given through two nodes
Edge* S_DiNet_InCore::addEdge(Node *node1, Node *node2){
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge=new SimpleEdge (node1, node2, lEdges->size());
  node1->addEdge(edge); // Adding edge to the out edge list of node origin
  node2->addEdge(edge); // Adding edge to the in edge list of node destiny
  return lEdges->add(edge);  // Adding edge
}

// Adds an edge given through two unsigned int
Edge* S_DiNet_InCore::addEdge(unsigned int key1, unsigned int key2){
  Node *node1 = new DiNode(key1);
  Node *node2 = new DiNode(key2);
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge = new SimpleEdge (node1, node2, lEdges->size());
  node1->addEdge(edge); // Adding edge to the out edge list of node origin
  node2->addEdge(edge); // Adding edge to the in edge list of node destiny
  return lEdges->add(edge);  // Adding edge
}

// Adds an edge given through two nodes
Edge* S_DiNet_InCore::addEdge(Node *node1, Node *node2, Interaction *inter){
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge=new GenEdge (node1, node2, inter, lEdges->size());
  node1->addEdge(edge); // Adding edge to the out edge list of node origin
  node2->addEdge(edge); // Adding edge to the in edge list of node destiny
  return lEdges->add(edge);  // Adding edge
}

// Adds an edge given through two unsigned int
Edge* S_DiNet_InCore::addEdge(unsigned int key1, unsigned int key2,
                              Interaction *inter){
  Node *node1 = new DiNode(key1);
  Node *node2 = new DiNode(key2);
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge = new GenEdge (node1, node2, inter, lEdges->size());
  node1->addEdge(edge); // Adding edge to the out edge list of node origin
  node2->addEdge(edge); // Adding edge to the in edge list of node destiny
  return lEdges->add(edge);  // Adding edge
}

 // Returns an iterator to the adjacent input nodes list
Iterator <Node>* S_DiNet_InCore::getAdjacentInNodes(Node* node){
  Node *aux = node;
  node = lNodes->find(node->getKey());

  if (node == nullptr) {
    // If the node does not exist in the graph
    std::cout<<endl<<"The adjacent nodes to the node identified as \""
             <<aux->getKey()<<"\" cannot be provided because the node does "
             <<"not exist in the graph"<<endl;
    std::exit(EXIT_FAILURE);
  }

  ListNetwork<Node> *l=new S_List_Map<Node>;
  Iterator<Edge> *it=node->iteratorInEdges();
  while(!it->isDone()){
    l->add(it->current()->getOpposite(node));
    it->next();
  }
  delete it;
  return l->iterator();
}

 // Returns an iterator to the adjacent input nodes list
Iterator <Node>* S_DiNet_InCore::getAdjacentInNodes(unsigned int key){
  Node *node = lNodes->find(key);

  if (node == nullptr) {
    // If the node does not exist in the graph
    std::cout<<endl<<"The adjacent nodes to the node identified as \""
             <<key<<"\" cannot be provided because the node does "
             <<"not exist in the graph"<<endl;
    std::exit(EXIT_FAILURE);
  }

  ListNetwork<Node> *l=new S_List_Map<Node>;
  Iterator<Edge> *it=node->iteratorInEdges();
  while(!it->isDone()){
    l->add(it->current()->getOpposite(node));
    it->next();
  }
  delete it;
  return l->iterator();
}

// Destructor method
S_DiNet_InCore::~S_DiNet_InCore(){}
