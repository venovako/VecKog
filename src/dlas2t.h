#ifndef DLAS2T_H
#define DLAS2T_H

#include "common.h"

extern double dlas2c
(const size_t n,
 const double F[static 1], const double G[static 1], const double H[static 1],
 double Smax[static 1], double Smin[static 1]);

#endif /* !DLAS2T_H */
