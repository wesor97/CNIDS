/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: January 29, 2014
*
* Purpose: Implementation file for class S_Net_InCore
*
*****************************************************************************/

/**
 * @file
 * Implementation file for class S_Net_InCore
*/

#include "S_Net_InCore.h"
#include "SimpleNode.h"
#include "SimpleEdge.h"
#include "GenEdge.h"
#include "S_List_Map.h"
#include "S_List_Array.h"
#include <iostream>
#include <cstdlib>


using namespace networkStructure;

// Constructor method
S_Net_InCore::S_Net_InCore(){
  lNodes=new S_List_Map<Node>; // Node list
  lEdges=new S_List_Map<Edge>; // Edge list
}

// Constructor method
S_Net_InCore::S_Net_InCore(unsigned int n, unsigned int m){
  if (n < 1000) n = 1000;
  if (m < 1000) m = 1000;
  lNodes=new S_List_Array<Node>(n); // Node list
  lEdges=new S_List_Array<Edge>(m); // Edge list
}

// Returns the number of nodes
unsigned int S_Net_InCore::getNNodes(){
  return lNodes->size();
}

// Returns maximum degree in the network
unsigned int S_Net_InCore::getKMax(){
  int aux=0;
  unsigned int kmax=0;
  Iterator<Node> *q;
  q=lNodes->iterator();

  // Iterating over nodes
  while(!q->isDone()){
    aux=q->current()->getK();
    if (aux>kmax) kmax=aux;
    q->next();
  }
  delete q;
  return kmax;
}

// Returns minimum degree in the network
unsigned int S_Net_InCore::getKMin(){
  int aux=0;
  unsigned int kmin=0;
  Iterator<Node> *q;

  // Iterating over nodes
  q=lNodes->iterator();
  kmin=q->current()->getK();
  while(!q->isDone()){
    aux=q->current()->getK();
    if (aux<kmin) kmin=aux;
    q->next();
  }
  delete q;
  return kmin;
}

// Returns the number of edges
unsigned int S_Net_InCore::getNEdges(){
  return lEdges->size();
}

// Adds a node given through a pointer
Node* S_Net_InCore::addNode(Node *node){
  return lNodes->add(node);
}

// Adds a node given through an integer
Node* S_Net_InCore::addNode(unsigned int n) {
  return lNodes->add(new SimpleNode(n));
}

// Adds an edge given through a pointer
Edge* S_Net_InCore::addEdge(Edge *edge){
  Node *node;

  node = edge->getOrigin();
  node = lNodes->add(node);
  node->addEdge(edge); // Adding edge to the adjacency list of node origin
  node = edge->getDestiny();
  node = lNodes->add(node);
  node->addEdge(edge); // Adding edge to the adjacency list of node destiny
  return lEdges->add(edge);  // Adding edge
}

// Adds a simple edge given through two nodes
Edge* S_Net_InCore::addEdge(Node *node1, Node *node2){
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge=new SimpleEdge (node1, node2, lEdges->size());
  node1->addEdge(edge); // Adding edge to the adjacency list of node origin
  node2->addEdge(edge); // Adding edge to the adjacency list of node destiny
  return lEdges->add(edge);            // Adding edge
}

// Adds a simple edge given through two unsigned int
Edge* S_Net_InCore::addEdge(unsigned int key1, unsigned int key2){
  Node *node1 = new SimpleNode(key1);
  Node *node2 = new SimpleNode(key2);
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge = new SimpleEdge (node1, node2, lEdges->size());
  node1->addEdge(edge); // Adding edge to the adjacency list of node origin
  node2->addEdge(edge); // Adding edge to the adjacency list of node destiny
  return lEdges->add(edge);            // Adding edge
}



// Adds ageneral edge given through two nodes
Edge* S_Net_InCore::addEdge(Node *node1, Node *node2, Interaction *inter){
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge=new GenEdge (node1, node2, inter, lEdges->size());
  node1->addEdge(edge); // Adding edge to the adjacency list of node origin
  node2->addEdge(edge); // Adding edge to the adjacency list of node destiny
  return lEdges->add(edge);            // Adding edge
}

// Adds a general edge given through two unsigned int
Edge* S_Net_InCore::addEdge(unsigned int key1, unsigned int key2,
                            Interaction *inter){
  Node *node1 = new SimpleNode(key1);
  Node *node2 = new SimpleNode(key2);
  node1 = lNodes->add(node1);   // Adding node1. The result is the node in
                                // the network
  node2 = lNodes->add(node2);   // Adding node2. The result is the node in
                                // the network
  Edge *edge = new GenEdge (node1, node2, inter, lEdges->size());
  node1->addEdge(edge); // Adding edge to the adjacency list of node origin
  node2->addEdge(edge); // Adding edge to the adjacency list of node destiny
  return lEdges->add(edge);            // Adding edge
}

// Returns a given node from the network (nullptr if the node does not exist)
Node* S_Net_InCore::getNode(unsigned int key){
  return lNodes->find(key);
}

// Returns a given edge from the network (nullptr if the edge does not exist)
Edge* S_Net_InCore::getEdge(unsigned int key){
  return lEdges->find(key);
}

