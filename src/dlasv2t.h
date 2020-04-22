#ifndef DLASV2T_H
#define DLASV2T_H

#include "common.h"

extern double dlasv2c
(const size_t n,
 const double F[static 1], const double G[static 1], const double H[static 1],
 double Smax[static 1], double Smin[static 1],
 double U11[static 1], double U21[static 1], double U12[static 1], double U22[static 1],
 double V11[static 1], double V21[static 1], double V12[static 1], double V22[static 1]);

#endif /* !DLASV2T_H */
