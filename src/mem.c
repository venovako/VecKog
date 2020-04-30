#include "mem.h"

#include "vec.h"

double *Valloc(const size_t n)
{
  const size_t V = n2V(n);
  double *const d = (double*)(V ? aligned_alloc(VA, V * VA) : NULL);
  if (d) {
    /* each thread zeroes-out its portion of *d */
#pragma omp parallel for default(none) shared(V,d)
    for (size_t i = (size_t)0u; i < V; ++i) {
      register const VD z = VI(setzero)();
      VI(store)((d + (i << VLlg)), z);
    }
  }
  else {
    perror("aligned_alloc");
    if (n)
      exit(EXIT_FAILURE);
  }
  return d;
}

double *Vfree(double *const d)
{
  free(d);
  return (double*)NULL;
}

Dmem *Dalloc(const size_t n)
{
  Dmem *const d = (Dmem*)(n ? calloc(1u, sizeof(Dmem)) : NULL);
  if (d) {
    d->r.A11 = Valloc(n);
    d->r.A21 = Valloc(n);
    d->r.A12 = Valloc(n);
    d->r.A22 = Valloc(n);
    d->r.U11 = Valloc(n);
    d->r.U21 = Valloc(n);
    d->r.U12 = Valloc(n);
    d->r.U22 = Valloc(n);
    d->r.V11 = Valloc(n);
    d->r.V21 = Valloc(n);
    d->r.V12 = Valloc(n);
    d->r.V22 = Valloc(n);
    d->v.S1 = Valloc(n);
    d->v.S2 = Valloc(n);
    d->v.s = Valloc(n);
#ifdef TEST_DLASV2
    d->t.R11 = Valloc(n);
    d->t.R12 = Valloc(n);
    d->t.R22 = Valloc(n);
    d->t.U11 = Valloc(n);
    d->t.U21 = Valloc(n);
    d->t.U12 = Valloc(n);
    d->t.U22 = Valloc(n);
    d->t.V11 = Valloc(n);
    d->t.V21 = Valloc(n);
    d->t.V12 = Valloc(n);
    d->t.V22 = Valloc(n);
#endif /* TEST_DLASV2 */
  }
  return d;
}

Dmem *Dfree(Dmem *const d)
{
  if (d) {
#ifdef TEST_DLASV2
    d->t.V22 = Vfree(d->t.V22);
    d->t.V12 = Vfree(d->t.V12);
    d->t.V21 = Vfree(d->t.V21);
    d->t.V11 = Vfree(d->t.V11);
    d->t.U22 = Vfree(d->t.U22);
    d->t.U12 = Vfree(d->t.U12);
    d->t.U21 = Vfree(d->t.U21);
    d->t.U11 = Vfree(d->t.U11);
    d->t.R22 = Vfree(d->t.R22);
    d->t.R12 = Vfree(d->t.R12);
    d->t.R11 = Vfree(d->t.R11);
#endif /* TEST_DLASV2 */
    d->v.s = Vfree(d->v.s);
    d->v.S2 = Vfree(d->v.S2);
    d->v.S1 = Vfree(d->v.S1);
    d->r.V22 = Vfree(d->r.V22);
    d->r.V12 = Vfree(d->r.V12);
    d->r.V21 = Vfree(d->r.V21);
    d->r.V11 = Vfree(d->r.V11);
    d->r.U22 = Vfree(d->r.U22);
    d->r.U12 = Vfree(d->r.U12);
    d->r.U21 = Vfree(d->r.U21);
    d->r.U11 = Vfree(d->r.U11);
    d->r.A22 = Vfree(d->r.A22);
    d->r.A12 = Vfree(d->r.A12);
    d->r.A21 = Vfree(d->r.A21);
    d->r.A11 = Vfree(d->r.A11);
    free(d);
  }
  return (Dmem*)NULL;
}

