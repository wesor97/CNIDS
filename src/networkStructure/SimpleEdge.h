/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 25, 2014
*
* Purpose: Definition (header) file for class SimpleEdge
*
*****************************************************************************/

/**
 * @file
 * Definition (header) file for class SimpleEdge representing the basic
 * structure and behavior of a simple edge (one without any interaction
 * associated) in a network.
*/


#ifndef SIMPLEEDGE_H
#define	SIMPLEEDGE_H

#include "Edge.h"

#include "Node.h"
#include "S_List_Map.h"

namespace networkStructure {

  /**
   * \brief Defines a simple edge in a network
   *
   * This class represents the basic structure and behavior of a simple
   * edge (one without any interaction associated) in a network. An unsigned int
   * is used as key to identify the edge.
   *
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 25, 2014
   */


  class SimpleEdge : public Edge {
    protected:
      unsigned int key; ///< Unique key (an unsigned int) of the edge
          Node *origin; ///< First node (origin if directed) of the edge
         Node *destiny; ///< Second node (destiny if directed) of the edge
    public:

      /**
      * Constructor method
      * @param n1 A pointer to the first node of the edge
      * @param n2 A pointer to the second node of the edge
      * @param key An unsigned int identifying the edge
      */
      SimpleEdge (Node *n1, Node *n2, unsigned int key);


      // Accessor methods

      /**
      * Returns a pointer to the first node of the edge
      * @return A pointer to the first node of the edge
      */
      Node* getOrigin();

      /**
      * Returns pointer to the second node of the edge
      * @return A pointer to the second node of the edge
      */
      Node* getDestiny();

      /**
      * Returns the key (unsigned int) identifying the edge
      * @return The key (unique unsigned int) of the edge
      */
      virtual unsigned int getKey();

      /**
      * Returns the interaction associated to the edge. In this class, it
      * returns nullptr (C++11)
      * @return A pointer to the interaction associated to the edge. In this
      * class, it returns nullptr (C++11)
      */
      virtual Interaction* getInteraction();

      /**
      * Sets first node of the edge
      * @param *node A pointer to the first node of the edge
      */
      void setOrigin(Node *node);

      /**
      * Sets second node of the edge
      * @param *node A pointer to the second node of the edge
      */
      void setDestiny(Node *node);

      // Additional methods

      /**
      * Gets node opposite (on this edge) to the one provided. If the node
      * does not belong to this edge it returns nullptr (C++11)
      * @param *node A pointer to the node which opposite we want to know
      * @return A pointer to the node opposite to the one introduced or nullptr
      * if this last does not exist
      */
      Node *getOpposite(Node *node);

      /**
      * Checks if the current and the given edges are the same as defined by the
      * key
      * @param node A pointer to an edge object
      * @return True if both edges are equal, false otherwise
      */
      bool equals(Edge *edge);

      // Destructor method
      /**
      * Destructor method
      */
      virtual ~SimpleEdge();
  };

}

#endif	/* SIMPLEEDGE_H */

