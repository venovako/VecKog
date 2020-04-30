#ifndef KOG_H
#define KOG_H

// KogbetliantzS from the paper, real and complex
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN D8SVD2    | EXTERN Z8SVD2
// CALL D8SVD2(...) | CALL Z8SVD2(...)

extern void d8svd2_
(const double A11r[static 1], const double A21r[static 1], const double A12r[static 1], const double A22r[static 1],
 double U11r[static 1], double U21r[static 1], double U12r[static 1], double U22r[static 1],
 double V11r[static 1], double V21r[static 1], double V12r[static 1], double V22r[static 1],
 double S1[static 1], double S2[static 1], double S[static 1]);

extern void z8svd2_
(const double A11r[static 1], const double A11i[static 1], const double A21r[static 1], const double A21i[static 1],
 const double A12r[static 1], const double A12i[static 1], const double A22r[static 1], const double A22i[static 1],
 double U11r[static 1], double U11i[static 1], double U21r[static 1], double U21i[static 1],
 double U12r[static 1], double U12i[static 1], double U22r[static 1], double U22i[static 1],
 double V11r[static 1], double V11i[static 1], double V21r[static 1], double V21i[static 1],
 double V12r[static 1], double V12i[static 1], double V22r[static 1], double V22i[static 1],
 double S1[static 1], double S2[static 1], double S[static 1]);

#endif /* !KOG_H */
