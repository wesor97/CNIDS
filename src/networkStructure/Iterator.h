/*****************************************************************************
 *
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
 *
 * Release date: May 13, 2013
 *
 * Purpose: Abstract class (pure) acting as an interface defining the functional
 *          specification of an iterator over the elements in a container. The
 *          class applies the iterator pattern. The class is generic, accepting
 *          type T. T is the class the elements in the container belongs to.
 *
 * Structure of the class (public interface):
 *    void next (T*) : Moves to the next element in the container
 *    bool isDone () : Returns true if no more elements remain unprocessed in
 *                     the container
 *    T* current()   : Returns a pointer to the actual element in the container
 *
 *****************************************************************************/

/**
 * @file
 * Abstract class acting as an interface defining the functional
 * specification of a general iterator
 *
 * This class applies the iterator pattern
*/


#ifndef ITERATOR_H
#define	ITERATOR_H

namespace networkStructure {

  template <class T>

  /**
   * \brief INTERFACE (defined by an abstract class) specifying the behavior of
   * a general iterator
   *
   * This class represents an interface for iterators of any data structure. The
   * class applies the iterator pattern. The class is generic, accepting type T.
   * 
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date March 13, 2013
   */

  class Iterator{
    public:

      /**
      * Moves to the next element in the data structure
      */
      virtual void next()=0;

      /**
      * Determines if the data structure has been fully traversed
      * @return True if we are at the end of the data structure, False otherwise
      */
      virtual bool isDone()=0;

      /**
      * Returns the current element of the data structure
      * @return The current element of the data structure
      */
      virtual T* current()=0;

      /**
      * Destructor method
      */
      virtual ~Iterator () {};  // Non-pure virtual destructor

  };

}

#endif	/* ITERATOR_H */

