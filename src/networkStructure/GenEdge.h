/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 25, 2014
*
* Purpose: Definition (header) for class GenEdge
*
*****************************************************************************/

/**
 * @file
 * Definition (header) file for class GenEdge representing the basic structure
 * and behavior of a general edge (one with an interaction associated) in a
 * network.
*/

#ifndef GENEDGE_H
#define	GENEDGE_H


#include "SimpleEdge.h"

namespace networkStructure {


  /**
   * \brief Defines a general edge in a network
   *
   * This class represents the basic structure and behavior of a general
   * edge (one with an interaction associated) in a network. A string is used as
   * key to identify the node.
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 25, 2014
   */


  class GenEdge : public SimpleEdge {
    protected:
       Interaction *inter; ///< Element associated to the edge

    public:

      /**
      * Constructor method
      * @param n1 A pointer to the first node of the edge
      * @param n2 A pointer to the second node of the edge
      * @param inter A pointer to the interaction associated to the edge
      * @param key An unsigned int identifying the edge
      */
      GenEdge (Node *n1, Node *n2, Interaction *inter, unsigned int key);

      /**
      * Returns the key (unique unsigned int) identifying the edge
      * @return The key (unique unsigned int) of the edge
      */
      unsigned int getKey();

      /**
      * Returns A pointer to the interaction associated to the edge
      * @return A pointer to the interaction associated to the edge
      */
      Interaction* getInteraction();

      // Destructor method
      /**
      * Destructor method
      */
      virtual ~GenEdge();
  };

}

#endif	/* GENEDGE_H */

