#include "wmm.h"

#include "wcmplx.h"

wide wdmm
(const double a11, const double a21, const double a12, const double a22,
 const double u11, const double u21, const double u12, const double u22,
 const double v11, const double v21, const double v12, const double v22,
 const double s1, const double s2, const double s)
{
  wide S = W_ZERO, S1 = (wide)s1, S2 = (wide)s2,
    A11 = (wide)-a11, A21 = (wide)-a21, A12 = (wide)-a12, A22 = (wide)-a22;
  if (s != 0.0) {
    S = (wide)-s;
    S1 = scalbw(S1, S);
    S2 = scalbw(S2, S);
  }
  const wide /* scale U by 2^{-s}Sigma */
    U11 = ((wide)u11 * S1), U21 = ((wide)u21 * S1), U12 = ((wide)u12 * S2), U22 = ((wide)u22 * S2),
    V11 = (wide)v11, V21 = (wide)v12, V12 = (wide)v21, V22 = (wide)v22; /* transpose V */

  A11 = fmaw(U11, V11, fmaw(U12, V21, A11));
  A21 = fmaw(U21, V11, fmaw(U22, V21, A21));
  A12 = fmaw(U11, V12, fmaw(U12, V22, A12));
  A22 = fmaw(U21, V12, fmaw(U22, V22, A22));

  return hypotw(hypotw(A11, A21), hypotw(A12, A22));
}

wide wzmm
(const double a11r, const double a11i, const double a21r, const double a21i,
 const double a12r, const double a12i, const double a22r, const double a22i,
 const double u11r, const double u11i, const double u21r, const double u21i,
 const double u12r, const double u12i, const double u22r, const double u22i,
 const double v11r, const double v11i, const double v21r, const double v21i,
 const double v12r, const double v12i, const double v22r, const double v22i,
 const double s1, const double s2, const double s)
{
  wide S = W_ZERO, S1 = (wide)s1, S2 = (wide)s2,
    A11r = (wide)-a11r, A11i = (wide)-a11i,
    A21r = (wide)-a21r, A21i = (wide)-a21i,
    A12r = (wide)-a12r, A12i = (wide)-a12i,
    A22r = (wide)-a22r, A22i = (wide)-a22i,
    r = W_ZERO, i = W_ZERO;
  if (s != 0.0) {
    S = (wide)-s;
    S1 = scalbw(S1, S);
    S2 = scalbw(S2, S);
  }
  const wide /* scale U by 2^{-s}Sigma */
    U11r = ((wide)u11r * S1), U11i = ((wide)u11i * S1),
    U21r = ((wide)u21r * S1), U21i = ((wide)u21i * S1),
    U12r = ((wide)u12r * S2), U12i = ((wide)u12i * S2),
    U22r = ((wide)u22r * S2), U22i = ((wide)u22i * S2),
    /* conjugate-transpose V */
    V11r = (wide)v11r, V11i = (wide)-v11i,
    V21r = (wide)v12r, V21i = (wide)-v12i,
    V12r = (wide)v21r, V12i = (wide)-v21i,
    V22r = (wide)v22r, V22i = (wide)-v22i;

  wfma(&r, &i, U12r, U12i, V21r, V21i, A11r, A11i);
  wfma(&A11r, &A11i, U11r, U11i, V11r, V11i, r, i);

  wfma(&r, &i, U22r, U22i, V21r, V21i, A21r, A21i);
  wfma(&A21r, &A21i, U21r, U21i, V11r, V11i, r, i);

  wfma(&r, &i, U12r, U12i, V22r, V22i, A12r, A12i);
  wfma(&A12r, &A12i, U11r, U11i, V12r, V12i, r, i);

  wfma(&r, &i, U22r, U22i, V22r, V22i, A22r, A22i);
  wfma(&A22r, &A22i, U21r, U21i, V12r, V12i, r, i);

  return hypotw(hypotw(hypotw(A11r, A11i), hypotw(A21r, A21i)), hypotw(hypotw(A12r, A12i), hypotw(A22r, A22i)));
}
