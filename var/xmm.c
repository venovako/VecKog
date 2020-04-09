#include "xmm.h"

#include "common.h"

long double xdmm
(double a11[static 1], double a21[static 1], double a12[static 1], double a22[static 1],
 const double u11, const double u21, const double u12, const double u22,
 const double s1, const double s2,
 const double v11, const double v21, const double v12, const double v22)
{
  long double
    A11 = (long double)-*a11, A21 = (long double)-*a21, A12 = (long double)-*a12, A22 = (long double)-*a22;
  const long double /* scale U by S, transpose V */
    S1 = (long double)s1, S2 = (long double)s2,
    U11 = ((long double)u11 * S1), U21 = ((long double)u21 * S1), U12 = ((long double)u12 * S2), U22 = ((long double)u22 * S2),
    V11 = (long double)v11, V21 = (long double)v12, V12 = (long double)v21, V22 = (long double)v22; /* transpose V */

  *a11 = (double)(A11 = fmal(U11, V11, fmal(U12, V21, A11)));
  *a21 = (double)(A21 = fmal(U21, V11, fmal(U22, V21, A21)));
  *a12 = (double)(A12 = fmal(U11, V12, fmal(U12, V22, A12)));
  *a22 = (double)(A22 = fmal(U21, V12, fmal(U22, V22, A22)));

  return hypotl(hypotl(A11, A21), hypotl(A12, A22));
}

static inline void xwfma(long double dr[static 1], long double di[static 1], const long double a, const long double br, const long double bi, const long double cr, const long double ci)
{
  *dr = fmal(a, br, cr);
  *di = fmal(a, bi, ci);
}

static inline void xjfma(long double dr[static 1], long double di[static 1], const long double a, const long double br, const long double bi, const long double cr, const long double ci)
{
  *dr = fmal(-a, bi, cr);
  *di = fmal( a, br, ci);
}

static inline void xxfma(long double dr[static 1], long double di[static 1], const long double ar, const long double ai, const long double br, const long double bi, const long double cr, const long double ci)
{
  *dr = fmal(ar, br, fmal(-ai, bi, cr));
  *di = fmal(ar, bi, fmal( ai, br, ci));
}

static inline void xfma(long double dr[static 1], long double di[static 1], const long double ar, const long double ai, const long double br, const long double bi, const long double cr, const long double ci)
{
  if (ai == 0.0L)
    xwfma(dr, di, ar, br, bi, cr, ci);
  else if (ar == 0.0L)
    xjfma(dr, di, ai, br, bi, cr, ci);
  else
    xxfma(dr, di, ar, ai, br, bi, cr, ci);
}

long double xzmm
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
  long double r = 0.0L, i = 0.0L,
    A11r = (long double)-*a11r, A11i = (long double)-*a11i,
    A21r = (long double)-*a21r, A21i = (long double)-*a21i,
    A12r = (long double)-*a12r, A12i = (long double)-*a12i,
    A22r = (long double)-*a22r, A22i = (long double)-*a22i;
  const long double
    S1 = (long double)s1, S2 = (long double)s2;
  const long double /* scale U by S, conjugate-transpose V */
    U11r = ((long double)u11r * S1), U11i = ((long double)u11i * S1),
    U21r = ((long double)u21r * S1), U21i = ((long double)u21i * S1),
    U12r = ((long double)u12r * S2), U12i = ((long double)u12i * S2),
    U22r = ((long double)u22r * S2), U22i = ((long double)u22i * S2),
    V11r = (long double)v11r, V11i = (long double)-v11i,
    V21r = (long double)v12r, V21i = (long double)-v12i,
    V12r = (long double)v21r, V12i = (long double)-v21i,
    V22r = (long double)v22r, V22i = (long double)-v22i;

  xfma(&r, &i, U12r, U12i, V21r, V21i, A11r, A11i);
  xfma(&A11r, &A11i, U11r, U11i, V11r, V11i, r, i);
  *a11r = (double)A11r;
  *a11i = (double)A11i;

  xfma(&r, &i, U22r, U22i, V21r, V21i, A21r, A21i);
  xfma(&A21r, &A21i, U21r, U21i, V11r, V11i, r, i);
  *a21r = (double)A21r;
  *a21i = (double)A21i;

  xfma(&r, &i, U12r, U12i, V22r, V22i, A12r, A12i);
  xfma(&A12r, &A12i, U11r, U11i, V12r, V12i, r, i);
  *a12r = (double)A12r;
  *a12i = (double)A12i;

  xfma(&r, &i, U22r, U22i, V22r, V22i, A22r, A22i);
  xfma(&A22r, &A22i, U21r, U21i, V12r, V12i, r, i);
  *a22r = (double)A22r;
  *a22i = (double)A22i;

  return hypotl(hypotl(hypotl(A11r, A11i), hypotl(A21r, A21i)), hypotl(hypotl(A12r, A12i), hypotl(A22r, A22i)));
}
