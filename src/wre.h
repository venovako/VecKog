#ifndef WRE_H
#define WRE_H

#include "common.h"

extern void wdre
(const size_t n, wide RE[static 1], wide OU[static 1], wide OV[static 1],
 const double A11[static 1], const double A21[static 1], const double A12[static 1], const double A22[static 1],
 const double U11[static 1], const double U21[static 1], const double U12[static 1], const double U22[static 1],
 const double *const S, const double S1[static 1], const double S2[static 1],
 const double V11[static 1], const double V21[static 1], const double V12[static 1], const double V22[static 1]);

extern void wzre
(const size_t n, wide RE[static 1], wide OU[static 1], wide OV[static 1],
 const double A11r[static 1], const double A11i[static 1],
 const double A21r[static 1], const double A21i[static 1],
 const double A12r[static 1], const double A12i[static 1],
 const double A22r[static 1], const double A22i[static 1],
 const double U11r[static 1], const double U11i[static 1],
 const double U21r[static 1], const double U21i[static 1],
 const double U12r[static 1], const double U12i[static 1],
 const double U22r[static 1], const double U22i[static 1],
 const double *const S, const double S1[static 1], const double S2[static 1],
 const double V11r[static 1], const double V11i[static 1],
 const double V21r[static 1], const double V21i[static 1],
 const double V12r[static 1], const double V12i[static 1],
 const double V22r[static 1], const double V22i[static 1]);

#endif /* !WRE_H */