// Removes a node (and its associated edges) from the node list
void S_Net_InCore::eraseNode (Node *node){
  // Removes the edges of the node from the edges list
  Iterator<Edge> *p;
  Node *aux = node;
  node = lNodes->find(node->getKey());

  if (node == nullptr) {
    // If the node does not exist in the graph
    std::cout<<endl<<"The node identified as \""<<aux->getKey()
             <<"\" cannot be removed from the network because it does not exist"
             <<" in it"<<endl;
    std::exit(EXIT_FAILURE);
  }

  // Auxiliary variables
  Edge *e;
  unsigned int key;

  for (p = node->iteratorEdges(); !p->isDone(); p->next()){
    e = p->current();
    aux = e->getOpposite(node);
    key = e->getKey();
    aux->eraseEdge(e);
    delete (e);
    lEdges->erase(key);
  }
  lNodes->erase(node->getKey());  // Removes node (deletes the adjacency list,
  delete node;                    // too)
  delete p;
}



// Removes a node (and its associated edges) from the node list
void S_Net_InCore::eraseNode(unsigned int key){
  // Removes the edges of the node from the edges list
  Iterator<Edge> *p;
  Node *node=lNodes->find(key);  // Finding the node with that key

  if (node == nullptr) {
    // If the node does not exist in the graph
    std::cout<<endl<<"The node identified as \""<<key
             <<"\" cannot be removed from the network because it does not exist"
             <<" in it"<<endl;
    std::exit(EXIT_FAILURE);
  }

  // Auxiliary variables
  Edge *e;
  Node *aux;
  unsigned int keyE;

  for (p = node->iteratorEdges(); !p->isDone(); p->next()){
    e = p->current();
    aux = e->getOpposite(node);
    keyE = e->getKey();
    aux->eraseEdge(e);
    delete (e);
    lEdges->erase(keyE);
  }
  lNodes->erase(node->getKey());  // Removes node (deletes the adjacency list,
  delete node;                    // too)
  delete p;
}

// Removes an edge from the edge list
void S_Net_InCore::eraseEdge(Edge *edge){
  Edge *aux = edge;
  edge = lEdges->find(edge->getKey());

  if (edge == nullptr) {
    // If the edge does not exist in the graph
    std::cout<<endl<<"The edge identified as \""<<aux->getKey()
             <<"\" cannot be removed from the network because it does not exist"
             <<" in it"<<endl;
    std::exit(EXIT_FAILURE);
  }

  // Removing from the adjacency list of its nodes
  Node *node=edge->getOrigin();
  node->eraseEdge(edge);
  node=edge->getDestiny();
  node->eraseEdge(edge);
  // Removing from the list of nodes
  lEdges->erase(edge->getKey());
  //Freeing memory
  delete edge;
}


// Removes an edge from the edge list
void S_Net_InCore::eraseEdge(unsigned int key){
  Edge *edge = lEdges->find(key);

  if (edge == nullptr) {
    // If the edge does not exist in the graph
    std::cout<<endl<<"The edge identified as \""<<key
             <<"\" cannot be removed from the network because it does not exist"
             <<" in it"<<endl;
    std::exit(EXIT_FAILURE);
  }

  // Removing from the adjacency list of its nodes
  Node *node=edge->getOrigin();
  node->eraseEdge(edge);
  node=edge->getDestiny();
  node->eraseEdge(edge);
  // Removing from the list of nodes
  lEdges->erase(edge->getKey());
  //Freeing memory
  delete edge;
}

 // Returns an iterator to the adjacent nodes list
Iterator <Node>* S_Net_InCore::getAdjacentNodes(Node* node){
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
  Iterator<Edge> *it=node->iteratorEdges();
  while(!it->isDone()){
    l->add(it->current()->getOpposite(node));
    it->next();
  }
  delete it;
  return l->iterator();
}

 // Returns an iterator to the adjacent nodes list
Iterator <Node>* S_Net_InCore::getAdjacentNodes(unsigned int key){
  Node *node = lNodes->find(key);

  if (node == nullptr) {
    // If the node does not exist in the graph
    std::cout<<endl<<"The adjacent nodes to the node identified as \""
             <<key<<"\" cannot be provided because the node does "
             <<"not exist in the graph"<<endl;
    std::exit(EXIT_FAILURE);
  }

  ListNetwork<Node> *l=new S_List_Map<Node>;
  Iterator<Edge> *it=node->iteratorEdges();
  while(!it->isDone()){
    l->add(it->current()->getOpposite(node));
    it->next();
  }
  delete it;
  return l->iterator();
}

 // Returns an iterator to the adjacent nodes list
Iterator <Node>* S_Net_InCore::getAdjacentInNodes(Node* node){
  getAdjacentNodes(node);
}

 // Returns an iterator to the adjacent nodes list
Iterator <Node>* S_Net_InCore::getAdjacentInNodes(unsigned int key){
  getAdjacentNodes(key);
}

// Returns an iterator to the node list
Iterator <Node>* S_Net_InCore::iteratorNodes(){
  return lNodes->iterator();
}

// Returns an iterator to the edge list
Iterator <Edge>* S_Net_InCore::iteratorEdges(){
  return lEdges->iterator();
}

// Destructor method
S_Net_InCore::~S_Net_InCore(){
  // Removing individual nodes
  Iterator<Node> *it = lNodes->iterator();
  while (!it->isDone()) {
    delete (it->current());
    it->next();
  }

  // Removing individual edges
  Iterator<Edge> *ie = lEdges->iterator();
  while (!ie->isDone()) {
    delete (ie->current());
    ie->next();
  }

  // Removing the list of nodes
  delete lNodes;
  // Removing the list of edges
  delete lEdges;
}
