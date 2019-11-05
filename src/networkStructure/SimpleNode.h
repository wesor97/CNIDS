/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 24, 2014
*
* Purpose: Definition (header) for class SimpleNode
*
*****************************************************************************/

/**
 * @file
 * Definition (header) file for class Simple Node representing the basic
 * structure and behavior of a simple node (one without an element associated)
 * in a network.
 */

#ifndef SIMPLENODE_H
#define	SIMPLENODE_H



#include "Node.h"
#include "S_List_Map.h"

namespace networkStructure {

  /**
   * \brief Defines the behavior of a simple node in an undirected network
   *
   * This class represents the basic structure and behavior of a simple
   * node (one without an element associated) in a network. An unsigned int is
   * used as key to identify the node.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 24, 2014
   */


  class SimpleNode : public Node {
    protected:
                unsigned int key; ///< Unique key (an unsigned int) of the node
     ListNetwork <Edge> *adjList; ///< Adjacency (edge) list


    public:

      /**
      * Constructor method
      * @param n An unsigned integer identifying the node
      */
      SimpleNode (unsigned int n);

      /**
      * Accessor method.
      * Returns a pointer to the element contained in the node. In this class,
      * it returns nullptr (C++11)
      * @return A pointer to the element contained in the node. Here, it returns
      * nullptr (C++11)
      */
      virtual Element* getElement();

      /**
      * Accessor method.
      * Returns the key (unique unsigned int) identifying the node
      * @return The key (unique unsigned int) of the node
      */
      unsigned int getKey();

      /**
      * Accessor method.
      * Gets the node total degree
      * @return The node total degree (k)
      */
      virtual unsigned int getK();

      /**
      * Accessor method.
      * Gets the node in degree. Here, this equals the total degree, k
      * @return The node in degree (k in)
      */
      virtual unsigned int getKIn();

      /**
      * Accessor method.
      * Gets the node out degree. Here, this equals the total degree, k
      * @return The node out degree (k out)
      */
      virtual unsigned int getKOut();

      /**
      * Accessor method.
      * Gets an iterator to the nodes edge list.
      * @return An iterator to edge list of the node
      */
      virtual Iterator<Edge>* iteratorEdges();

      /**
      * Accessor method.
      * Gets an iterator to the nodes's input edge list (in edges). Here,
      * undirected network, is the same as iteratorEdges.
      * @return  An iterator to the edge list of the node
      */
      virtual Iterator<Edge>* iteratorInEdges();

      // Additional methods
      /**
      * Checks if the current and the given nodes are the same as defined by the
      * key
      * @param node A pointer to a node object
      * @return True if both nodes are equal, false otherwise
      */
      bool equals (Node *node);

      /**
      * Adds an edge to the edge list of the current node
      * @param edge A pointer to an edge object
      */
      virtual void addEdge(Edge *edge);

      /**
      * Erases an edge from the edge list of the current node
      * @param edge A pointer to an edge object
      */
      virtual void eraseEdge (Edge *edge);

      /**
      * Erases an edge from the edge list of the current node
      * @param key The unsigned int ID key of the edge object
      */
      virtual void eraseEdge (unsigned int key);

      /**
      * Erases all edges from the edge list of the current node
      */
      void eraseAllEdges ();

      // Destructor method
      /**
      * Destructor method. Erases all edges from the
      * adjacency list and the list itself
      */
      virtual ~SimpleNode();
  };

}

#endif	/* SIMPLENODE_H */

