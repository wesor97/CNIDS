/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 8, 2014
*
* Purpose: Definition (header) for class DiGenNode
*
*****************************************************************************/


/**
 * @file
 * Definition (header) file for class DiGenNode
*/


#ifndef DIGENNODE_H
#define	DIGENNODE_H

#include "DiNode.h"

namespace networkStructure {

  /**
   * \brief Defines a general node in a directed network
   *
   * Defines a general node (one with an element associated) in a directed
   * network (a directed network has adjacency lists for output and input edges)
   *
   * This class represents the basic structure and behavior of a general node
   * in a directed network.
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date April 8, 2014
   */

  class DiGenNode: public DiNode {
    protected:
      Element* element; ///< Element contained in the node

    public:

      /**
      * Constructor method
      * @param element A pointer to the element contained in the node
      * @param n An unsigned integer identifying the node
      */
      DiGenNode(Element* element, unsigned int n);

      /**
      * Accessor method.
      * Returns a pointer to the element contained in the node
      * @return A pointer to the element contained in the node
      */
      Element* getElement();


      // Destructor method
      /**
      * Destructor method. Erases all edges from the
      * out adjacency list and the list itself
      */
      ~DiGenNode();
  };

}

#endif	/* DIGENNODE_H */

