// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the IFqx2gqxDipoleKernel class.
//

#include "IFqx2gqxDipoleKernel.h"
#include "ThePEG/Interface/ClassDocumentation.h"


#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace Herwig;

IFqx2gqxDipoleKernel::IFqx2gqxDipoleKernel() 
  : DipoleSplittingKernel() {}

IFqx2gqxDipoleKernel::~IFqx2gqxDipoleKernel() {}

IBPtr IFqx2gqxDipoleKernel::clone() const {
  return new_ptr(*this);
}

IBPtr IFqx2gqxDipoleKernel::fullclone() const {
  return new_ptr(*this);
}

bool IFqx2gqxDipoleKernel::canHandle(const DipoleIndex& ind) const {
  return
  useThisKernel() &&
    abs(ind.emitterData()->id()) < 6  &&
    ind.emitterData()->mass() == ZERO &&
    ind.spectatorData()->mass() == ZERO &&
    ind.initialStateEmitter() && !ind.initialStateSpectator();
}

bool IFqx2gqxDipoleKernel::canHandleEquivalent(const DipoleIndex& a,
					       const DipoleSplittingKernel& sk,
					       const DipoleIndex& b) const {

  assert(canHandle(a));

  if ( !canHandle(b) )
    return false;

  return
    a.emitterData() == b.emitterData() &&
    emitter(a) == sk.emitter(b) &&
    a.emitterPDF() == b.emitterPDF();

}


tcPDPtr IFqx2gqxDipoleKernel::emitter(const DipoleIndex&) const {
  return getParticleData(ParticleID::g);
}

tcPDPtr IFqx2gqxDipoleKernel::emission(const DipoleIndex& ind) const {
  return ind.emitterData()->CC();
}

tcPDPtr IFqx2gqxDipoleKernel::spectator(const DipoleIndex& ind) const {
  return ind.spectatorData();
}

double IFqx2gqxDipoleKernel::evaluate(const DipoleSplittingInfo& split) const {

  double ret = alphaPDF(split);

  double z = split.lastZ();
  double ratio = sqr(split.lastPt()/split.scale());

  double rho = 1. - 4.*ratio*z*(1.-z)/sqr(1.-z+ratio);
  double x = 0.5*((1.-z+ratio)/ratio)*(1.-sqrt(rho));

  ret *= .5 * ( 1.-2.*x*(1.-x)  );

  return ret > 0. ? ret : 0.;

}

vector< pair<int, Complex> >
IFqx2gqxDipoleKernel::generatePhi(const DipoleSplittingInfo&, const RhoDMatrix&) const {

  // No dependence on the spin density matrix,
  // dependence on off-diagonal terms cancels.
  return {{ {0, 1.} }};
}

DecayMEPtr IFqx2gqxDipoleKernel::matrixElement(const DipoleSplittingInfo& dInfo) const {

  double z = dInfo.lastZ();

  // Altarelli-Parisi spin-indexed kernels:
  double v_AP_ppm = z;
  double v_AP_mpm = (1.-z);
  
  double v_AP_mmp = -v_AP_ppm;
  double v_AP_pmp = -v_AP_mpm;
    
  // Construct the (phi-dependent) spin-unaveraged splitting kernel
  DecayMEPtr kernelPhiDep
    (new_ptr(TwoBodyDecayMatrixElement(PDT::Spin1, PDT::Spin1Half, PDT::Spin1Half)));
  Complex phase = exp(Complex(0.,1.)*dInfo.lastPhi());

  // 0 = -, 2 = +
  (*kernelPhiDep)(0,0,0) = 0.;
  (*kernelPhiDep)(2,1,1) = 0.;
  (*kernelPhiDep)(0,0,1) = v_AP_mmp/phase;
  (*kernelPhiDep)(2,1,0) = v_AP_ppm*phase;
  (*kernelPhiDep)(0,1,0) = v_AP_mpm/phase;
  (*kernelPhiDep)(2,0,1) = v_AP_pmp*phase;
  (*kernelPhiDep)(0,1,1) = 0.;
  (*kernelPhiDep)(2,0,0) = 0.;

  return kernelPhiDep;
}

// If needed, insert default implementations of  function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void IFqx2gqxDipoleKernel::persistentOutput(PersistentOStream & ) const {
}

void IFqx2gqxDipoleKernel::persistentInput(PersistentIStream & , int) {
}

ClassDescription<IFqx2gqxDipoleKernel> IFqx2gqxDipoleKernel::initIFqx2gqxDipoleKernel;
// Definition of the static class description member.

void IFqx2gqxDipoleKernel::Init() {

  static ClassDocumentation<IFqx2gqxDipoleKernel> documentation
    ("IFqx2gqxDipoleKernel");

}

