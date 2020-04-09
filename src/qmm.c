#include "qmm.h"

#include "common.h"

__float128 qdmm
(double a11[static 1], double a21[static 1], double a12[static 1], double a22[static 1],
 const double u11, const double u21, const double u12, const double u22,
 const double s1, const double s2,
 const double v11, const double v21, const double v12, const double v22)
{
  __float128
    A11 = (__float128)-*a11, A21 = (__float128)-*a21, A12 = (__float128)-*a12, A22 = (__float128)-*a22;
  const __float128 /* scale U by S, transpose V */
    S1 = (__float128)s1, S2 = (__float128)s2,
    U11 = ((__float128)u11 * S1), U21 = ((__float128)u21 * S1), U12 = ((__float128)u12 * S2), U22 = ((__float128)u22 * S2),
    V11 = (__float128)v11, V21 = (__float128)v12, V12 = (__float128)v21, V22 = (__float128)v22; /* transpose V */

  *a11 = (double)(A11 = __fmaq(U11, V11, __fmaq(U12, V21, A11)));
  *a21 = (double)(A21 = __fmaq(U21, V11, __fmaq(U22, V21, A21)));
  *a12 = (double)(A12 = __fmaq(U11, V12, __fmaq(U12, V22, A12)));
  *a22 = (double)(A22 = __fmaq(U21, V12, __fmaq(U22, V22, A22)));

  return __hypotq(__hypotq(A11, A21), __hypotq(A12, A22));
}

static inline void qwfma(__float128 dr[static 1], __float128 di[static 1], const __float128 a, const __float128 br, const __float128 bi, const __float128 cr, const __float128 ci)
{
  *dr = __fmaq(a, br, cr);
  *di = __fmaq(a, bi, ci);
}

static inline void qjfma(__float128 dr[static 1], __float128 di[static 1], const __float128 a, const __float128 br, const __float128 bi, const __float128 cr, const __float128 ci)
{
  *dr = __fmaq(-a, bi, cr);
  *di = __fmaq( a, br, ci);
}

static inline void qxfma(__float128 dr[static 1], __float128 di[static 1], const __float128 ar, const __float128 ai, const __float128 br, const __float128 bi, const __float128 cr, const __float128 ci)
{
  *dr = __fmaq(ar, br, __fmaq(-ai, bi, cr));
  *di = __fmaq(ar, bi, __fmaq( ai, br, ci));
}

static inline void qfma(__float128 dr[static 1], __float128 di[static 1], const __float128 ar, const __float128 ai, const __float128 br, const __float128 bi, const __float128 cr, const __float128 ci)
{
  if (ai == 0.0q)
    qwfma(dr, di, ar, br, bi, cr, ci);
  else if (ar == 0.0q)
    qjfma(dr, di, ai, br, bi, cr, ci);
  else
    qxfma(dr, di, ar, ai, br, bi, cr, ci);
}

__float128 qzmm
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
  __float128 r = 0.0q, i = 0.0q,
    A11r = (__float128)-*a11r, A11i = (__float128)-*a11i,
    A21r = (__float128)-*a21r, A21i = (__float128)-*a21i,
    A12r = (__float128)-*a12r, A12i = (__float128)-*a12i,
    A22r = (__float128)-*a22r, A22i = (__float128)-*a22i;
  const __float128
    S1 = (__float128)s1, S2 = (__float128)s2;
  const __float128 /* scale U by S, conjugate-transpose V */
    U11r = ((__float128)u11r * S1), U11i = ((__float128)u11i * S1),
    U21r = ((__float128)u21r * S1), U21i = ((__float128)u21i * S1),
    U12r = ((__float128)u12r * S2), U12i = ((__float128)u12i * S2),
    U22r = ((__float128)u22r * S2), U22i = ((__float128)u22i * S2),
    V11r = (__float128)v11r, V11i = (__float128)-v11i,
    V21r = (__float128)v12r, V21i = (__float128)-v12i,
    V12r = (__float128)v21r, V12i = (__float128)-v21i,
    V22r = (__float128)v22r, V22i = (__float128)-v22i;

  qfma(&r, &i, U12r, U12i, V21r, V21i, A11r, A11i);
  qfma(&A11r, &A11i, U11r, U11i, V11r, V11i, r, i);
  *a11r = (double)A11r;
  *a11i = (double)A11i;

  qfma(&r, &i, U22r, U22i, V21r, V21i, A21r, A21i);
  qfma(&A21r, &A21i, U21r, U21i, V11r, V11i, r, i);
  *a21r = (double)A21r;
  *a21i = (double)A21i;

  qfma(&r, &i, U12r, U12i, V22r, V22i, A12r, A12i);
  qfma(&A12r, &A12i, U11r, U11i, V12r, V12i, r, i);
  *a12r = (double)A12r;
  *a12i = (double)A12i;

  qfma(&r, &i, U22r, U22i, V22r, V22i, A22r, A22i);
  qfma(&A22r, &A22i, U21r, U21i, V12r, V12i, r, i);
  *a22r = (double)A22r;
  *a22i = (double)A22i;

  return __hypotq(__hypotq(__hypotq(A11r, A11i), __hypotq(A21r, A21i)), __hypotq(__hypotq(A12r, A12i), __hypotq(A22r, A22i)));
}
