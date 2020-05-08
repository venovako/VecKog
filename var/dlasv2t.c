#include "dlasv2t.h"

static inline void dlasv2f
(const double F[static 1], const double G[static 1], const double H[static 1],
 double Smax[static 1], double Smin[static 1],
 double U11[static 1], double U21[static 1], double U12[static 1], double U22[static 1],
 double V11[static 1], double V21[static 1], double V12[static 1], double V22[static 1])
{
  /* extracted from LAPACK's dlasv2.f:
   * SUBROUTINE DLASV2( F, G, H, SSMIN, SSMAX, SNR, CSR, SNL, CSL )
   * [ CSL  SNL ] [  F   G  ] [ CSR -SNR ]  =  [ SSMAX   0   ]
   * [-SNL  CSL ] [  0   H  ] [ SNR  CSR ]     [  0    SSMIN ] */
  LAPACK_D(lasv2)(F, G, H, Smin, Smax, V21, V11, U21, U11);
  *U12 = -*U21;
  *U22 =  *U11;
  *V12 = -*V21;
  *V22 =  *V11;
}

double dlasv2c
(const size_t n,
 const double F[static 1], const double G[static 1], const double H[static 1],
 double Smax[static 1], double Smin[static 1],
 double U11[static 1], double U21[static 1], double U12[static 1], double U22[static 1],
 double V11[static 1], double V21[static 1], double V12[static 1], double V22[static 1])
{
  const double t = omp_get_wtime();
#pragma omp parallel for default(none) shared(n,F,G,H,Smax,Smin,U11,U21,U12,U22,V11,V21,V12,V22)
  for (size_t i = (size_t)0u; i < n; ++i) {
    dlasv2f
      ((F + i), (G + i), (H + i),
       (Smax + i), (Smin + i),
       (U11 + i), (U21 + i), (U12 + i), (U22 + i),
       (V11 + i), (V21 + i), (V12 + i), (V22 + i));
  }
  return (omp_get_wtime() - t);
}
