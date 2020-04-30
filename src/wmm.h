#ifndef WMM_H
#define WMM_H

#include "common.h"

/* Computes A' = U 2^{-s}Sigma V^T - A and returns || A' ||_F in wide precision. */
extern wide wdmm
(const double a11, const double a21, const double a12, const double a22,
 const double u11, const double u21, const double u12, const double u22,
 const double v11, const double v21, const double v12, const double v22,
 const double s1, const double s2, const double s);

/* Computes A' = U 2^{-s}Sigma V^H - A and returns || A' ||_F in wide precision. */
extern wide wzmm
(const double a11r, const double a11i, const double a21r, const double a21i,
 const double a12r, const double a12i, const double a22r, const double a22i,
 const double u11r, const double u11i, const double u21r, const double u21i,
 const double u12r, const double u12i, const double u22r, const double u22i,
 const double v11r, const double v11i, const double v21r, const double v21i,
 const double v12r, const double v12i, const double v22r, const double v22i,
 const double s1, const double s2, const double s);

#endif /* !WMM_H */
