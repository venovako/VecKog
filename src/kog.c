#include "kog.h"

#include "vec.h"

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
  register const VD p1 = VI(set1)(+1.0);

  // load A from RAM
  register VD a11r = VI(load)(A11r);
  register VD a21r = VI(load)(A21r);
  register VD a12r = VI(load)(A12r);
  register VD a22r = VI(load)(A22r);

  // compute E
  register const VD e11r = VI(sub)(h, VI(getexp)(a11r));
  register const VD e21r = VI(sub)(h, VI(getexp)(a21r));
  register const VD e12r = VI(sub)(h, VI(getexp)(a12r));
  register const VD e22r = VI(sub)(h, VI(getexp)(a22r));

  // compute s
  register const VD er = VI(min)(VI(min)(e11r, e21r), VI(min)(e12r, e22r));
  register const VD s = VI(min)(VI(set1)(DBL_MAX), er);

  // scale A
  a11r = VI(scalef)(a11r, s);
  a21r = VI(scalef)(a21r, s);
  a12r = VI(scalef)(a12r, s);
  a22r = VI(scalef)(a22r, s);

  // compute the absolute values
  register const VD a11_ = VI(abs)(a11r);
  register const VD a21_ = VI(abs)(a21r);
  register const VD a12_ = VI(abs)(a12r);
  register const VD a22_ = VI(abs)(a22r);

  // compute the column norms
  register const VD a1_ = VI(hypot)(a11_, a21_);
  register const VD a2_ = VI(hypot)(a12_, a22_);

  // <-compare a1_ and a2_
  register const MD c = LT(a1_, a2_);

  // column-permute
  register const VD a11r_ = VI(mask_blend)(c, a11r, a12r);
  register const VD a11__ = VI(mask_blend)(c, a11_, a12_);
  register const VD a12r_ = VI(mask_blend)(c, a12r, a11r);
  register const VD a12__ = VI(mask_blend)(c, a12_, a11_);
  register const VD a1__ = VI(mask_blend)(c, a1_, a2_);
  register const VD a21r_ = VI(mask_blend)(c, a21r, a22r);
  register const VD a21__ = VI(mask_blend)(c, a21_, a22_);
  register const VD a22r_ = VI(mask_blend)(c, a22r, a21r);
  register const VD a22__ = VI(mask_blend)(c, a22_, a21_);
  register const VD a2__ = VI(mask_blend)(c, a2_, a1_);

  // <-compare a11__ and a21__
  register const MD r = LT(a11__, a21__);

  // row-permute
  register const VD a11r__ = VI(mask_blend)(r, a11r_, a21r_);
  register const VD a11___ = VI(mask_blend)(r, a11__, a21__);
  register const VD a21r__ = VI(mask_blend)(r, a21r_, a11r_);
  register const VD a21___ = VI(mask_blend)(r, a21__, a11__);
  register const VD a12r__ = VI(mask_blend)(r, a12r_, a22r_);
  register const VD a12___ = VI(mask_blend)(r, a12__, a22__);
  register const VD a22r__ = VI(mask_blend)(r, a22r_, a12r_);
  register const VD a22___ = VI(mask_blend)(r, a22__, a12__);

  register VD s1_, s2_;
#ifdef BACKSCALE
  // optional backscaling
  register const VD _s = VI(xor)(s, m0);
  // store the singular values
  VI(store)(S1, VI(scalef)(s1_, _s));
  VI(store)(S2, VI(scalef)(s2_, _s));
  // store -0.0 as the scaling parameter
  VI(store)(S, m0);
#else /* !BACKSCALE */
  // store the singular values
  VI(store)(S1, s1_);
  VI(store)(S2, s2_);
  // store the scaling parameters
  VI(store)(S, s);
