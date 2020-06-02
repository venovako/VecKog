#ifndef ZKOG8_H
#define ZKOG8_H

// zSsvd2 from the paper
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN Z8SVD2
// CALL Z8SVD2(...)

extern void z8svd2_
(const double A11r[static restrict VL], const double A11i[static restrict VL], const double A21r[static restrict VL], const double A21i[static restrict VL],
 const double A12r[static restrict VL], const double A12i[static restrict VL], const double A22r[static restrict VL], const double A22i[static restrict VL],
 double U11r[static restrict VL], double U11i[static restrict VL], double U21r[static restrict VL], double U21i[static restrict VL],
 double U12r[static restrict VL], double U12i[static restrict VL], double U22r[static restrict VL], double U22i[static restrict VL],
 double V11r[static restrict VL], double V11i[static restrict VL], double V21r[static restrict VL], double V21i[static restrict VL],
 double V12r[static restrict VL], double V12i[static restrict VL], double V22r[static restrict VL], double V22i[static restrict VL],
 double S1[static restrict VL], double S2[static restrict VL], double S[static restrict VL]);

#endif /* !ZKOG8_H */
