#include "dlas2t.h"

static inline void dlas2f(const double F[static 1], const double G[static 1], const double H[static 1], double Smax[static 1], double Smin[static 1])
{
  LAPACK_D(las2)(F, G, H, Smin, Smax);
}

double dlas2c
(const size_t n,
 const double F[static 1], const double G[static 1], const double H[static 1],
 double Smax[static 1], double Smin[static 1])
{
  const double t = omp_get_wtime();
#pragma omp parallel for default(none) shared(n,F,G,H,Smax,Smin)
  for (size_t i = (size_t)0u; i < n; ++i) {
    dlas2f((F + i), (G + i), (H + i), (Smax + i), (Smin + i));
  }
  return (omp_get_wtime() - t);
}
