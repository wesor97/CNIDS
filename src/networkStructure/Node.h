/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 24, 2014
*
* Purpose: Abstract class (pure) acting as an interface defining defining the
*          functional specification of a node in a network
*
*****************************************************************************/

/**
 * @file
 * INTERFACE (defined by an abstract class) defining the
 * functional specification of a node in a network.
 */

#ifndef NODE_H
#define	NODE_H


#include "Iterator.h"
#include "Edge.h"
#include "Element.h"


namespace networkStructure {

  /**
   * \brief INTERFACE (defined by an abstract class) defining the basic behavior
   * of a node in a network.
   *
   * An unsigned int is used as key to identify the node.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 24, 2014
   */


  class Node {
    public:

      /**
      * Accessor method.
      * Returns a pointer to the element contained in the node
      * @return A pointer to the element contained in the node
      */
      virtual Element* getElement() = 0;

      /**
      * Accessor method.
      * Returns the key (unique unsigned int) identifying the node
      * @return The key (unique unsigned int) of the node
      */
      virtual unsigned int getKey() = 0;

      /**
      * Accessor method.
      * Gets the total degree of the node
      * @return The total degree (k) of the node
      */
      virtual unsigned int getK() = 0;

      /**
      * Accessor method.
      * Gets the in degree of the node. In a non-directed node this equals the
      * total degree, k
      * @return The in degree (k in) of the node
      */
      virtual unsigned int getKIn() = 0;

      /**
      * Accessor method.
      * Gets the out degree of the node. In a non-directed node this equals the
      * total degree k
      * @return The out degree (k out) of the node
      */
      virtual unsigned int getKOut() = 0;

      /**
      * Accessor method.
      * Gets an iterator to the edge list of the node. In case of a directed
      * network it returns an iterator to the out edges list.
      * @return An iterator to the (all/out) edge list of the node
      */
      virtual Iterator<Edge>* iteratorEdges() = 0;

      /**
      * Accessor method.
      * Gets an iterator to the nodes's input edge list (in edges). In an
      * undirected network it returns the all edges list (same as iteratorEdges)
      * @return  An iterator to the (in/all) edge list of the node
      */
      virtual Iterator<Edge>* iteratorInEdges() = 0;


      // Additional methods
      /**
      * Checks if the current and the given nodes are the same as defined by the
      * key
      * @param node A pointer to a node object
      * @return True if both nodes are equal, false otherwise
      */
      virtual bool equals (Node *node) = 0;

      /**
      * Adds an edge to the edge list of the current node. In a directed network
      * it adds the edge to the in and out edge lists
      * @param edge A pointer to an edge object
      */
      virtual void addEdge(Edge *edge) = 0;

      /**
      * Erases an edge from the edge list of the current node
      * @param edge A pointer to an edge object
      */
      virtual void eraseEdge (Edge *edge) = 0;

      /**
      * Erases an edge from the edge list of the current node
      * @param key The unsigned int ID key of the edge object
      */
      virtual void eraseEdge (unsigned int key) = 0;

      /**
      * Erases all edges from the edge list of the current node
      */
      virtual void eraseAllEdges () = 0;

      // Destructor method
      /**
      * Destructor method. Erases all edges from the
      * adjacency list and the list itself
      */
      virtual ~Node() {};
  };

}

#endif	/* NODE_H */

