#include "wmm.h"

wide wdmm
(double a11[static 1], double a21[static 1], double a12[static 1], double a22[static 1],
 const double u11, const double u21, const double u12, const double u22,
 const double s1, const double s2,
 const double v11, const double v21, const double v12, const double v22)
{
  wide
    A11 = (wide)-*a11, A21 = (wide)-*a21, A12 = (wide)-*a12, A22 = (wide)-*a22;
  const wide /* scale U by S, transpose V */
    S1 = (wide)s1, S2 = (wide)s2,
    U11 = ((wide)u11 * S1), U21 = ((wide)u21 * S1), U12 = ((wide)u12 * S2), U22 = ((wide)u22 * S2),
    V11 = (wide)v11, V21 = (wide)v12, V12 = (wide)v21, V22 = (wide)v22; /* transpose V */

  *a11 = (double)(A11 = fmaw(U11, V11, fmaw(U12, V21, A11)));
  *a21 = (double)(A21 = fmaw(U21, V11, fmaw(U22, V21, A21)));
  *a12 = (double)(A12 = fmaw(U11, V12, fmaw(U12, V22, A12)));
  *a22 = (double)(A22 = fmaw(U21, V12, fmaw(U22, V22, A22)));

  return hypotw(hypotw(A11, A21), hypotw(A12, A22));
}

static inline void wwfma(wide dr[static 1], wide di[static 1], const wide a, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(a, br, cr);
  *di = fmaw(a, bi, ci);
}

static inline void wjfma(wide dr[static 1], wide di[static 1], const wide a, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(-a, bi, cr);
  *di = fmaw( a, br, ci);
}

static inline void wxfma(wide dr[static 1], wide di[static 1], const wide ar, const wide ai, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(ar, br, fmaw(-ai, bi, cr));
  *di = fmaw(ar, bi, fmaw( ai, br, ci));
}

static inline void wfma(wide dr[static 1], wide di[static 1], const wide ar, const wide ai, const wide br, const wide bi, const wide cr, const wide ci)
{
  if (ai == 0.0q)
    wwfma(dr, di, ar, br, bi, cr, ci);
  else if (ar == 0.0q)
    wjfma(dr, di, ai, br, bi, cr, ci);
  else
    wxfma(dr, di, ar, ai, br, bi, cr, ci);
}

wide wzmm
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
 const double v22r, const double v22i)
{
  wide r = 0.0q, i = 0.0q,
    A11r = (wide)-*a11r, A11i = (wide)-*a11i,
    A21r = (wide)-*a21r, A21i = (wide)-*a21i,
    A12r = (wide)-*a12r, A12i = (wide)-*a12i,
    A22r = (wide)-*a22r, A22i = (wide)-*a22i;
  const wide
    S1 = (wide)s1, S2 = (wide)s2;
  const wide /* scale U by S, conjugate-transpose V */
    U11r = ((wide)u11r * S1), U11i = ((wide)u11i * S1),
    U21r = ((wide)u21r * S1), U21i = ((wide)u21i * S1),
    U12r = ((wide)u12r * S2), U12i = ((wide)u12i * S2),
    U22r = ((wide)u22r * S2), U22i = ((wide)u22i * S2),
    V11r = (wide)v11r, V11i = (wide)-v11i,
    V21r = (wide)v12r, V21i = (wide)-v12i,
    V12r = (wide)v21r, V12i = (wide)-v21i,
    V22r = (wide)v22r, V22i = (wide)-v22i;

  wfma(&r, &i, U12r, U12i, V21r, V21i, A11r, A11i);
  wfma(&A11r, &A11i, U11r, U11i, V11r, V11i, r, i);
  *a11r = (double)A11r;
  *a11i = (double)A11i;

  wfma(&r, &i, U22r, U22i, V21r, V21i, A21r, A21i);
  wfma(&A21r, &A21i, U21r, U21i, V11r, V11i, r, i);
  *a21r = (double)A21r;
  *a21i = (double)A21i;

  wfma(&r, &i, U12r, U12i, V22r, V22i, A12r, A12i);
  wfma(&A12r, &A12i, U11r, U11i, V12r, V12i, r, i);
  *a12r = (double)A12r;
  *a12i = (double)A12i;

  wfma(&r, &i, U22r, U22i, V22r, V22i, A22r, A22i);
  wfma(&A22r, &A22i, U21r, U21i, V12r, V12i, r, i);
  *a22r = (double)A22r;
  *a22i = (double)A22i;

  return hypotw(hypotw(hypotw(A11r, A11i), hypotw(A21r, A21i)), hypotw(hypotw(A12r, A12i), hypotw(A22r, A22i)));
}
