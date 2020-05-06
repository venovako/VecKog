void d8svd2_
(const double A11r[static VL], const double A21r[static VL], const double A12r[static VL], const double A22r[static VL],
 double U11r[static VL], double U21r[static VL], double U12r[static VL], double U22r[static VL],
 double V11r[static VL], double V21r[static VL], double V12r[static VL], double V22r[static VL],
 double S1[static VL], double S2[static VL], double S[static VL])
{
#include "kogp.c"

  // load A from RAM
  register VD a11r = VI(load)(A11r); VP(a11r);
  register VD a21r = VI(load)(A21r); VP(a21r);
  register VD a12r = VI(load)(A12r); VP(a12r);
  register VD a22r = VI(load)(A22r); VP(a22r);

  // compute E
  register VD e11r = VI(sub)(h, VI(getexp)(a11r)); VP(e11r);
  register VD e21r = VI(sub)(h, VI(getexp)(a21r)); VP(e21r);
  register VD e12r = VI(sub)(h, VI(getexp)(a12r)); VP(e12r);
  register VD e22r = VI(sub)(h, VI(getexp)(a22r)); VP(e22r);

  // compute s
  register VD er = VI(min)(VI(min)(e11r, e21r), VI(min)(e12r, e22r)); VP(er);
#ifdef NOSCALE
  register VD s = VI(setzero)();
#else /* !NOSCALE */
  register VD s = VI(min)(VI(set1)(DBL_MAX), er); VP(s);
#endif /* ?NOSCALE */

  // scale A
  a11r = VI(scalef)(a11r, s); VP(a11r);
  a21r = VI(scalef)(a21r, s); VP(a21r);
  a12r = VI(scalef)(a12r, s); VP(a12r);
  a22r = VI(scalef)(a22r, s); VP(a22r);

  // compute the absolute values
  register VD a11_ = ANDNOT(m0, a11r); VP(a11_);
  register VD a21_ = ANDNOT(m0, a21r); VP(a21_);
  register VD a12_ = ANDNOT(m0, a12r); VP(a12_);
  register VD a22_ = ANDNOT(m0, a22r); VP(a22_);

  // compute the column norms
  register VD a1_ = VI(hypot)(a11_, a21_); VP(a1_);
  register VD a2_ = VI(hypot)(a12_, a22_); VP(a2_);

  // <-compare a1_ and a2_
  register const MD c = LT(a1_, a2_); MP(c);

  // column-permute
  register VD a11r_ = VI(mask_blend)(c, a11r, a12r); VP(a11r_);
  register VD a11__ = VI(mask_blend)(c, a11_, a12_); VP(a11__);
  register VD a12r_ = VI(mask_blend)(c, a12r, a11r); VP(a12r_);
  register VD a12__ = VI(mask_blend)(c, a12_, a11_); VP(a12__);
  register VD a21r_ = VI(mask_blend)(c, a21r, a22r); VP(a21r_);
  register VD a21__ = VI(mask_blend)(c, a21_, a22_); VP(a21__);
  register VD a22r_ = VI(mask_blend)(c, a22r, a21r); VP(a22r_);
  register VD a22__ = VI(mask_blend)(c, a22_, a21_); VP(a22__);

  // <-compare a11__ and a21__
  register const MD r = LT(a11__, a21__); MP(r);

  // row-permute
  a11r = VI(mask_blend)(r, a11r_, a21r_); VP(a11r);
  a11_ = VI(mask_blend)(r, a11__, a21__); VP(a11_);
  a21r = VI(mask_blend)(r, a21r_, a11r_); VP(a21r);
  a21_ = VI(mask_blend)(r, a21__, a11__); VP(a21_);
  a12r = VI(mask_blend)(r, a12r_, a22r_); VP(a12r);
  a12_ = VI(mask_blend)(r, a12__, a22__); VP(a12_);
  a22r = VI(mask_blend)(r, a22r_, a12r_); VP(a22r);
  a22_ = VI(mask_blend)(r, a22__, a12__); VP(a22_);

  // d11
  a11r_ = OR(p1, AND(a11r, m0)); VP(a11r_);

  // d22
  a21r_ = OR(p1, AND(a21r, m0)); VP(a21r_);

  // a12'''
  a12r_ = XOR(AND(a11r_, m0), a12r); VP(a12r_);

  // a22'''
  a22r_ = XOR(AND(a21r_, m0), a22r); VP(a22r_);

  // -\tan(\alpha)
  register const VD _ta = VI(max)(VI(div)(a21_, a11_), p0); VP(_ta);
  // \cos(\alpha)
  register const VD ca = VI(invsqrt)(VI(fmadd)(_ta, _ta, p1)); VP(ca);

  // r11
  a11r = VI(mask_blend)(c, a1_, a2_); VP(a11r);

  // r12'
  a12r = VI(mul)(ca, VI(fmadd)(_ta, a22r_, a12r_)); VP(a12r);

  // r22''
  a22r = VI(mul)(ca, VI(fnmadd)(_ta, a12r_, a22r_)); VP(a22r);

  // \tilde{d}22
  a12r_ = OR(p1, AND(a12r, m0)); VP(a12r_);

  // r12
  a12r = ANDNOT(m0, a12r); VP(a12r);

  // r22'
  a22r_ = XOR(a22r, AND(a12r_, m0)); VP(a22r_);

  // r22
  a22r = ANDNOT(m0, a22r_); VP(a22r);

  // \hat{d}22
  a22r_ = OR(p1, AND(a22r_, m0)); VP(a22r_);

#include "svd2.c"

  // v11
  e11r = cv; VP(e11r);

  // v12
  e12r = VI(mul)(cv, tv); VP(e12r);

  // v21
  e21r = XOR(VI(mul)(e12r, a12r_), m0); VP(e21r);

  // v22
  e22r = VI(mul)(cv, a12r_); VP(e22r);

  // P_c * V
  VI(store)(V11r, VI(mask_blend)(c, e11r, e21r));
  VI(store)(V21r, VI(mask_blend)(c, e21r, e11r));
  VI(store)(V12r, VI(mask_blend)(c, e12r, e22r));
  VI(store)(V22r, VI(mask_blend)(c, e22r, e12r));

  // cos(\alpha) * cos(\varphi)
  s = VI(mul)(ca, cu); VP(s);

  // \hat{d}22 * -tan(\alpha)
  er = VI(mul)(a22r_, _ta); VP(er);

  // s * d11
  a11r = VI(mul)(s, a11r_); VP(a11r);

  // s * d22
  a21r = VI(mul)(s, a21r_); VP(a21r);

  // u11
  e11r = VI(mul)(a11r, VI(fmadd)(er, tu, p1)); VP(e11r);

  // u21
  e21r = VI(mul)(a21r, VI(fnmadd)(a22r_, tu, _ta)); VP(e21r);

  // u12
  e12r = VI(mul)(a11r, VI(fnmadd)(a22r_, _ta, tu)); VP(e12r);

  // u22
  e22r = VI(mul)(a21r, VI(fmadd)(_ta, tu, a22r_)); VP(e22r);

  // P_r * U
  VI(store)(U11r, VI(mask_blend)(r, e11r, e21r));
  VI(store)(U21r, VI(mask_blend)(r, e21r, e11r));
  VI(store)(U12r, VI(mask_blend)(r, e12r, e22r));
  VI(store)(U22r, VI(mask_blend)(r, e22r, e12r));
}
