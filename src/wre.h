#ifndef WRE_H
#define WRE_H

#include "common.h"

extern void wdre
(const size_t n, wide K2[static restrict 1], wide RE[static restrict 1], wide OU[static restrict 1], wide OV[static restrict 1],
 const double A11[static restrict 1], const double A21[static restrict 1], const double A12[static restrict 1], const double A22[static restrict 1],
 const double U11[static restrict 1], const double U21[static restrict 1], const double U12[static restrict 1], const double U22[static restrict 1],
 const double V11[static restrict 1], const double V21[static restrict 1], const double V12[static restrict 1], const double V22[static restrict 1],
 const double S1[static restrict 1], const double S2[static restrict 1], const double *const S);

extern void wzre
(const size_t n, wide K2[static restrict 1], wide RE[static restrict 1], wide OU[static restrict 1], wide OV[static restrict 1],
 const double A11r[static restrict 1], const double A11i[static restrict 1], const double A21r[static restrict 1], const double A21i[static restrict 1],
 const double A12r[static restrict 1], const double A12i[static restrict 1], const double A22r[static restrict 1], const double A22i[static restrict 1],
 const double U11r[static restrict 1], const double U11i[static restrict 1], const double U21r[static restrict 1], const double U21i[static restrict 1],
 const double U12r[static restrict 1], const double U12i[static restrict 1], const double U22r[static restrict 1], const double U22i[static restrict 1],
 const double V11r[static restrict 1], const double V11i[static restrict 1], const double V21r[static restrict 1], const double V21i[static restrict 1],
 const double V12r[static restrict 1], const double V12i[static restrict 1], const double V22r[static restrict 1], const double V22i[static restrict 1],
 const double S1[static restrict 1], const double S2[static restrict 1], const double *const S);

extern int Pwre(FILE f[static 1], const size_t n, const wide K2[static restrict 1], const wide RE[static restrict 1], const wide OU[static restrict 1], const wide OV[static restrict 1]);
extern int Bwre(FILE f[static 1], const size_t i, const double t, const wide k2, const wide re, const wide ou, const wide ov, const double *const avg);

#endif /* !WRE_H */
