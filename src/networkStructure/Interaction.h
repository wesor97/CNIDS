/*****************************************************************************
*
* Authors: SciCom research group-E.S.I. Universidad de Castilla-La Mancha
*          Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
*
* Release date: May 4, 2014
*
* Purpose: Class defining a basic interaction associated to edges in a network.
*          This class allows to set a weight to the edges of the network.
*
*****************************************************************************/

/**
 * @file
 * Basic interaction to associate to an edge in a network.
 */


#ifndef INTERACTION_H
#define	INTERACTION_H

namespace networkStructure {

  /**
   * \brief Defines a simple interaction to associate to an edge
   *
   * This sample
   * interaction allows to set a weight to the edges of a network. Useful for
   * algorithms such as Dijkstra's shortest path algorithm.
   *
   * @author SciCom research group-E.S.I. Universidad de Castilla-La Mancha.
   *         Paseo de la Universidad 4, 13004-Ciudad Real. SPAIN
   * @date May 4, 2014
   */


  class Interaction {
    private:
      double weight; ///< Weight associated to the edge
    public:
      /**
       * Constructor method
       * @param w The weight associated to the edge
       */
      Interaction (double w) {
        weight = w;
      }
      /**
       * Changes the value of the weight associated to the edge
       * @param w The new value of the weight
       */
      void setWeight(double w) {
        weight = w;
      }

      /**
       * Return the current value of the weight associated to the edge
       * @return The current value of the weight associated to the edge
       */
      double getWeight() {
        return weight;
      }

      /**
       * Destructor method
       */
      virtual ~Interaction() { }
  };

}

#endif	/* INTERACTION_H */

