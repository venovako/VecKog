// complex xSsvd2 from the paper
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN Z8SVD2
// CALL Z8SVD2(...)

extern void z8svd2_
(const double A11r[static VL], const double A11i[static VL], const double A21r[static VL], const double A21i[static VL],
 const double A12r[static VL], const double A12i[static VL], const double A22r[static VL], const double A22i[static VL],
 double U11r[static VL], double U11i[static VL], double U21r[static VL], double U21i[static VL],
 double U12r[static VL], double U12i[static VL], double U22r[static VL], double U22i[static VL],
 double V11r[static VL], double V11i[static VL], double V21r[static VL], double V21i[static VL],
 double V12r[static VL], double V12i[static VL], double V22r[static VL], double V22i[static VL],
 double S1[static VL], double S2[static VL], double S[static VL]);

// complex x1svd2 from the paper
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN Z1SVD2
// CALL Z1SVD2(...)

extern void z1svd2_
(const double A11r[static 1], const double A11i[static 1], const double A21r[static 1], const double A21i[static 1],
 const double A12r[static 1], const double A12i[static 1], const double A22r[static 1], const double A22i[static 1],
 double U11r[static 1], double U11i[static 1], double U21r[static 1], double U21i[static 1],
 double U12r[static 1], double U12i[static 1], double U22r[static 1], double U22i[static 1],
 double V11r[static 1], double V11i[static 1], double V21r[static 1], double V21i[static 1],
 double V12r[static 1], double V12i[static 1], double V22r[static 1], double V22i[static 1],
 double S1[static 1], double S2[static 1], double S[static 1]);
