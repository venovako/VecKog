#include "mem.h"

#include "vec.h"

static inline void free_nil(double **const d)
{
  if (d) {
    free(*d);
    *d = (double*)NULL;
  }
}

double *Valloc(const size_t n)
{
  const size_t V = n2V(n);
  double *const d = (double*)(V ? aligned_alloc(VA, V * VA) : NULL);
  if (d) {
    /* each thread zeroes-out its portion of *d */
#pragma omp parallel for default(none) shared(V,d)
    for (size_t i = (size_t)0u; i < V; ++i) {
      register const VD z = VI(setzero)();
      VI(stream)((d + (i << VLlg)), z);
    }
  }
  else {
    perror("aligned_alloc");
    if (n)
      exit(EXIT_FAILURE);
  }
  return d;
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
  }
  return d;
}

void Dfree(Dmem d[static 1])
{
  free_nil(&(d->v.s));
  free_nil(&(d->v.S2));
  free_nil(&(d->v.S1));
  free_nil(&(d->r.V22));
  free_nil(&(d->r.V12));
  free_nil(&(d->r.V21));
  free_nil(&(d->r.V11));
  free_nil(&(d->r.U22));
  free_nil(&(d->r.U12));
  free_nil(&(d->r.U21));
  free_nil(&(d->r.U11));
  free_nil(&(d->r.A22));
  free_nil(&(d->r.A12));
  free_nil(&(d->r.A21));
  free_nil(&(d->r.A11));
  free(d);
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
  }
  return z;
}

void Zfree(Zmem z[static 1])
{
  free_nil(&(z->v.s));
  free_nil(&(z->v.S2));
  free_nil(&(z->v.S1));
  free_nil(&(z->i.V22));
  free_nil(&(z->i.V12));
  free_nil(&(z->i.V21));
  free_nil(&(z->i.V11));
  free_nil(&(z->i.U22));
  free_nil(&(z->i.U12));
  free_nil(&(z->i.U21));
  free_nil(&(z->i.U11));
  free_nil(&(z->i.A22));
  free_nil(&(z->i.A12));
  free_nil(&(z->i.A21));
  free_nil(&(z->i.A11));
  free_nil(&(z->r.V22));
  free_nil(&(z->r.V12));
  free_nil(&(z->r.V21));
  free_nil(&(z->r.V11));
  free_nil(&(z->r.U22));
  free_nil(&(z->r.U12));
  free_nil(&(z->r.U21));
  free_nil(&(z->r.U11));
  free_nil(&(z->r.A22));
  free_nil(&(z->r.A12));
  free_nil(&(z->r.A21));
  free_nil(&(z->r.A11));
  free(z);
}
