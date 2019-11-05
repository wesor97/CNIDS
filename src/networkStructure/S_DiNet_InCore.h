/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: January 29, 2014
*
* Purpose: Definition (header) for class S_DiNet_InCore. The class implements
*          the interface Network.
*
* Comment: This class works sequentially and uses map or array based lists
*  as containers.
*
*****************************************************************************/

/**
 * @file
 * Definition (header) file for a directed network. Multiple
 * edges, between pairs of nodes, and self-loops are allowed.
*/

#ifndef S_DINET_INCORE_H
#define	S_DINET_INCORE_H

#include "S_Net_InCore.h"

namespace networkStructure {

  /**
   * \brief Implements the behavior of a directed network sequentially
   * processed in main memory.
   *
   * This class uses map or array-based lists for the edge
   * and node lists.  Multiple edges, between pairs of nodes, and
   * self-loops are allowed.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date January 28, 2014
   */

  class S_DiNet_InCore: public S_Net_InCore {
    public:
      /**
      * Constructor method
      */
       S_DiNet_InCore();

      /**
      * Constructor method. In this case a static, array based data structure is
      * used for node and edge lists
      * @param n Dimension of the node list array
      * @param m Dimension of the edge list array
      */
      S_DiNet_InCore(unsigned int n, unsigned int m);

      // Additional methods
       virtual Node* addNode(unsigned int n);

      /**
      * Adds an edge to the network. IMPORTANT: if the nodes with key1 and key2
      * do not exist the method creates them as SIMPLE dinodes (i.e., without
      * element inside). In turn, the edge created is also a SIMPLE edge. Here,
      * the method adds the edge to the out list of the origin node and to
      * the in list of the destiny node.
      * @param key1 An unsigned int identifying the origin node
      * @param key2 An unsigned int identifying the destiny node
      * @return The corresponding edge in the network
      *
      * The key of the edge is the sequential order in which the edges are
      * provided. So, the first edge added is labeled as 0, the second as 1 and
      * so on.
      */
       virtual Edge* addEdge (unsigned int key1, unsigned int key2);

      /**
      * Adds an edge to the network. The edge is formed by two nodes. This is
      * the method to use for adding general nodes (those containing, inside, an
      * element) to a network. Here, the method adds the edge to the out
      * list of the origin node and to the in list of the destiny node.
      * @param node1 A pointer to the origin node
      * @param node2 A pointer to the destiny node
      * @return The corresponding edge in the network
      */
       virtual Edge* addEdge (Node *node1, Node *node2);

      /**
      * Adds an edge to the network. IMPORTANT: if the nodes with key1 and key2
      * do not exist the method creates them as SIMPLE dinodes (i.e., without
      * element inside). In turn, the edge created is a GENERAL edge (one
      * containing, inside, an interaction). In a
      * directed network it adds the edge to the out list of the origin node and
      * to the in list of the destiny node.
      * @param key1 An unsigned int identifying the origin node
      * @param key2 An unsigned int identifying the destiny node
      * @param inter A pointer to an object of class Interaction associated to
      * the edge
      * @return The corresponding edge in the network
      *
      * The key of the edge is the sequential order in which the edges are
      * provided. So, the first edge added is labeled as 0, the second as 1 and
      * so on.
      */
       virtual Edge* addEdge (unsigned int key1, unsigned int key2,
                              Interaction *inter);

      /**
      * Adds a general edge to the network. The edge is formed by two nodes.
      * This is the method to use for adding general nodes (those containing,
      * inside, an element) to a
      * network. In a directed network it adds the edge to the out
      * list of the origin node and to the in list of the destiny node.
      * @param node1 A pointer to the origin node
      * @param node2 A pointer to the destiny node
      * @param inter A pointer to an object of class Interaction associated to
      * the edge
      * @return The corresponding edge in the network
      */
       virtual Edge* addEdge (Node *node1, Node *node2, Interaction *inter);

      /**
      * Here, directed networks, it returns an iterator to the adjacent input
      * nodes list
      * @param node A reference to a node object
      * @return An iterator to the adjacent nodes list
      */
       virtual Iterator <Node>* getAdjacentInNodes(Node* node);

      /**
      * Here, directed networks, it returns an iterator to the adjacent input
      * nodes list
      * @param key An unsigned int acting as key for the node
      * @return An iterator to the adjacent nodes list
      */
       virtual Iterator <Node>* getAdjacentInNodes(unsigned int key);

      /**
      * Destructor method
      */
      virtual ~S_DiNet_InCore();
  };

}

#endif	/* S_DINET_INCORE_H */

