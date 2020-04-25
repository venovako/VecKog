#ifndef MEM_H
#define MEM_H

#include "common.h"

typedef struct {
  double *A11, *A21, *A12, *A22;
  double *U11, *U21, *U12, *U22;
  double *V11, *V21, *V12, *V22;
} matrices;

typedef struct {
  double *R11, *R12, *R22; /* F, G, H */
  double *U11, *U21, *U12, *U22;
  double *V11, *V21, *V12, *V22;
} triang;

typedef struct {
  double *S1, *S2;
  double *s;
} vectors;

typedef struct {
  matrices r;
  vectors v;
#ifdef TEST_DLASV2
  triang t;
#endif /* TEST_DLASV2 */
} Dmem;

typedef struct {
  matrices r, i;
  vectors v;
#ifdef TEST_DLASV2
  triang t;
#endif /* TEST_DLASV2 */
} Zmem;

extern double *Valloc(const size_t n);

extern Dmem *Dalloc(const size_t n);
extern void Dfree(Dmem d[static 1]);
extern Zmem *Zalloc(const size_t n);
extern void Zfree(Zmem z[static 1]);

#endif /* !MEM_H */
