void z1svd2_
(const double A11r[static restrict 1], const double A11i[static restrict 1], const double A21r[static restrict 1], const double A21i[static restrict 1],
 const double A12r[static restrict 1], const double A12i[static restrict 1], const double A22r[static restrict 1], const double A22i[static restrict 1],
 double U11r[static restrict 1], double U11i[static restrict 1], double U21r[static restrict 1], double U21i[static restrict 1],
 double U12r[static restrict 1], double U12i[static restrict 1], double U22r[static restrict 1], double U22i[static restrict 1],
 double V11r[static restrict 1], double V11i[static restrict 1], double V21r[static restrict 1], double V21i[static restrict 1],
 double V12r[static restrict 1], double V12i[static restrict 1], double V22r[static restrict 1], double V22i[static restrict 1],
 double S1[static restrict 1], double S2[static restrict 1], double S[static restrict 1])
{
  // load A from RAM
  double
    a11r = *A11r, a11i = *A11i,
    a21r = *A21r, a21i = *A21i,
    a12r = *A12r, a12i = *A12i,
    a22r = *A22r, a22i = *A22i;

  // compute E
  int e11r, e11i, e21r, e21i, e12r, e12i, e22r, e22i;
  (void)frexp(a11r, &e11r);
  (void)frexp(a11i, &e11i);
  (void)frexp(a21r, &e21r);
  (void)frexp(a21i, &e21i);
  (void)frexp(a12r, &e12r);
  (void)frexp(a12i, &e12i);
  (void)frexp(a22r, &e22r);
  (void)frexp(a22i, &e22i);

  const int h = DBL_MAX_EXP - 2;
  e11r = h - e11r;
  e11i = h - e11i;
  e21r = h - e21r;
  e21i = h - e21i;
  e12r = h - e12r;
  e12i = h - e12i;
  e22r = h - e22r;
  e22i = h - e22i;

  // compute s
  e11r = ((e11r <= e21r) ? e11r : e21r);
  e11i = ((e11i <= e21i) ? e11i : e21i);
  e12r = ((e12r <= e22r) ? e12r : e22r);
  e12i = ((e12i <= e22i) ? e12i : e22i);

  e11r = ((e11r <= e12r) ? e11r : e12r);
  e11i = ((e11i <= e12i) ? e11i : e12i);
  int s = ((e11r <= e11i) ? e11r : e11i);

  // scale A
  a11r = scalbn(a11r, s);
  a11i = scalbn(a11i, s);
  a21r = scalbn(a21r, s);
  a21i = scalbn(a21i, s);
  a12r = scalbn(a12r, s);
  a12i = scalbn(a12i, s);
  a22r = scalbn(a22r, s);
  a22i = scalbn(a22i, s);

  // compute the absolute values
  double
    a11_ = hypot(a11r, a11i),
    a21_ = hypot(a21r, a21i),
    a12_ = hypot(a12r, a12i),
    a22_ = hypot(a22r, a22i),
  // compute the column norms
    a1_ = hypot(a11_, a21_),
    a2_ = hypot(a12_, a22_),
  // aux variables
    a11r_, a11i_, a11__,
    a21r_, a21i_, a21__,
    a12r_, a12i_, a12__,
    a22r_, a22i_, a22__;

  // <-compare a1_ and a2_
  const bool c = (a1_ < a2_);

  // column-permute
  if (c) {
    a11r_ = a12r;
    a11i_ = a12i;
    a11__ = a12_;
    a12r_ = a11r;
    a12i_ = a11i;
    a12__ = a11_;
    a21r_ = a22r;
    a21i_ = a22i;
    a21__ = a22_;
    a22r_ = a21r;
    a22i_ = a21i;
    a22__ = a21_;
  }
  else {
    a11r_ = a11r;
    a11i_ = a11i;
    a11__ = a11_;
    a12r_ = a12r;
    a12i_ = a12i;
    a12__ = a12_;
    a21r_ = a21r;
    a21i_ = a21i;
    a21__ = a21_;
    a22r_ = a22r;
    a22i_ = a22i;
    a22__ = a22_;
  }

  // <-compare a11__ and a21__
  const bool r = (a11__ < a21__);

  // row-permute
  if (r) {
    a11r = a21r_;
    a11i = a21i_;
    a11_ = a21__;
    a21r = a11r_;
    a21i = a11i_;
    a21_ = a11__;
    a12r = a22r_;
    a12i = a22i_;
    a12_ = a22__;
    a22r = a12r_;
    a22i = a12i_;
    a22_ = a12__;
  }
  else {
    a11r = a11r_;
    a11i = a11i_;
    a11_ = a11__;
    a21r = a21r_;
    a21i = a21i_;
    a21_ = a21__;
    a12r = a12r_;
    a12i = a12i_;
    a12_ = a12__;
    a22r = a22r_;
    a22i = a22i_;
    a22_ = a22__;
  }

  // d11
  a11r_ = copysign(fmin(fabs(a11r) / a11_, 1.0), a11r);
  a11i_ = a11i / fmax(a11_, DBL_TRUE_MIN);

  // d22
  a21r_ = copysign(fmin(fabs(a21r) / a21_, 1.0), a21r);
  a21i_ = a21i / fmax(a21_, DBL_TRUE_MIN);

  // a12'''
  a12r_ = fma(a11r_, a12r,  (a11i_ * a12i));
  a12i_ = fma(a11r_, a12i, -(a11i_ * a12r));

  // a22'''
  a22r_ = fma(a21r_, a22r,  (a21i_ * a22i));
  a22i_ = fma(a21r_, a22i, -(a21i_ * a22r));

  // functions of \alpha
  const double
    ta = -fmax(a21_ / a11_, 0.0),
    ca = invsqrt(fma(ta, ta, 1.0)),
    sa = ca * ta;

  // r11
  a11r = (c ? a2_ : a1_);

  // r12'
  a12r = ca * fma(-ta, a22r_, a12r_);
  a12i = ca * fma(-ta, a22i_, a12i_);
  a12_ = hypot(a12r, a12i);

  // r22''
  a22r = ca * fma(ta, a12r_, a22r_);
  a22i = ca * fma(ta, a12i_, a22i_);

  // \tilde{d}22
  a12r_ = copysign(fmin(fabs(a12r) / a12_, 1.0), a12r);
  a12i_ = -a12i / fmax(a12_, DBL_TRUE_MIN);

  // r12
  a12r = a12_;

  // r22'
  a22r_ = fma(a22r, a12r_, -(a22i * a12i_));
  a22i_ = fma(a22i, a12r_,  (a22r * a12i_));
  a22_ = hypot(a22r_, a22i_);

  // \hat{d}22
  a22r_ = copysign(fmin(fabs(a22r_) / a22_, 1.0), a22r_);
  a22i_ = a22i_ / fmax(a22_, DBL_TRUE_MIN);

  // r22
  a22r = a22_;

  *U22r = a11r;
  *U12r = a12r;
  *V22r = a22r;
  LAPACK_D(lasv2)(U22r, U12r, V22r, S2, S1, V21r, V11r, U21r, U11r);

#ifdef BACKSCALE
  s = -s;
  *S1 = scalbn(*S1, s);
  *S2 = scalbn(*S2, s);
  *S = -0.0;
#else /* !BACKSCALE */
  *S = (double)s;
#endif /* ?BACKSCALE */

  // functions of \varphi
  const double
    cu = *U11r,
    su = -*U21r;

  // functions of \psi
  const double
    cv = *V11r,
    sv = -*V21r;

  // P_c^T V
  a11r = cv;
  a11i = 0.0;
  a21r = -a12r_ * sv;
  a21i = -a12i_ * sv;
  a12r = sv;
  a12i = 0.0;
  a22r = a12r_ * cv;
  a22i = a12i_ * cv;

  if (c) {
    *V11r = a21r;
    *V11i = a21i;
    *V21r = a11r;
    *V21i = a11i;
    *V12r = a22r;
    *V12i = a22i;
    *V22r = a12r;
    *V22i = a12i;
  }
  else {
    *V11r = a11r;
    *V11i = a11i;
    *V21r = a21r;
    *V21i = a21i;
    *V12r = a12r;
    *V12i = a12i;
    *V22r = a22r;
    *V22i = a22i;
  }

  const double
    cacu = ca * cu,
    casu = ca * su,
    sacu = sa * cu,
    sasu = sa * su;

  // P_r^T U
  a11_ = fma(-a22r_, sasu, cacu);
  a11__ = -a22i_ * sasu;
  a11r = fma(a11r_, a11_, -(a11i_ * a11__));
  a11i = fma(a11r_, a11__, (a11i_ * a11_));

  a21_ = fma(a22r_, casu, sacu);
  a21__ = a22i_ * casu;
  a21r = -fma(a21r_, a21_, -(a21i_ * a21__));
  a21i = -fma(a21r_, a21__, (a21i_ * a21_));

  a12_ = fma(a22r_, sacu, casu);
  a12__ = a22i_ * sacu;
  a12r = fma(a11r_, a12_, -(a11i_ * a12__));
  a12i = fma(a11r_, a12__, (a11i_ * a12_));

  a22_ = fma(a22r_, cacu, -sasu);
  a22__ = a22i_ * cacu;
  a22r = fma(a21r_, a22_, -(a21i_ * a22__));
  a22i = fma(a21r_, a22__, (a21i_ * a22_));

  if (r) {
    *U11r = a21r;
    *U11i = a21i;
    *U21r = a11r;
    *U21i = a11i;
    *U12r = a22r;
    *U12i = a22i;
    *U22r = a12r;
    *U22i = a12i;
  }
  else {
    *U11r = a11r;
    *U11i = a11i;
    *U21r = a21r;
    *U21i = a21i;
    *U12r = a12r;
    *U12i = a12i;
    *U22r = a22r;
    *U22i = a22i;
  }
}
