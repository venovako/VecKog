#ifndef WMM_H
#define WMM_H

#include "common.h"

/* Computes A' = U S V^T - A and returns || A' ||_F in quadruple precision. */
extern wide wdmm
(double a11[static 1], double a21[static 1], double a12[static 1], double a22[static 1],
 const double u11, const double u21, const double u12, const double u22,
 const double s1, const double s2,
 const double v11, const double v21, const double v12, const double v22);

/* Computes A' = U S V^H - A and returns || A' ||_F in quadruple precision. */
extern wide wzmm
(double a11r[static 1], double a11i[static 1],
 double a21r[static 1], double a21i[static 1],
 double a12r[static 1], double a12i[static 1],
 double a22r[static 1], double a22i[static 1],
 const double u11r, const double u11i,
 const double u21r, const double u21i,
 const double u12r, const double u12i,
 const double u22r, const double u22i,
 const double s1, const double s2,
 const double v11r, const double v11i,
 const double v21r, const double v21i,
 const double v12r, const double v12i,
 const double v22r, const double v22i);

#endif /* !WMM_H */
