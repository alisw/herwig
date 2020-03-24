// -*- C++ -*-
//
// VFFDecayer.h is a part of Herwig - A multi-purpose Monte Carlo event generator
// Copyright (C) 2002-2019 The Herwig Collaboration
//
// Herwig is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef HERWIG_VFFDecayer_H
#define HERWIG_VFFDecayer_H
//
// This is the declaration of the VFFDecayer class.
//

#include "GeneralTwoBodyDecayer.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Helicity/Vertex/Vector/FFVVertex.h"
#include "ThePEG/Helicity/Vertex/Vector/VVVVertex.h"

namespace Herwig {
using namespace ThePEG;
using Helicity::FFVVertexPtr;

/** \ingroup Decay
 * The VFFDecayer class implements the decay of a vector
 * to 2 fermions in a general model. It holds an FFVVertex pointer
 * that must be typecast from the VertexBase pointer held in 
 * GeneralTwoBodyDecayer. It implents the virtual functions me2() and
 * partialWidth(). 
 *
 * @see GeneralTwoBodyDecayer
 */
class VFFDecayer: public GeneralTwoBodyDecayer {

public:
  
  /**
   * The default constructor.
   */
  VFFDecayer() {}

public:

  /** @name Virtual functions required by the Decayer class. */
  //@{
  /**
   * Return the matrix element squared for a given mode and phase-space channel.  
   * @param ichan The channel we are calculating the matrix element for.
   * @param part The decaying Particle.
   * @param decay The particles produced in the decay.
   * @param meopt Option for the matrix element
   * @return The matrix element squared for the phase-space configuration.
   */
  virtual double me2(const int ichan, const Particle & part,
		     const ParticleVector & decay, MEOption meopt) const;
  
  /**
   * Function to return partial Width
   * @param inpart The decaying particle.
   * @param outa One of the decay products.
   * @param outb The other decay product.
   */
  virtual Energy partialWidth(PMPair inpart, PMPair outa, 
			      PMPair outb) const;

  /**
   *  Has a POWHEG style correction
   */
  virtual POWHEGType hasPOWHEGCorrection()  {
    POWHEGType output = FSR;
    for(auto vertex : vertex_) {
      if(vertex->orderInAllCouplings()!=1) {
	output = No;
	break;
      }
    }
    return output;
  }

  /**
   *  Three-body matrix element including additional QCD radiation
   */
  virtual double threeBodyME(const int , const Particle & inpart,
			     const ParticleVector & decay,
			     ShowerInteraction inter, MEOption meopt);

  /**
   * Indentify outgoing vertices for the fermion and antifermion
   */
  void identifyVertices(const int iferm, const int ianti,
			const Particle & inpart, const ParticleVector & decay,
			AbstractFFVVertexPtr & abstractOutgoingVertexF, 
			AbstractFFVVertexPtr & abstractOutgoingVertexA,
			ShowerInteraction inter);

  /**
   *  Set the information on the decay
   */
  virtual void setDecayInfo(PDPtr incoming, PDPair outgoing,
			    vector<VertexBasePtr>,
			    map<ShowerInteraction,VertexBasePtr> &,
			    const vector<map<ShowerInteraction,VertexBasePtr> > &,
			    map<ShowerInteraction,VertexBasePtr>);
  //@}

public:

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
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

private:
  
  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  VFFDecayer & operator=(const VFFDecayer &) = delete;

private:

  /**
   *  Abstract pointer to AbstractFFVVertex
   */
  vector<AbstractFFVVertexPtr> vertex_;

  /**
   * Pointer to the perturbative vertex
   */
  vector<FFVVertexPtr> perturbativeVertex_;

  /**
   *  Abstract pointer to AbstractVVVVertex for QCD radiation from incoming vector
   */
  map<ShowerInteraction,AbstractVVVVertexPtr> incomingVertex_;

  /**
   *  Abstract pointer to AbstractFFVVertex for QCD radiation from outgoing (anti)fermion
   */
  map<ShowerInteraction,AbstractFFVVertexPtr> outgoingVertex1_;

  /**
   *  Abstract pointer to AbstractFFVVertex for QCD radiation from outgoing (anti)fermion
   */
  map<ShowerInteraction,AbstractFFVVertexPtr> outgoingVertex2_;

  /**
   *  Spin density matrix 
   */
  mutable RhoDMatrix rho_;

  /**
   *  Polarization vectors for the decaying particle
   */
  mutable vector<VectorWaveFunction> vectors_;

  /**
   *  Spinors for the decay products 
   */
  mutable vector<SpinorWaveFunction> wave_;

  /**
   *  Barred spinors for the decay products
   */
  mutable vector<SpinorBarWaveFunction> wavebar_;
 /**
   *  Spin density matrix for 3 body decay
   */
  mutable RhoDMatrix rho3_;

  /**
   *  Scalar wavefunction for 3 body decay
   */
  mutable vector<VectorWaveFunction> vector3_;

  /**
   *  Spinor wavefunction for 3 body decay
   */
  mutable vector<SpinorWaveFunction> wave3_;

  /**
   *  Barred spinor wavefunction for 3 body decay
   */
  mutable vector<SpinorBarWaveFunction> wavebar3_;

    /**
   *  Vector wavefunction for 3 body decay
   */
  mutable vector<VectorWaveFunction> gluon_;

};

}

#endif /* HERWIG_VFFDecayer_H */
