/*******************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: April 29, 2014
*
* Purpose: Definition and implementation for class template
*          (generic class) S_List_Array. This is a static list implemented with
*          an array and representing an abstraction of a container. The array
*          is resized automatically to accomodate additional elements
*          if its maximum capacity is reached.
*
* Comments: This class inherits from abstract base class ListNetwork.
*           IMPORTANT: The class assumes that the key of the elements
*                      (unsigned int) corresponds to the index in the array.
*******************************************************************************/

/**
 * @file
 * Definition and implementation file for class S_List_Array
*/


#ifndef S_LIST_ARRAY_H
#define	S_LIST_ARRAY_H

#include "ListNetwork.h"
#include "Iterator.h"


#include <iostream>

using namespace std;

namespace networkStructure {


  template <typename T>

  /**
   * \brief Defines a resizable, array-based associative container
   *
   * Definition and implementation for class template (generic class)
   * S_List_Array. This is a static list implemented with an array and
   * representing an abstraction of a container. The array
   * is resized automatically to accomodate additional elements
   * if its maximum capacity is reached.
   *
   *  IMPORTANT: The class assumes that the key of the elements (unsigned int)
   *             corresponds to the index in the array.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date April 29, 2014
   */

  class S_List_Array : public ListNetwork<T> {

    private:

      // Defining nested class for the iterator
      /**
      * Nested class representing an iterator for the static list
      *
      * @date April 29, 2014
      */
      class Iterator_S_List_Array : public Iterator <T> {
        private:
          T **aux;           ///< A pointer to the list(array)
          unsigned int pos ; ///< Current position in the list (array)
          unsigned int n ;   ///< Size of the list (array)
        public:
          /**
          * Constructor method
          * @param **l A pointer to the list (array) of pointers
          */
          Iterator_S_List_Array(T **l, unsigned int n0) {
            aux = l;
            n = n0;
            pos = 0;
            while (aux[pos] == nullptr){
              ++pos;
            }
          }

          /**
          * Moves to the next not null (nullptr) element in the list
          */
          void next(){
            ++pos;
            while (pos < n && aux[pos] == nullptr){
              ++pos;
            }
          }

          /**
          * Determines if we reached the end of the list
          */
          bool isDone(){
            return pos >= n;
          }

          /**
          * Returns the current element in the list
          */
          T * current(){
            return aux[pos];  // Assumes that it is a reference
          }
      };

      T **list;        ///< Array representing the list (array of pointers)
      unsigned int n;  ///< Size of the array
      unsigned int ne; ///< Number of elements in the list

    public:

      /**
      * Constructor method.
      * @param n The size of the list (array)
      */
      S_List_Array(unsigned int n) {
        list = new T*[n];
        this->n = n;
        ne = 0;
        eraseAll(); // Setting all list positions to nullptr
      }

      /**
      * Returns the number of not null (nullptr) elements in the static list
      * (array). Please, note that this is not necessarily equal to the size of
      * static list (some positions in the list can be set to null).
      * @return The number of elements in the list
      */
      unsigned int size(){
        return ne;
      }

      /**
      * Checks if the container is empty. Here, with an static list, it checks
      * if any of its elements is different from nullptr.
      * @return True if the container is empty, false otherwise
      */
      bool empty(){
        return ne == 0;
      }

      /**
      * Adds elements to the list. In this case, since the list is static, it
      * acts as a simple update method. The array
      * representing the list resizes to acommodate new elements when needed.
      * The default increase factor for the array size is a 20% of the original
      * size (i. e., new size = old size + 20% of the old size).
      * @param data A pointer to the element to add
      * @return The added element or the already existint element
      */
      T* add(T *data){
        unsigned int k = data->getKey();
        // If no room left in array
        if (k >= n) {
            unsigned int n0 = n, delta = n/5;
            if (delta == 0) delta = 1;
            n+= delta; // New maximun size (array size)
            if (n < k) n = k;   // Just in case
            T** newList = new T* [n];
            // Copying original matrix
            for (int i = 0; i < n0; ++i){
              newList[i] = list [i];
            }
            // Setting the rest of elements to nullptr
            for (int i = n0; i < n; ++i){
              newList[i] = nullptr;
            }
            delete list;
            list = newList;
        }

        if (list[k] == nullptr) {
          ++ne; //Increasing number of elements
          list[k] = data;
        } else {
          data = list [k];  // Existent element
        }

        return data;
      }

      /**
      * Finds the element with the given key in the static list. Returns nullptr
      * if the element does not exist in the container.
      * @param key The key (an unsigned int) of the element to look for
      * @return A pointer to the element with the given key
      */
      T* find (unsigned int key) {
        T *result = nullptr;
        if (key >=0 && key < n){
          result = list[key];
        }
        return result;
      }

      /**
      * Erases from the list the element with the given key
      * (an unsigned int). Here, since the list is static it does not really
      * remove an element of the list. What the method does is to assign the
      * corresponding list position to nullptr (C++11).
      * @param key The key (unsigned int) of the element to erase
      */
      void erase (unsigned int key) {
        if (key >=0 && key < n){
          list[key] = nullptr;
          --ne;
        }
      }

     /**
     * Erases all nodes of the list (but not the elements). Here, since the list
     * is static it does not really remove elements. What the method does is to
     * assign the list positions to nullptr (C++11).
     */
      void eraseAll() {
        for (unsigned int i=0; i < n; ++i) {
          list[i] = nullptr;
        }
        ne = 0;
      }

      /**
      * Checks the existence of the element with given key in the static list.
      * @param key The key (unsigned int) of the element to look for
      * @return True if an element with that key does exist, false otherwise
      */
      bool exists (unsigned int key){
        bool result = false;

        if (key >=0 && key < n){
          if (list[key] != nullptr) {
            result = (key == list[key]->getKey());
          }
        }
        return result;
      }

      // Creating iterator to the list
      Iterator<T>* iterator(){
        return new Iterator_S_List_Array(list, n); //Creating iterator in the
      }                                            // heap

      /**
      * Destructor
      */
      virtual ~S_List_Array(){
        delete list;
      }

  };

}

#endif	/* S_LIST_ARRAY_H */

