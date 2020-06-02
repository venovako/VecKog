#ifndef ZKOG1_H
#define ZKOG1_H

// z1svd2 from the paper

// callable from Fortran directly (no interfaces needed):
// EXTERN Z1SVD2
// CALL Z1SVD2(...)

extern void z1svd2_
(const double A11r[static restrict 1], const double A11i[static restrict 1], const double A21r[static restrict 1], const double A21i[static restrict 1],
 const double A12r[static restrict 1], const double A12i[static restrict 1], const double A22r[static restrict 1], const double A22i[static restrict 1],
 double U11r[static restrict 1], double U11i[static restrict 1], double U21r[static restrict 1], double U21i[static restrict 1],
 double U12r[static restrict 1], double U12i[static restrict 1], double U22r[static restrict 1], double U22i[static restrict 1],
 double V11r[static restrict 1], double V11i[static restrict 1], double V21r[static restrict 1], double V21i[static restrict 1],
 double V12r[static restrict 1], double V12i[static restrict 1], double V22r[static restrict 1], double V22i[static restrict 1],
 double S1[static restrict 1], double S2[static restrict 1], double S[static restrict 1]);

#endif /* !ZKOG1_H */
