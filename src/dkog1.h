#ifndef DKOG1_H
#define DKOG1_H

// d1svd2 from the paper

// callable from Fortran directly (no interfaces needed):
// EXTERN D1SVD2
// CALL D1SVD2(...)

extern void d1svd2_
(const double A11r[static restrict 1], const double A21r[static restrict 1], const double A12r[static restrict 1], const double A22r[static restrict 1],
 double U11r[static restrict 1], double U21r[static restrict 1], double U12r[static restrict 1], double U22r[static restrict 1],
 double V11r[static restrict 1], double V21r[static restrict 1], double V12r[static restrict 1], double V22r[static restrict 1],
 double S1[static restrict 1], double S2[static restrict 1], double S[static restrict 1]);

#endif /* !DKOG1_H */
