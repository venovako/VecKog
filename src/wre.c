#include "wre.h"

#ifdef USE_EXTENDED
#include "xmm.h"
#else /* USE_QUAD */
#include "qmm.h"
#endif /* ?USE_EXTENDED */

void wdre
(const size_t n, relerr RE[static 1], relerr OU[static 1], relerr OV[static 1],
 double A11[static 1], double A21[static 1], double A12[static 1], double A22[static 1],
 const double U11[static 1], const double U21[static 1], const double U12[static 1], const double U22[static 1],
 const double S1[static 1], const double S2[static 1],
 const double V11[static 1], const double V21[static 1], const double V12[static 1], const double V22[static 1])
{
#pragma omp parallel for default(none) shared(n,RE,OU,OV,A11,A21,A12,A22,U11,U21,U12,U22,S1,S2,V11,V21,V12,V22)
  for (size_t i = (size_t)0u; i < n; ++i) {
    RE[i] =
#ifdef USE_EXTENDED
      xdmm
#else /* USE_QUAD */
      qdmm
#endif /* ?USE_EXTENDED */
      ((A11 + i), (A21 + i), (A12 + i), (A22 + i), U11[i], U21[i], U12[i], U22[i], S1[i], S2[i], V11[i], V21[i], V12[i], V22[i]);
  }
}

void wzre
(const size_t n, relerr RE[static 1], relerr OU[static 1], relerr OV[static 1],
 double A11r[static 1], double A11i[static 1],
 double A21r[static 1], double A21i[static 1],
 double A12r[static 1], double A12i[static 1],
 double A22r[static 1], double A22i[static 1],
 const double U11r[static 1], const double U11i[static 1],
 const double U21r[static 1], const double U21i[static 1],
 const double U12r[static 1], const double U12i[static 1],
 const double U22r[static 1], const double U22i[static 1],
 const double S1[static 1], const double S2[static 1],
 const double V11r[static 1], const double V11i[static 1],
 const double V21r[static 1], const double V21i[static 1],
 const double V12r[static 1], const double V12i[static 1],
 const double V22r[static 1], const double V22i[static 1])
{
#pragma omp parallel for default(none) shared(n,RE,OU,OV,A11r,A11i,A21r,A21i,A12r,A12i,A22r,A22i,U11r,U11i,U21r,U21i,U12r,U12i,U22r,U22i,S1,S2,V11r,V11i,V21r,V21i,V12r,V12i,V22r,V22i)
  for (size_t i = (size_t)0u; i < n; ++i) {
    RE[i] =
#ifdef USE_EXTENDED
      xzmm
#else /* USE_QUAD */
      qzmm
#endif /* ?USE_EXTENDED */
      ((A11r + i), (A11i + i), (A21r + i), (A21i + i), (A12r + i), (A12i + i), (A22r + i), (A22i + i),
       U11r[i], U11i[i], U21r[i], U21i[i], U12r[i], U12i[i], U22r[i], U22i[i],
       S1[i], S2[i],
       V11r[i], V11i[i], V21r[i], V21i[i], V12r[i], V12i[i], V22r[i], V22i[i]);
  }
}
