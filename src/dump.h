/* -*- c++ -*- -------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifndef LMP_DUMP_H
#define LMP_DUMP_H

#include "stdio.h"
#include "pointers.h"

namespace LAMMPS_NS {

class Dump : protected Pointers {
 public:
  char *id;                  // user-defined name of Dump
  char *style;               // style of Dump
  int igroup,groupbit;       // group that Dump is performed on

  int first_flag;            // 0 if no initial dump, 1 if yes initial dump
  int clearstep;             // 1 if dump invokes computes, 0 if not

  // static variable across all Dump objects

  static Dump *dumpptr;         // holds a ptr to Dump currently being used

  Dump(class LAMMPS *, int, char **);
  virtual ~Dump();
  void init();
  void write();
  void modify_params(int, char **);
  virtual double memory_usage();

 protected:
  int me,nprocs;             // proc info

  char *filename;            // user-specified file
  int compressed;            // 1 if dump file is written compressed, 0 no
  int binary;                // 1 if dump file is written binary, 0 no
  int multifile;             // 0 = one big file, 1 = one file per timestep
  int multiproc;             // 0 = proc 0 writes for all, 1 = one file/proc

  int header_flag;           // 0 = item, 2 = xyz
  int flush_flag;            // 0 if no flush, 1 if flush every dump
  int sort_flag;             // 1 if sorted output
  int append_flag;           // 1 if open file in append mode, 0 if not
  int singlefile_opened;     // 1 = one big file, already opened, else 0
  int sortcol;               // 0 to sort on ID, 1-N on columns
  int sortcolm1;             // sortcol - 1
  int sortorder;             // ASCEND or DESCEND

  char *format_default;      // default format string
  char *format_user;         // format string set by user
  char *format;              // format string for the file write
  FILE *fp;                  // file to write dump to
  int size_one;              // # of quantities for one atom
  int nme;                   // # of atoms in this dump from me

  double boxxlo,boxxhi;      // local copies of domain values
  double boxylo,boxyhi;      // lo/hi are bounding box for triclinic
  double boxzlo,boxzhi;
  double boxxy,boxxz,boxyz;

  int ntotal;                // # of per-atom lines in snapshot
  int reorderflag;           // 1 if OK to reorder instead of sort
  int ntotal_reorder;        // # of atoms that must be in snapshot
  int nme_reorder;           // # of atoms I must own in snapshot
  int idlo;                  // lowest ID I own when reordering

  int maxbuf;                // size of buf
  double *buf;               // memory for atom quantities

  int maxids;                // size of ids
  int maxsort;               // size of bufsort, idsort, index
  int maxproc;               // size of proclist
  int *ids;                  // list of atom IDs, if sorting on IDs
  double *bufsort;
  int *idsort,*index,*proclist;


  class Irregular *irregular;

  virtual void init_style() = 0;
  virtual void openfile();
  virtual int modify_param(int, char **) {return 0;}
  virtual void write_header(int) = 0;
  virtual int count() = 0;
  virtual void pack(int *) = 0;
  virtual void write_data(int, double *) = 0;

  void sort();
  static int idcompare(const void *, const void *);
  static int bufcompare(const void *, const void *);
  static int bufcompare_reverse(const void *, const void *);
};

}

#endif
