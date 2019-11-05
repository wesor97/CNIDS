/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 25, 2014
*
* Purpose: Abstract class (pure) acting as an interface defining defining the
*          functional specification of an edge in a network
*
*****************************************************************************/

/**
 * @file
 * INTERFACE (defined by an abstract class) defining the
 * functional specification of an edge in a network.
*/


#ifndef EDGE_H
#define	EDGE_H

#include "Interaction.h"

namespace networkStructure {

  class Node;  // Forward declaration

  /**
   * \brief Defines a simple edge in a network
   *
   * INTERFACE (defined by an abstract class) defining the behavior of an edge
   * in a network. An unsigned int is used as key to identify the edge.
   *
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 25, 2014
   */


  class Edge {
    public:

      // Accessor methods

      /**
      * Returns a pointer to the first node of the edge
      * @return A pointer to the first node of the edge
      */
      virtual Node* getOrigin() = 0;

      /**
      * Returns pointer to the second node of the edge
      * @return A pointer to the second node of the edge
      */
      virtual Node* getDestiny() = 0;

      /**
      * Returns the key (unsigned int) identifying the edge
      * @return The key (unique unsigned int) of the edge
      */
      virtual unsigned int getKey() = 0;

      /**
      * Returns the interaction associated to the edge
      * @return A pointer to the interaction associated to the edge
      */
      virtual Interaction* getInteraction() = 0;

      /**
      * Sets the first node of the edge
      * @param *node A pointer to the first node of the edge
      */
      virtual void setOrigin(Node *node) = 0;

      /**
      * Sets the second node of the edge
      * @param *node A pointer to the second node of the edge
      */
      virtual void setDestiny(Node *node) = 0;

      // Additional methods

      /**
      * Gets node opposite (on this edge) to the one provided. If the node
      * does not belong to this edge the method returns nullptr (C++11)
      * @param *node A pointer to the node which opposite we want to know
      * @return A pointer to the node opposite to the one introduced or nullptr
      * if this last does not exist
      */
      virtual Node *getOpposite(Node *node) = 0;

      /**
      * Checks if the current and the given edges are the same as defined by the
      * key
      * @param node A pointer to an edge object
      * @return True if both edges are equal, false otherwise
      */
      virtual bool equals (Edge *edge) = 0;

      // Destructor method
      /**
      * Destructor method
      */
      virtual ~Edge() {};
  };

}

#endif	/* EDGE_H */

