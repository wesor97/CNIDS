/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: January 29, 2014
*
* Purpose: Abstract class (pure) acting as an interface defining the functional
*          specification for any network.
*
*****************************************************************************/

/**
 * @file
 * Abstract class acting as an interface defining the functional
 * specification of any network. Multiple edges, between pairs of nodes, and
 * self-loops are allowed.
*/


#ifndef NETWORK_H
#define	NETWORK_H


# include "ListNetwork.h"
# include "Node.h"
# include "Edge.h"

namespace networkStructure {

  /**
   * \brief INTERFACE (defined by an abstract class) specifying the behavior of
   * any network. Multiple edges, between pairs of nodes, and
   * self-loops are allowed.
   *
   * This class represents an interface for the basic behavior of any network.
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 18, 2013
   */

  class Network {
    protected:
      ListNetwork <Node> *lNodes; ///< Node list
      ListNetwork <Edge> *lEdges; ///< Edge list
    public:
      // Accessor methods

      /**
      * Gets the number of nodes in the network
      * @return The number of nodes
      */
      virtual unsigned int getNNodes()=0;

      /**
      * Gets the number of edges in the network
      * @return The number of edges
      */
      virtual unsigned int getNEdges()=0;

      /**
      * Gets the maximum node degree in the network
      * @return The maximum node degree in the network
      */
      virtual unsigned int getKMax()=0;

      /**
      * Gets the minimum node degree in the network
      * @return The minimum node degree in the network
      */
      virtual unsigned int getKMin()=0;

      // Additional methods

      /**
      * Adds a node to the network. The node can be simple or
      * general (i. e., containing, inside, an element).
      * @param node A pointer to a node object
      * @return The corresponding node in the network
      */
      virtual Node* addNode(Node* node)=0;

      /**
      * Adds a simple node to the network
      * @param n An unsigned integer identifying a node object
      * @return The corresponding node in the network
      */
      virtual Node* addNode(unsigned int n)=0;

      /**
      * Adds an existing edge to the network. The edge can be simple or general
      * (with an interaction inside it) and formed by simple or
      * general (i. e., containing, inside, an element) nodes. In a directed
      * network it adds the edge to the out list of the origin node and to the
      * in list of the destiny node.
      * @param edge A pointer to an edge object
      * @return The corresponding edge in the network
      */
      virtual Edge* addEdge(Edge* edge)=0;

      /**
      * Adds an edge to the network. IMPORTANT: if the nodes with key1 and key2
      * do not exist the method creates them as SIMPLE nodes (i.e., without
      * element inside). In turn, the edge created is also a SIMPLE edge. In a
      * directed network it adds the edge to the out list of the origin node and
      * to the in list of the destiny node.
      * @param key1 An unsigned int identifying the origin node
      * @param key2 An unsigned int identifying the destiny node
      * @return The corresponding edge in the network
      *
      * The key of the edge is the sequential order in which the edges are
      * provided. So, the first edge added is labeled as 0, the second as 1 and
      * so on.
      */
       virtual Edge* addEdge (unsigned int key1, unsigned int key2)=0;

      /**
      * Adds a simple edge to the network. The edge is formed by two nodes. This
      * is the method to use for adding general nodes (those containing, inside,
      * an element) to a network. In a directed network it adds the edge to the
      * out list of the origin node and to the in list of the destiny node.
      * @param node1 A pointer to the origin node
      * @param node2 A pointer to the destiny node
      * @return The corresponding edge in the network
      */
       virtual Edge* addEdge (Node *node1, Node *node2)=0;


      /**
      * Adds an edge to the network. IMPORTANT: if the nodes with key1 and key2
      * do not exist the method creates them as SIMPLE nodes (i.e., without
      * element inside). In turn, the edge created is a GENERAL edge (one
      * containing, inside, an interaction). In a
      * directed network it adds the edge to the out list of the origin node and
      * to the in list of the destiny node.
      * @param key1 An unsigned int identifying the origin node
      * @param key2 An unsigned int identifying the destiny node
      * @param inter An object of class Interaction associated to the edge
      * @return The corresponding edge in the network
      *
      * The key of the edge is the sequential order in which the edges are
      * provided. So, the first edge added is labeled as 0, the second as 1 and
      * so on.
      */
       virtual Edge* addEdge (unsigned int key1, unsigned int key2,
                              Interaction *inter)=0;

      /**
      * Adds a general edge to the network. The edge is formed by two nodes.
      * This is the method to use for adding general nodes
      * (those containing, inside,
      * an element) and general edges (those containing an interaction) to a
      * network. In a directed network it adds the edge to the out
      * list of the origin node and to the in list of the destiny node.
      * @param node1 A pointer to the origin node
      * @param node2 A pointer to the destiny node
      * @param inter An object of class Interaction associated to the edge
      * @return The corresponding edge in the network
      */
       virtual Edge* addEdge (Node *node1, Node *node2, Interaction *inter)=0;

      /**
      * Returns a given node from the network (nullptr if the node does not
      * exist)
      * @param key The unsigned int acting as a key for the node
      * @return The node corresponding to the key provided
      */
      virtual Node* getNode(unsigned int key)=0;

      /**
      * Returns a given Edge from the network (nullptr if the Edge does not
      * exist)
      * @param key The unsigned int acting as a key for the Edge
      * @return The Edge corresponding to the key provided
      */
      virtual Edge* getEdge(unsigned int key)=0;

      /**
      * Erases a node from the network
      * @param node A reference to a node object
      */
      virtual void eraseNode(Node* node)=0;

      /**
      * Erases a node from the network
      * @param key An unsigned int acting as key for the node
      */
      virtual void eraseNode(unsigned int key)=0;

      /**
      * Erases an edge from the network
      * @param edge A reference to an edge object
      */
      virtual void eraseEdge(Edge* edge)=0;

      /**
      * Erases an edge from the network
      * @param key An unsigned int acting as key for the edge
      */
      virtual void eraseEdge(unsigned int key)=0;

      // Iterator methods

      /**
      * Returns an iterator to the adjacent nodes list. In a directed network
      * returns the output nodes list
      * @param node A reference to a node object
      * @return An iterator to the adjacent nodes list
      */
      virtual Iterator <Node>* getAdjacentNodes(Node* node)=0;

      /**
      * Returns an iterator to the adjacent nodes list. In a directed network
      * returns the output nodes list
      * @param key An unsigned int acting as key for the node
      * @return An iterator to the adjacent nodes list
      */
      virtual Iterator <Node>* getAdjacentNodes(unsigned int key)=0;

      /**
      * Returns an iterator to the adjacent input nodes list. In an undirected
      * network returns the adjacent nodes list (same as the getAdjacentNodes
      * method).
      * @param node A reference to a node object
      * @return An iterator to the adjacent nodes list
      */
      virtual Iterator <Node>* getAdjacentInNodes(Node* node)=0;

      /**
      * Returns an iterator to the adjacent input nodes list. In an undirected
      * network returns the adjacent nodes list (same as the getAdjacentNodes
      * method).
      * @param key An unsigned int acting as key for the node
      * @return An iterator to the adjacent nodes list
      */
      virtual Iterator <Node>* getAdjacentInNodes(unsigned int key)=0;

      /**
      * Returns an iterator to the node list
      * @return An iterator to the node list
      */
      virtual Iterator <Node>* iteratorNodes()=0;

      /**
      * Returns an iterator to the edge list
      * @return An iterator to the edge list
      */
      virtual Iterator <Edge>* iteratorEdges()=0;

      virtual ~Network(){}; // Virtual (nonpure) destructor
  };

}

#endif	/* NETWORK_H */

