// -*- C++ -*-
//
// ADDModelVVGRVertex.h is a part of Herwig - A multi-purpose Monte Carlo event generator
// Copyright (C) 2002-2019 The Herwig Collaboration
//
// Herwig is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef HERWIG_ADDModelVVGRVertex_H
#define HERWIG_ADDModelVVGRVertex_H
//
// This is the declaration of the ADDModelVVGRVertex class.

#include "ThePEG/Helicity/Vertex/Tensor/VVTVertex.h"
#include "ADDModel.h"

namespace Herwig {
using namespace ThePEG;

/** \ingroup Helicity
 * 
 *  This is the implementation of the vector-vector-graviton vertex for
 *  the ADD model
 * 
 *  @see VVTVertex
 *  @see VertexBase
 */
class ADDModelVVGRVertex: public VVTVertex {
  
public:
  
  /**
   * Default constructor.
   */
  ADDModelVVGRVertex();
  
  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}
  
  /**
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();
  
  /**
   * Calculate the couplings. 
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param part1 The ParticleData pointer for the first  particle.
   * @param part2 The ParticleData pointer for the second particle.
   * @param part3 The ParticleData pointer for the third  particle.
   */
  virtual void setCoupling(Energy2 q2,tcPDPtr part1,tcPDPtr part2,tcPDPtr part3);

protected:
  
  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const {return new_ptr(*this);}

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const {return new_ptr(*this);}
  //@}

protected:
  
  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit();

  /**
   * Calculate the propagator for a diagram.
   * @param iopt The option for the Breit-Wigner shape
   * @param q2 The scale
   * @param part The ParticleData pointer for the off-shell particle.
   * @param mass The mass if not to be taken from the ParticleData object
   * @param width The width if not to be taken from the ParticleData object
   */
  virtual Complex propagator(int iopt, Energy2 q2,tcPDPtr part,
			     Energy mass=-GeV, Energy width=-GeV);
    
private:
  
  /**
   * Private and non-existent assignment operator.
   */
  ADDModelVVGRVertex & operator=(const ADDModelVVGRVertex &) = delete;

  /**
   * The coupling.
   */
  InvEnergy kappa_;

  /**
   *  Mass ratio for the propagator
   */
  Energy r_;
  
};
}

#endif /* HERWIG_ADDModelVVGRVertex_H */
