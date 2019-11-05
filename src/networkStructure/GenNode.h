/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: March 24, 2014
*
* Purpose: Definition (header) for class GenNode
*
*****************************************************************************/

/**
 * @file
 * Definition (header) file for class GenNode representing the basic structure
 * and behavior of a general node (one with an element associated) in a network.
*/

#ifndef GENNODE_H
#define	GENNODE_H

#include "SimpleNode.h"

namespace networkStructure {

  /**
   * \brief Defines a general node in an undirected network
   *
   * This class represents the basic structure and behavior of a general
   * node (one with an element associated) in a network. An unsigned integer is
   * used as key to identify the node.
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 24, 2014
   */


  class GenNode : public SimpleNode {
    protected:
      Element* element; ///< Element contained in the node

    public:

      /**
      * Constructor method
      * the key)
      * @param element A pointer to the element contained in the node
      * @param n An unsigned integer identifying the node (will be stored as
      */
      GenNode(Element* element, unsigned int n);

      /**
      * Accessor method.
      * Returns a pointer to the element contained in the node
      * @return A pointer to the element contained in the node
      */
      Element* getElement();

      // Destructor method
      /**
      * Destructor method. Erases the present element, all edges from the
      * adjacency list and the list itself
      */
      virtual ~GenNode();
  };

}

#endif	/* GENNODE_H */