Zmem *Zalloc(const size_t n)
{
  Zmem *const z = (Zmem*)(n ? calloc(1u, sizeof(Zmem)) : NULL);
  if (z) {
    z->r.A11 = Valloc(n);
    z->r.A21 = Valloc(n);
    z->r.A12 = Valloc(n);
    z->r.A22 = Valloc(n);
    z->r.U11 = Valloc(n);
    z->r.U21 = Valloc(n);
    z->r.U12 = Valloc(n);
    z->r.U22 = Valloc(n);
    z->r.V11 = Valloc(n);
    z->r.V21 = Valloc(n);
    z->r.V12 = Valloc(n);
    z->r.V22 = Valloc(n);
    z->i.A11 = Valloc(n);
    z->i.A21 = Valloc(n);
    z->i.A12 = Valloc(n);
    z->i.A22 = Valloc(n);
    z->i.U11 = Valloc(n);
    z->i.U21 = Valloc(n);
    z->i.U12 = Valloc(n);
    z->i.U22 = Valloc(n);
    z->i.V11 = Valloc(n);
    z->i.V21 = Valloc(n);
    z->i.V12 = Valloc(n);
    z->i.V22 = Valloc(n);
    z->v.S1 = Valloc(n);
    z->v.S2 = Valloc(n);
    z->v.s = Valloc(n);
#ifdef TEST_DLASV2
    z->t.R11 = Valloc(n);
    z->t.R12 = Valloc(n);
    z->t.R22 = Valloc(n);
    z->t.U11 = Valloc(n);
    z->t.U21 = Valloc(n);
    z->t.U12 = Valloc(n);
    z->t.U22 = Valloc(n);
    z->t.V11 = Valloc(n);
    z->t.V21 = Valloc(n);
    z->t.V12 = Valloc(n);
    z->t.V22 = Valloc(n);
#endif /* TEST_DLASV2 */
  }
  return z;
}

Zmem *Zfree(Zmem *const z)
{
  if (z) {
#ifdef TEST_DLASV2
    z->t.V22 = Vfree(z->t.V22);
    z->t.V12 = Vfree(z->t.V12);
    z->t.V21 = Vfree(z->t.V21);
    z->t.V11 = Vfree(z->t.V11);
    z->t.U22 = Vfree(z->t.U22);
    z->t.U12 = Vfree(z->t.U12);
    z->t.U21 = Vfree(z->t.U21);
    z->t.U11 = Vfree(z->t.U11);
    z->t.R22 = Vfree(z->t.R22);
    z->t.R12 = Vfree(z->t.R12);
    z->t.R11 = Vfree(z->t.R11);
#endif /* TEST_DLASV2 */
    z->v.s = Vfree(z->v.s);
    z->v.S2 = Vfree(z->v.S2);
    z->v.S1 = Vfree(z->v.S1);
    z->i.V22 = Vfree(z->i.V22);
    z->i.V12 = Vfree(z->i.V12);
    z->i.V21 = Vfree(z->i.V21);
    z->i.V11 = Vfree(z->i.V11);
    z->i.U22 = Vfree(z->i.U22);
    z->i.U12 = Vfree(z->i.U12);
    z->i.U21 = Vfree(z->i.U21);
    z->i.U11 = Vfree(z->i.U11);
    z->i.A22 = Vfree(z->i.A22);
    z->i.A12 = Vfree(z->i.A12);
    z->i.A21 = Vfree(z->i.A21);
    z->i.A11 = Vfree(z->i.A11);
    z->r.V22 = Vfree(z->r.V22);
    z->r.V12 = Vfree(z->r.V12);
    z->r.V21 = Vfree(z->r.V21);
    z->r.V11 = Vfree(z->r.V11);
    z->r.U22 = Vfree(z->r.U22);
    z->r.U12 = Vfree(z->r.U12);
    z->r.U21 = Vfree(z->r.U21);
    z->r.U11 = Vfree(z->r.U11);
    z->r.A22 = Vfree(z->r.A22);
    z->r.A12 = Vfree(z->r.A12);
    z->r.A21 = Vfree(z->r.A21);
    z->r.A11 = Vfree(z->r.A11);
    free(z);
  }
  return (Zmem*)NULL;
}
