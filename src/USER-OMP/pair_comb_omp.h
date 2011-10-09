/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Axel Kohlmeyer (Temple U)
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS

PairStyle(comb/omp,PairCombOMP)

#else

#ifndef LMP_PAIR_COMB_OMP_H
#define LMP_PAIR_COMB_OMP_H

#include "pair_comb.h"
#include "thr_omp.h"

namespace LAMMPS_NS {

class PairCombOMP : public PairComb, public ThrOMP {

 public:
  PairCombOMP(class LAMMPS *);

  virtual void compute(int, int);
  virtual double memory_usage();

  virtual double yasu_char(double *, int &);

 private:
  template <int EVFLAG, int EFLAG, int VFLAG_ATOM>
  void eval(double **f, int ifrom, int ito, int tid);

  void Short_neigh_thr();
};

}

#endif
#endif
