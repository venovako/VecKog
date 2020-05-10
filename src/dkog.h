// real xSsvd2 from the paper
// all arguments must be aligned to VA (64) bytes

// callable from Fortran directly (no interfaces needed):
// EXTERN D8SVD2
// CALL D8SVD2(...)

extern void d8svd2_
(const double A11r[static VL], const double A21r[static VL], const double A12r[static VL], const double A22r[static VL],
 double U11r[static VL], double U21r[static VL], double U12r[static VL], double U22r[static VL],
 double V11r[static VL], double V21r[static VL], double V12r[static VL], double V22r[static VL],
 double S1[static VL], double S2[static VL], double S[static VL]);