#endif /* ?BACKSCALE */
}

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
  register const VD h = VI(set1)((double)(DBL_MAX_EXP - 3));
  register const VD m = VI(set1)(DBL_TRUE_MIN);
  register const VD m0 = VI(set1)(-0.0);
  register const VD p1 = VI(set1)(+1.0);

  // load A from RAM
  register VD a11r = VI(load)(A11r);
  register VD a11i = VI(load)(A11i);
  register VD a21r = VI(load)(A21r);
  register VD a21i = VI(load)(A21i);
  register VD a12r = VI(load)(A12r);
  register VD a12i = VI(load)(A12i);
  register VD a22r = VI(load)(A22r);
  register VD a22i = VI(load)(A22i);

  // compute E
  register const VD e11r = VI(sub)(h, VI(getexp)(a11r));
  register const VD e11i = VI(sub)(h, VI(getexp)(a11i));
  register const VD e21r = VI(sub)(h, VI(getexp)(a21r));
  register const VD e21i = VI(sub)(h, VI(getexp)(a21i));
  register const VD e12r = VI(sub)(h, VI(getexp)(a12r));
  register const VD e12i = VI(sub)(h, VI(getexp)(a12i));
  register const VD e22r = VI(sub)(h, VI(getexp)(a22r));
  register const VD e22i = VI(sub)(h, VI(getexp)(a22i));

  // compute s
  register const VD er = VI(min)(VI(min)(e11r, e21r), VI(min)(e12r, e22r));
  register const VD ei = VI(min)(VI(min)(e11i, e21i), VI(min)(e12i, e22i));
  register const VD s = VI(min)(VI(set1)(DBL_MAX), VI(min)(er, ei));

  // scale A
  a11r = VI(scalef)(a11r, s);
  a11i = VI(scalef)(a11i, s);
  a21r = VI(scalef)(a21r, s);
  a21i = VI(scalef)(a21i, s);
  a12r = VI(scalef)(a12r, s);
  a12i = VI(scalef)(a12i, s);
  a22r = VI(scalef)(a22r, s);
  a22i = VI(scalef)(a22i, s);

  // compute the absolute values
  register const VD a11_ = VI(hypot)(a11r, a11i);
  register const VD a21_ = VI(hypot)(a21r, a21i);
  register const VD a12_ = VI(hypot)(a12r, a12i);
  register const VD a22_ = VI(hypot)(a22r, a22i);

  // compute the column norms
  register const VD a1_ = VI(hypot)(a11_, a21_);
  register const VD a2_ = VI(hypot)(a12_, a22_);

  // <-compare a1_ and a2_
  register const MD c = LT(a1_, a2_);

  // column-permute
  register const VD a11r_ = VI(mask_blend)(c, a11r, a12r);
  register const VD a11i_ = VI(mask_blend)(c, a11i, a12i);
  register const VD a11__ = VI(mask_blend)(c, a11_, a12_);
  register const VD a12r_ = VI(mask_blend)(c, a12r, a11r);
  register const VD a12i_ = VI(mask_blend)(c, a12i, a11i);
  register const VD a12__ = VI(mask_blend)(c, a12_, a11_);
  register const VD a1__ = VI(mask_blend)(c, a1_, a2_);
  register const VD a21r_ = VI(mask_blend)(c, a21r, a22r);
  register const VD a21i_ = VI(mask_blend)(c, a21i, a22i);
  register const VD a21__ = VI(mask_blend)(c, a21_, a22_);
  register const VD a22r_ = VI(mask_blend)(c, a22r, a21r);
  register const VD a22i_ = VI(mask_blend)(c, a22i, a21i);
  register const VD a22__ = VI(mask_blend)(c, a22_, a21_);
  register const VD a2__ = VI(mask_blend)(c, a2_, a1_);

  // <-compare a11__ and a21__
  register const MD r = LT(a11__, a21__);

  // row-permute
  register const VD a11r__ = VI(mask_blend)(r, a11r_, a21r_);
  register const VD a11i__ = VI(mask_blend)(r, a11i_, a21i_);
  register const VD a11___ = VI(mask_blend)(r, a11__, a21__);
  register const VD a21r__ = VI(mask_blend)(r, a21r_, a11r_);
  register const VD a21i__ = VI(mask_blend)(r, a21i_, a11i_);
  register const VD a21___ = VI(mask_blend)(r, a21__, a11__);
  register const VD a12r__ = VI(mask_blend)(r, a12r_, a22r_);
  register const VD a12i__ = VI(mask_blend)(r, a12i_, a22i_);
  register const VD a12___ = VI(mask_blend)(r, a12__, a22__);
  register const VD a22r__ = VI(mask_blend)(r, a22r_, a12r_);
  register const VD a22i__ = VI(mask_blend)(r, a22i_, a12i_);
  register const VD a22___ = VI(mask_blend)(r, a22__, a12__);

  register VD s1_, s2_;
#ifdef BACKSCALE
  // optional backscaling
  register const VD _s = VI(xor)(s, m0);
  // store the singular values
  VI(store)(S1, VI(scalef)(s1_, _s));
  VI(store)(S2, VI(scalef)(s2_, _s));
  // store -0.0 as the scaling parameter
  VI(store)(S, m0);
#else /* !BACKSCALE */
  // store the singular values
  VI(store)(S1, s1_);
  VI(store)(S2, s2_);
  // store the scaling parameters
  VI(store)(S, s);
#endif /* ?BACKSCALE */
}
