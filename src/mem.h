#ifndef MEM_H
#define MEM_H

#include "common.h"

typedef struct {
  double *A11, *A21, *A12, *A22;
  double *U11, *U21, *U12, *U22;
  double *V11, *V21, *V12, *V22;
} matrices;

typedef struct {
  double *S1, *S2;
  double *s;
} vectors;

typedef struct {
  matrices r;
  vectors v;
} Dmem;

typedef struct {
  matrices r, i;
  vectors v;
} Zmem;

typedef struct {
  wide *K2, *RE, *OU, *OV;
  double *w;
} Tout;

extern double *Valloc(const size_t n);
extern double *Vfree(double *const d);

extern Dmem *Dalloc(const size_t n);
extern Dmem *Dfree(Dmem *const d);

extern Zmem *Zalloc(const size_t n);
extern Zmem *Zfree(Zmem *const z);

extern Tout *Talloc(const size_t n);
extern Tout *Tfree(Tout *const t);

#endif /* !MEM_H */
