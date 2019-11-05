/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 8, 2014
*
* Purpose: Definition (header) for class DiNode
*
*****************************************************************************/


/**
 * @file
 * Definition (header) file for class DiNode
*/


#ifndef DINODE_H
#define	DINODE_H

#include "SimpleNode.h"

namespace networkStructure {

  /**
   * \brief Defines a simple node in a directed network
   *
   * Defines a directed node in a network (a directed node has adjacency lists
   * for output and input edges)
   *
   * This class represents the basic structure and behavior of a directed node
   * in a directed network.
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date April 8, 2014
   */

  class DiNode: public SimpleNode {
    protected:
      ListNetwork <Edge> *inList; ///< Input adjacency list

    public:
      /**
      * Constructor method
      * @param n An unsigned integer identifying the node
      */
      DiNode (unsigned int n);

      // Accessor methods

      /**
      * Accessor method.
      * Gets the node total degree
      * @return The node total degree (k)
      */
      unsigned int getK();

      /**
      * Accessor method.
      * Gets the node in degree.
      * @return The node in degree (k in)
      */
      unsigned int getKIn();

      /**
      * Accessor method.
      * Gets the node out degree.
      * @return The out degree (k out) of the node
      */
      unsigned int getKOut();

      /**
      * Accessor method.
      * Gets an iterator to the out edge list of the node.
      * @return An iterator to the out edge list of the node
      */
      Iterator<Edge>* iteratorEdges();

      /**
      * Accessor method.
      * Gets an iterator to the input edge list (in edges) of the node.
      * @return  An iterator to the in edge list of the node
      */
      Iterator<Edge>* iteratorInEdges();

      /**
      * Adds an edge to the node. If the node is the origin node of the edge
      * it is added to the out edge list of the node. If the node is the
      * destiny edge of the node it is added to the out edge list of the node
      * @param edge A pointer to an edge object
      */
      void addEdge(Edge *edge);

      /**
      * Erases an edge from the current node. If the node is the origin node of
      * the edge it is removed from the out edge list of the node. If the node
      * is the edge destiny of the node it is removed from the in edge list
      * of the node
      * @param key0 The unsigned int ID key of the edge object
      */
      virtual void eraseEdge (unsigned int key0);

      /**
      * Erases an edge from the current node. If the node is the origin node of
      * the edge it is removed from the out edge list of the node. If the node
      * is the edge destiny of the node it is removed from the in edge list
      * of the node
      * @param edge A pointer to an edge object
      */
      virtual void eraseEdge (Edge *edge);

      // Destructor method
      /**
      * Destructor method. Erases all edges from the
      * out adjacency list and the list itself
      */
      ~DiNode();
  };

}

#endif	/* DINODE_H */

