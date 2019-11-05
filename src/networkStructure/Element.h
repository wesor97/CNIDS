/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: May 4, 2014
*
* Purpose: Class defining a basic element associated to nodes in a network.
*          This class allows to keep track of the visited nodes in the network.
*
*****************************************************************************/


/**
 * @file
 * Basic element to associate to a node in a network.
 */


#ifndef ELEMENT_H
#define	ELEMENT_H

namespace networkStructure {

  /**
   * \brief Defines a simple element to associate to a node
   *
   * This sample element allows
   * to keep track of the visited nodes in a network. Useful for traversing and
   * searching algorithms such as Breath-First-Search (BFS)
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universiddad 4, 13004-Ciudad Real. SPAIN
   * @date May 4, 2014
   */

  class Element {
    private:
      bool visited; ///< Variable to identify a node as visited
    public:
      /**
       * Constructor method. By default the element is not visited
       */
      Element() {
        visited = false;
      }
      /**
       * Sets the value of the visited variable
       * @param v The new value for the visited variable
       */
      void setVisited(bool v) {
        visited = v;
      }

      /**
       * Returns the current value of the visited variable
       * @return The visited variable
       */
      bool getVisited(){
        return visited;
      }

      /**
       * Destructor method
       */
      virtual ~Element() {}
  };

}

#endif	/* ELEMENT_H */

