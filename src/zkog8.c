void z8svd2_
(const double A11r[static restrict VL], const double A11i[static restrict VL], const double A21r[static restrict VL], const double A21i[static restrict VL],
 const double A12r[static restrict VL], const double A12i[static restrict VL], const double A22r[static restrict VL], const double A22i[static restrict VL],
 double U11r[static restrict VL], double U11i[static restrict VL], double U21r[static restrict VL], double U21i[static restrict VL],
 double U12r[static restrict VL], double U12i[static restrict VL], double U22r[static restrict VL], double U22i[static restrict VL],
 double V11r[static restrict VL], double V11i[static restrict VL], double V21r[static restrict VL], double V21i[static restrict VL],
 double V12r[static restrict VL], double V12i[static restrict VL], double V22r[static restrict VL], double V22i[static restrict VL],
 double S1[static restrict VL], double S2[static restrict VL], double S[static restrict VL])
{
#ifdef POINTWISE
  for (unsigned i = 0u; i < VL; ++i)
    z1svd2_
      ((A11r + i), (A11i + i), (A21r + i), (A21i + i),
       (A12r + i), (A12i + i), (A22r + i), (A22i + i),
       (U11r + i), (U11i + i), (U21r + i), (U21i + i),
       (U12r + i), (U12i + i), (U22r + i), (U22i + i),
       (V11r + i), (V11i + i), (V21r + i), (V21i + i),
       (V12r + i), (V12i + i), (V22r + i), (V22i + i),
       (S1 + i), (S2 + i), (S + i));
#else /* !POINTWISE */
#include "kogp.c"

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
  register VD a21r_ = VI(mask_blend)(c, a21r, a22r); VP(a21r_);
  register VD a21i_ = VI(mask_blend)(c, a21i, a22i); VP(a21i_);
  register VD a21__ = VI(mask_blend)(c, a21_, a22_); VP(a21__);
  register VD a22r_ = VI(mask_blend)(c, a22r, a21r); VP(a22r_);
  register VD a22i_ = VI(mask_blend)(c, a22i, a21i); VP(a22i_);
  register VD a22__ = VI(mask_blend)(c, a22_, a21_); VP(a22__);

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
  a11r_ = OR(VI(min)(VI(div)(ANDNOT(m0, a11r), a11_), p1), AND(a11r, m0)); VP(a11r_);
  a11i_ = VI(div)(a11i, VI(max)(a11_, m)); VP(a11i_);

  // d22
  a21r_ = OR(VI(min)(VI(div)(ANDNOT(m0, a21r), a21_), p1), AND(a21r, m0)); VP(a21r_);
  a21i_ = VI(div)(a21i, VI(max)(a21_, m)); VP(a21i_);

  // a12'''
  a12r_ = VI(fmadd)(a11r_, a12r, VI(mul)(a11i_, a12i)); VP(a12r_);
  a12i_ = VI(fmsub)(a11r_, a12i, VI(mul)(a11i_, a12r)); VP(a12i_);

  // a22'''
  a22r_ = VI(fmadd)(a21r_, a22r, VI(mul)(a21i_, a22i)); VP(a22r_);
  a22i_ = VI(fmsub)(a21r_, a22i, VI(mul)(a21i_, a22r)); VP(a22i_);

  // -\tan(\alpha)
  register const VD _ta = VI(max)(VI(div)(a21_, a11_), p0); VP(_ta);
  // \cos(\alpha)
  register const VD ca = VI(invsqrt)(VI(fmadd)(_ta, _ta, p1)); VP(ca);

  // r11
  a11r = VI(mask_blend)(c, a1_, a2_); VP(a11r);

  // r12'
  a12r = VI(mul)(ca, VI(fmadd)(_ta, a22r_, a12r_)); VP(a12r);
  a12i = VI(mul)(ca, VI(fmadd)(_ta, a22i_, a12i_)); VP(a12i);
  a12_ = VI(hypot)(a12r, a12i); VP(a12_);

  // r22''
  a22r = VI(mul)(ca, VI(fnmadd)(_ta, a12r_, a22r_)); VP(a22r);
  a22i = VI(mul)(ca, VI(fnmadd)(_ta, a12i_, a22i_)); VP(a22i);

  // conj(\tilde{d}22)
  a12r_ = OR(VI(min)(VI(div)(ANDNOT(m0, a12r), a12_), p1), AND(a12r, m0)); VP(a12r_);
  a12i_ = VI(div)(a12i, VI(max)(a12_, m)); VP(a12i_);

  // r12
  a12r = a12_; VP(a12r);

  // r22'
  a22r_ = VI(fmadd)(a22r, a12r_, VI(mul)(a22i, a12i_)); VP(a22r_);
  a22i_ = VI(fmsub)(a22i, a12r_, VI(mul)(a22r, a12i_)); VP(a22i_);
  a22_ = VI(hypot)(a22r_, a22i_); VP(a22_);

  // \hat{d}22
  a22r_ = OR(VI(min)(VI(div)(ANDNOT(m0, a22r_), a22_), p1), AND(a22r_, m0)); VP(a22r_);
  a22i_ = VI(div)(a22i_, VI(max)(a22_, m)); VP(a22i_);

  // r22
  a22r = a22_; VP(a22r);

#include "svd2.c"

  // cos(\psi) * tan(\psi)
  er = VI(mul)(cv, tv); VP(er);

  // v11
  e11r = cv; VP(e11r);
  e11i = p0; VP(e11i);

  // v21
  e21r = VI(mul)(er, XOR(a12r_, m0)); VP(e21r);
  e21i = VI(mul)(er, a12i_); VP(e21i);

  // v12
  e12r = er; VP(e12r);
  e12i = p0; VP(e12i);

  // v22
  e22r = VI(mul)(cv, a12r_); VP(e22r);
  e22i = VI(mul)(cv, XOR(a12i_, m0)); VP(e22i);

  // P_c * V
  VI(store)(V11r, VI(mask_blend)(c, e11r, e21r));
  VI(store)(V11i, VI(mask_blend)(c, e11i, e21i));
  VI(store)(V21r, VI(mask_blend)(c, e21r, e11r));
  VI(store)(V21i, VI(mask_blend)(c, e21i, e11i));
  VI(store)(V12r, VI(mask_blend)(c, e12r, e22r));
  VI(store)(V12i, VI(mask_blend)(c, e12i, e22i));
  VI(store)(V22r, VI(mask_blend)(c, e22r, e12r));
  VI(store)(V22i, VI(mask_blend)(c, e22i, e12i));

  // cos(\alpha) * cos(\varphi)
  s = VI(mul)(ca, cu); VP(s);

  // -tan(\alpha) * tan(\varphi)
  er = VI(mul)(_ta, tu); VP(er);

  // s * d11
  a11r = VI(mul)(s, a11r_); VP(a11r);
  a11i = VI(mul)(s, a11i_); VP(a11i);

  // s * d22
  a21r = VI(mul)(s, a21r_); VP(a21r);
  a21i = VI(mul)(s, a21i_); VP(a21i);

  // u11'
  ei = VI(mul)(a22i_, er); VP(ei);
  er = VI(fmadd)(a22r_, er, p1); VP(er);

  // u11
  e11r = VI(fmsub)(a11r, er, VI(mul)(a11i, ei)); VP(e11r);
  e11i = VI(fmadd)(a11r, ei, VI(mul)(a11i, er)); VP(e11i);

  // u21'
  er = VI(fnmadd)(a22r_, tu, _ta); VP(er);
  ei = VI(mul)(a22i_, tu); VP(ei);

  // u21
  e21r = VI(fmadd)(a21r, er, VI(mul)(a21i, ei)); VP(e21r);
  e21i = VI(fnmadd)(a21r, ei, VI(mul)(a21i, er)); VP(e21i);

  // u12'
  er = VI(fnmadd)(a22r_, _ta, tu); VP(er);
  ei = VI(mul)(a22i_, _ta); VP(ei);

  // u12
  e12r = VI(fmadd)(a11r, er, VI(mul)(a11i, ei)); VP(e12r);
  e12i = VI(fnmadd)(a11r, ei, VI(mul)(a11i, er)); VP(e12i);

  // u22'
  er = VI(fmadd)(_ta, tu, a22r_); VP(er);
  ei = a22i_; VP(ei);

  // u22
  e22r = VI(fmsub)(a21r, er, VI(mul)(a21i, ei)); VP(e22r);
  e22i = VI(fmadd)(a21r, ei, VI(mul)(a21i, er)); VP(e22i);

  // P_r * U
  VI(store)(U11r, VI(mask_blend)(r, e11r, e21r));
  VI(store)(U11i, VI(mask_blend)(r, e11i, e21i));
  VI(store)(U21r, VI(mask_blend)(r, e21r, e11r));
  VI(store)(U21i, VI(mask_blend)(r, e21i, e11i));
  VI(store)(U12r, VI(mask_blend)(r, e12r, e22r));
  VI(store)(U12i, VI(mask_blend)(r, e12i, e22i));
  VI(store)(U22r, VI(mask_blend)(r, e22r, e12r));
  VI(store)(U22i, VI(mask_blend)(r, e22i, e12i));
#endif /* ?POINTWISE */
}
