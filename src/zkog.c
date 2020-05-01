#include "zkog.h"

void z8svd2_
(const double A11r[static 1], const double A11i[static 1], const double A21r[static 1], const double A21i[static 1],
 const double A12r[static 1], const double A12i[static 1], const double A22r[static 1], const double A22i[static 1],
 double U11r[static 1], double U11i[static 1], double U21r[static 1], double U21i[static 1],
 double U12r[static 1], double U12i[static 1], double U22r[static 1], double U22i[static 1],
 double V11r[static 1], double V11i[static 1], double V21r[static 1], double V21i[static 1],
 double V12r[static 1], double V12i[static 1], double V22r[static 1], double V22i[static 1],
 double S1[static 1], double S2[static 1], double S[static 1])
{
  // constants
  register const VD h = VI(set1)((double)(DBL_MAX_EXP - 3)); VP(h);
  register const VD m = VI(set1)(DBL_TRUE_MIN); VP(m);
  register const VD m0 = VI(set1)(-0.0); VP(m0);
  register const VD p0 = VI(setzero)(); VP(p0);
  register const VD p1 = VI(set1)(+1.0); VP(p1);

  // load A from RAM
  register VD a11r = VI(load)(A11r); VP(a11r);
  register VD a11i = VI(load)(A11i); VP(a11i);
  register VD a21r = VI(load)(A21r); VP(a21r);
  register VD a21i = VI(load)(A21i); VP(a21i);
  register VD a12r = VI(load)(A12r); VP(a12r);
  register VD a12i = VI(load)(A12i); VP(a12i);
  register VD a22r = VI(load)(A22r); VP(a22r);
  register VD a22i = VI(load)(A22i); VP(a22i);

  // compute E
  register VD e11r = VI(sub)(h, VI(getexp)(a11r)); VP(e11r);
  register VD e11i = VI(sub)(h, VI(getexp)(a11i)); VP(e11i);
  register VD e21r = VI(sub)(h, VI(getexp)(a21r)); VP(e21r);
  register VD e21i = VI(sub)(h, VI(getexp)(a21i)); VP(e21i);
  register VD e12r = VI(sub)(h, VI(getexp)(a12r)); VP(e12r);
  register VD e12i = VI(sub)(h, VI(getexp)(a12i)); VP(e12i);
  register VD e22r = VI(sub)(h, VI(getexp)(a22r)); VP(e22r);
  register VD e22i = VI(sub)(h, VI(getexp)(a22i)); VP(e22i);

  // compute s
  register VD er = VI(min)(VI(min)(e11r, e21r), VI(min)(e12r, e22r)); VP(er);
  register VD ei = VI(min)(VI(min)(e11i, e21i), VI(min)(e12i, e22i)); VP(ei);
  register VD s = VI(min)(VI(set1)(DBL_MAX), VI(min)(er, ei)); VP(s);

  // scale A
  a11r = VI(scalef)(a11r, s); VP(a11r);
  a11i = VI(scalef)(a11i, s); VP(a11i);
  a21r = VI(scalef)(a21r, s); VP(a21r);
  a21i = VI(scalef)(a21i, s); VP(a21i);
  a12r = VI(scalef)(a12r, s); VP(a12r);
  a12i = VI(scalef)(a12i, s); VP(a12i);
  a22r = VI(scalef)(a22r, s); VP(a22r);
  a22i = VI(scalef)(a22i, s); VP(a22i);

  // compute the absolute values
  register VD a11_ = VI(hypot)(a11r, a11i); VP(a11_);
  register VD a21_ = VI(hypot)(a21r, a21i); VP(a21_);
  register VD a12_ = VI(hypot)(a12r, a12i); VP(a12_);
  register VD a22_ = VI(hypot)(a22r, a22i); VP(a22_);

  // compute the column norms
  register VD a1_ = VI(hypot)(a11_, a21_); VP(a1_);
  register VD a2_ = VI(hypot)(a12_, a22_); VP(a2_);

  // <-compare a1_ and a2_
  register const MD c = LT(a1_, a2_); MP(c);

  // column-permute
  register VD a11r_ = VI(mask_blend)(c, a11r, a12r); VP(a11r_);
  register VD a11i_ = VI(mask_blend)(c, a11i, a12i); VP(a11i_);
  register VD a11__ = VI(mask_blend)(c, a11_, a12_); VP(a11__);
  register VD a12r_ = VI(mask_blend)(c, a12r, a11r); VP(a12r_);
  register VD a12i_ = VI(mask_blend)(c, a12i, a11i); VP(a12i_);
  register VD a12__ = VI(mask_blend)(c, a12_, a11_); VP(a12__);
  register VD a1__ = VI(mask_blend)(c, a1_, a2_); VP(a1__);
  register VD a21r_ = VI(mask_blend)(c, a21r, a22r); VP(a21r_);
  register VD a21i_ = VI(mask_blend)(c, a21i, a22i); VP(a21i_);
  register VD a21__ = VI(mask_blend)(c, a21_, a22_); VP(a21__);
  register VD a22r_ = VI(mask_blend)(c, a22r, a21r); VP(a22r_);
  register VD a22i_ = VI(mask_blend)(c, a22i, a21i); VP(a22i_);
  register VD a22__ = VI(mask_blend)(c, a22_, a21_); VP(a22__);
  register VD a2__ = VI(mask_blend)(c, a2_, a1_); VP(a2__);

  // <-compare a11__ and a21__
  register const MD r = LT(a11__, a21__); MP(r);

  // row-permute
  a11r = VI(mask_blend)(r, a11r_, a21r_); VP(a11r);
  a11i = VI(mask_blend)(r, a11i_, a21i_); VP(a11i);
  a11_ = VI(mask_blend)(r, a11__, a21__); VP(a11_);
  a21r = VI(mask_blend)(r, a21r_, a11r_); VP(a21r);
  a21i = VI(mask_blend)(r, a21i_, a11i_); VP(a21i);
  a21_ = VI(mask_blend)(r, a21__, a11__); VP(a21_);
  a12r = VI(mask_blend)(r, a12r_, a22r_); VP(a12r);
  a12i = VI(mask_blend)(r, a12i_, a22i_); VP(a12i);
  a12_ = VI(mask_blend)(r, a12__, a22__); VP(a12_);
  a22r = VI(mask_blend)(r, a22r_, a12r_); VP(a22r);
  a22i = VI(mask_blend)(r, a22i_, a12i_); VP(a22i);
  a22_ = VI(mask_blend)(r, a22__, a12__); VP(a22_);

  // d11
  a11r_ = VI(or)(VI(min)(VI(div)(VI(abs)(a11r), a11_), p1), VI(and)(a11r, m0)); VP(a11r_);
  a11i_ = VI(div)(a11i, VI(max)(a11_, m)); VP(a11i_);

  // d22
  a21r_ = VI(or)(VI(min)(VI(div)(VI(abs)(a21r), a21_), p1), VI(and)(a21r, m0)); VP(a21r_);
  a21i_ = VI(div)(a21i, VI(max)(a21_, m)); VP(a21i_);

  // e11i = -cimag(d11)
  e11i = VI(xor)(a11i_, m0); VP(e11i);
  // e21i = -cimag(d22)
  e21i = VI(xor)(a21i_, m0); VP(e21i);

  // a12'''
  a12r_ = VI(fmsub)(a11r_, a12r, VI(mul)(e11i, a12i)); VP(a12r_);
  a12i_ = VI(fmadd)(a11r_, a12i, VI(mul)(e11i, a12r)); VP(a12i_);

  // a22'''
  a22r_ = VI(fmsub)(a21r_, a22r, VI(mul)(e21i, a22i)); VP(a22r_);
  a22i_ = VI(fmadd)(a21r_, a22i, VI(mul)(e21i, a22r)); VP(a22i_);

  // \mp\tan(\alpha)
  register const VD _ta = VI(max)(VI(div)(a21_, a11_), p0); VP(_ta);
  register const VD ta = VI(xor)(_ta, m0); VP(ta);
  // \cos(\alpha)
  register const VD ca = VI(invsqrt)(VI(fmadd)(ta, ta, p1)); VP(ca);

  // r11
  a11r = a1_; VP(a11r);

  // r12'
  a12r = VI(mul)(ca, VI(fmadd)(_ta, a22r_, a12r_)); VP(a12r);
  a12i = VI(mul)(ca, VI(fmadd)(_ta, a22i_, a12i_)); VP(a12i);

  // r22''
  a22r = VI(mul)(ca, VI(fmadd)(ta, a12r_, a22r_)); VP(a22r);
  a22i = VI(mul)(ca, VI(fmadd)(ta, a12i_, a22i_)); VP(a22i);

  // \tilde{d}22 -> a12r/i_
  // \hat{d}22 -> a22r/i_

  register VD s1, s2;
#ifdef BACKSCALE
  // optional backscaling by -s
  s = VI(xor)(s, m0); VP(s);
  // backscale the singular values
  s1 = VI(scalef)(s1, s); VP(s1);
  s2 = VI(scalef)(s2, s); VP(s2);
  // set -0.0 as the scaling parameter
  s = m0; VP(s);
#endif /* BACKSCALE */

  // store the singular values
  VI(store)(S1, s1);
  VI(store)(S2, s2);
  // store the scaling parameters
  VI(store)(S, s);
}
