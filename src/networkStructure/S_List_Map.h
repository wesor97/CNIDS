/*******************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: May 13, 2013
*
* Purpose: Definition (header) and implementation for class template
*          (generic class) S_List_Map. This class uses the C++ STL
*          map as basic data structure. This is an adapter class (applies the
*          Adapter design pattern) representing an abstraction of a container
*
*
* Comments: This class inherits from abstract base class ListNetwork.
*           IMPORTANT: The class works sequentially and uses a map of REFERENCES
*******************************************************************************/

/**
 * @file
 * Implementation file for class S_List_Map
*/


# ifndef S_LIST_MAP
# define S_LIST_MAP

# include <map>
# include "Iterator.h"
# include "ListNetwork.h"
# include "FSBAllocator.h"

using namespace std;

namespace networkStructure {


  template <typename T>
  /**
   * \brief Defines a map-based associative container
   *
   * Implementation of class template
   * (generic class) S_List_Map. This class uses the C++ STL
   * map as basic data structure. This is an adapter class (applies the
   * Adapter design pattern) representing an abstraction of a container.
   *
   *  IMPORTANT: The class works sequentially and uses a map of REFERENCES. To
   *             improve the performance of the map the FSBAllocator developed
   *             by Juha Nieminen is used, see:
   *             http://warp.povusers.org/FSBAllocator/
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date May 13, 2013
   */

  class S_List_Map: public ListNetwork<T> {
    private:
      typedef typename map<unsigned int, T*, less<unsigned int>,
      FSBAllocator<pair<unsigned int, T*>>>::iterator iteratorMap; // Iterator

      map <unsigned int, T*, less<unsigned int>,
          FSBAllocator<pair<unsigned int, T*>>> *lista;
    public:

    // Methods of the class
      S_List_Map(){
        lista=new map<unsigned int, T*, less<unsigned int>,
              FSBAllocator<pair<unsigned int, T*>>>;
      }

      // Returns the number of elements in the list
      unsigned int size(){
        return lista->size();
      }

      // Adds a new element to the list returning the object added (or the one
      // in the list if it already exists)
      T* add(T *element){
        pair<iteratorMap, bool> result;
        // The insert method checks if the element already exists
        result = lista->insert(pair<unsigned int, T*>(element->getKey(),
                                                      element));
        if (!result.second) {
          return result.first->second;
        } else {
          return element;
        }
      }

      // Checks if the container is empty
      bool empty(){
        return lista->empty();
      }

      // Returns nullptr if the element is not in the container. Overload
      T* find(unsigned int key){
        iteratorMap q=lista->find(key);
        if (q==lista->end()){
          return nullptr;
        }
        return q->second;
      }

      // Removes an element from the container
      void erase(unsigned int key){
        lista->erase(key);
      }

      // Removes all the element from the container
      void eraseAll(){
        // We delete the references to the elements in the list
        lista->clear();
      }

      // Determines if the element exists in the container
      bool exists(unsigned int key){
        return(lista->count(key)==1); // True if the element is found
      }                               // (the N id is unique)

      // Returns an iterator to the elements in the container
      Iterator<T> *iterator(){
        return new Iterator_S_List_Map(lista); // Creating iterator in the heap
      }

      // Destructor method. Frees allocated memory
      ~S_List_Map(){
        // We delete the references to the elements in the list
        lista->clear();
        // Now we delete the reference to the list
        delete lista;
      }

    private:
      // Defining nested class for the iterator
      class Iterator_S_List_Map: public Iterator <T> {
        private:
          iteratorMap it;
          map <unsigned int, T*, less<unsigned int>,
               FSBAllocator<pair<unsigned int, T*>>> *list;
        public:
          Iterator_S_List_Map(map <unsigned int, T*, less<unsigned int>,
                              FSBAllocator<pair<unsigned int, T*>>> *l) {
            list=l;
            it=list->begin();
          }
          void next(){
            ++it;
          }
          bool isDone(){
            return it==list->end();
          }
          T * current(){
            return (it->second);  // Assumes that second is a reference
          }
      };

  };

}

# endif

