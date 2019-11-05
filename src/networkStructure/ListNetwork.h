/*****************************************************************************
 *
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
 *
 * Release date: May 13, 2013
 *
 * Purpose: Abstract class (pure) acting as an interface defining the functional
 *          specification of the container used in networks
 *          (for nodes or edges). The class is generic, accepting type
 *          T. T is the class the elements in the container belongs to.
 *
 *****************************************************************************/


/**
 * @file
 * INTERFACE (defined by an abstract class) defining the
 * functional specification of the container used in networks
 * (for nodes or edges). The class is generic, accepting type
 * T. T is the class the elements in the container belongs to.
*/


#ifndef LISTNETWORK_H
#define	LISTNETWORK_H

# include "Iterator.h"

namespace networkStructure {


  template <class T>

  /**
   * \brief INTERFACE (defined by an abstract class) specifying the functional
   * behavior of the container used in networks
   * (for nodes or edges).
   *
   * The class is generic, accepting type T.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universiddd 4, 13004-Ciudad Real. SPAIN
   * @date May 13, 2013
   */


  class ListNetwork {
    public:

      /**
      * Returns the number of elements in the container
      * @return The number of elements in the container
      */
      virtual unsigned int size()=0;

      /**
      * Adds element, if it does not exist, to the container
      * @param element A pointer to the element to add
      * @return The element added or the one in the contaniner if this already
      * exists
      */
      virtual T* add(T* element)=0;

      /**
      * Checks if the container is empty
      * @return True if the container is empty, false otherwise
      */
      virtual bool empty()=0;

      /**
      * Finds the element with the given key. Returns nullptr if the element
      * does not exist in the container.
      * @param key The key (an unsigned int) of the element to look for
      * @return A pointer to the element with the given key
      */
      virtual T* find(unsigned int key)=0;

      /**
      * Erases element with the given key (an unsigned int)
      * @param key The key (unsigned int) of the element to erase
      */
      virtual void erase(unsigned int key)=0;

      /**
      * Erases the container (fully)
      */
      virtual void eraseAll()=0;

      /**
      * Checks the existence of the element with given key
      * @param key The key (unsigned int) of the element to look for
      * @return True if an element with that key does exist, false otherwise
      */
      virtual bool exists(unsigned int key)=0;

      /**
      * Returns an iterator to the elements in the container
      * @return An iterator to the elements in the container
      */
      virtual Iterator<T>* iterator()=0;

      /**
      * Destructor
      */
      virtual ~ListNetwork(){}; // Non-pure virtual destructor
  };

}

#endif	/* LISTNETWORK_H */

