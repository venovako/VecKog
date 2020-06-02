#ifndef DKOG8_H
#define DKOG8_H

// dSsvd2 from the paper
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN D8SVD2
// CALL D8SVD2(...)

extern void d8svd2_
(const double A11r[static restrict VL], const double A21r[static restrict VL], const double A12r[static restrict VL], const double A22r[static restrict VL],
 double U11r[static restrict VL], double U21r[static restrict VL], double U12r[static restrict VL], double U22r[static restrict VL],
 double V11r[static restrict VL], double V21r[static restrict VL], double V12r[static restrict VL], double V22r[static restrict VL],
 double S1[static restrict VL], double S2[static restrict VL], double S[static restrict VL]);

#endif /* !DKOG8_H */
