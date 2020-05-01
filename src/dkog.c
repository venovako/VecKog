#include "dkog.h"

void d8svd2_
(const double A11r[static 1], const double A21r[static 1], const double A12r[static 1], const double A22r[static 1],
 double U11r[static 1], double U21r[static 1], double U12r[static 1], double U22r[static 1],
 double V11r[static 1], double V21r[static 1], double V12r[static 1], double V22r[static 1],
 double S1[static 1], double S2[static 1], double S[static 1])
{
  // constants
  register const VD h = VI(set1)((double)(DBL_MAX_EXP - 3));
  register const VD m = VI(set1)(DBL_TRUE_MIN);
  register const VD m0 = VI(set1)(-0.0);
  register const VD p0 = VI(setzero)();
  register const VD p1 = VI(set1)(+1.0);

  // load A from RAM
  register VD a11r = VI(load)(A11r);
  register VD a21r = VI(load)(A21r);
  register VD a12r = VI(load)(A12r);
  register VD a22r = VI(load)(A22r);

  // compute E
  register VD e11r = VI(sub)(h, VI(getexp)(a11r));
  register VD e21r = VI(sub)(h, VI(getexp)(a21r));
  register VD e12r = VI(sub)(h, VI(getexp)(a12r));
  register VD e22r = VI(sub)(h, VI(getexp)(a22r));

  // compute s
  register VD er = VI(min)(VI(min)(e11r, e21r), VI(min)(e12r, e22r));
  register VD s = VI(min)(VI(set1)(DBL_MAX), er);

  // scale A
  a11r = VI(scalef)(a11r, s);
  a21r = VI(scalef)(a21r, s);
  a12r = VI(scalef)(a12r, s);
  a22r = VI(scalef)(a22r, s);

  // compute the absolute values
  register VD a11_ = VI(abs)(a11r);
  register VD a21_ = VI(abs)(a21r);
  register VD a12_ = VI(abs)(a12r);
  register VD a22_ = VI(abs)(a22r);

  // compute the column norms
  register VD a1_ = VI(hypot)(a11_, a21_);
  register VD a2_ = VI(hypot)(a12_, a22_);

  // <-compare a1_ and a2_
  register const MD c = LT(a1_, a2_);

  // column-permute
  register VD a11r_ = VI(mask_blend)(c, a11r, a12r);
  register VD a11__ = VI(mask_blend)(c, a11_, a12_);
  register VD a12r_ = VI(mask_blend)(c, a12r, a11r);
  register VD a12__ = VI(mask_blend)(c, a12_, a11_);
  register VD a1__ = VI(mask_blend)(c, a1_, a2_);
  register VD a21r_ = VI(mask_blend)(c, a21r, a22r);
  register VD a21__ = VI(mask_blend)(c, a21_, a22_);
  register VD a22r_ = VI(mask_blend)(c, a22r, a21r);
  register VD a22__ = VI(mask_blend)(c, a22_, a21_);
  register VD a2__ = VI(mask_blend)(c, a2_, a1_);

  // <-compare a11__ and a21__
  register const MD r = LT(a11__, a21__);

  // row-permute
  a11r = VI(mask_blend)(r, a11r_, a21r_);
  a11_ = VI(mask_blend)(r, a11__, a21__);
  a21r = VI(mask_blend)(r, a21r_, a11r_);
  a21_ = VI(mask_blend)(r, a21__, a11__);
  a12r = VI(mask_blend)(r, a12r_, a22r_);
  a12_ = VI(mask_blend)(r, a12__, a22__);
  a22r = VI(mask_blend)(r, a22r_, a12r_);
  a22_ = VI(mask_blend)(r, a22__, a12__);

  // d11
  a11r_ = VI(or)(p1, VI(and)(a11r, m0));

  // d22
  a21r_ = VI(or)(p1, VI(and)(a21r, m0));

  // a12'''
  a12r_ = VI(xor)(VI(and)(a11r_, m0), a12r);

  // a22'''
  a22r_ = VI(xor)(VI(and)(a21r_, m0), a22r);

  // \mp\tan(\alpha)
  register const VD _ta = VI(max)(VI(div)(a21_, a11_), p0);
  register const VD ta = VI(xor)(_ta, m0);
  // \cos(\alpha)
  register const VD ca = VI(invsqrt)(VI(fmadd)(ta, ta, p1));

  // r11
  a11r = a1_;

  // r12'
  a12r = VI(mul)(ca, VI(fmadd)(_ta, a22r_, a12r_));

  // r22''
  a22r = VI(mul)(ca, VI(fmadd)(ta, a12r_, a22r_));

  // \tilde{d}22 -> a12r_
  // \hat{d}22 -> a22r_

  register VD s1, s2;
#ifdef BACKSCALE
  // optional backscaling by -s
  s = VI(xor)(s, m0);
  // backscale the singular values
  s1 = VI(scalef)(s1, s);
  s2 = VI(scalef)(s2, s);
  // set -0.0 as the scaling parameter
  s = m0;
#endif /* BACKSCALE */

  // store the singular values
  VI(store)(S1, s1);
  VI(store)(S2, s2);
  // store the scaling parameters
  VI(store)(S, s);
}
