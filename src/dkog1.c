void d1svd2_
(const double A11r[static 1], const double A21r[static 1], const double A12r[static 1], const double A22r[static 1],
 double U11r[static 1], double U21r[static 1], double U12r[static 1], double U22r[static 1],
 double V11r[static 1], double V21r[static 1], double V12r[static 1], double V22r[static 1],
 double S1[static 1], double S2[static 1], double S[static 1])
{
  // load A from RAM
  double
    a11r = *A11r, a21r = *A21r, a12r = *A12r, a22r = *A22r;

  // compute E
  int e11r, e21r, e12r, e22r;
  (void)frexp(a11r, &e11r);
  (void)frexp(a21r, &e21r);
  (void)frexp(a12r, &e12r);
  (void)frexp(a22r, &e22r);

  const int h = DBL_MAX_EXP - 2;
  e11r = h - e11r;
  e21r = h - e21r;
  e12r = h - e12r;
  e22r = h - e22r;

  // compute s
  e11r = ((e11r <= e21r) ? e11r : e21r);
  e12r = ((e12r <= e22r) ? e12r : e22r);
  int s = ((e11r <= e12r) ? e11r : e12r);

  // scale A
  a11r = scalbn(a11r, s);
  a21r = scalbn(a21r, s);
  a12r = scalbn(a12r, s);
  a22r = scalbn(a22r, s);

  // compute the absolute values
  double
    a11_ = fabs(a11r),
    a21_ = fabs(a21r),
    a12_ = fabs(a12r),
    a22_ = fabs(a22r),
  // compute the column norms
    a1_ = hypot(a11_, a21_),
    a2_ = hypot(a12_, a22_),
  // column-permuted variables
    a11r_, a11__, a12r_, a12__, a21r_, a21__, a22r_, a22__;

  // <-compare a1_ and a2_
  const bool c = (a1_ < a2_);

  // column-permute
  if (c) {
    a11r_ = a12r;
    a11__ = a12_;
    a12r_ = a11r;
    a12__ = a11_;
    a21r_ = a22r;
    a21__ = a22_;
    a22r_ = a21r;
    a22__ = a21_;
  }
  else {
    a11r_ = a11r;
    a11__ = a11_;
    a12r_ = a12r;
    a12__ = a12_;
    a21r_ = a21r;
    a21__ = a21_;
    a22r_ = a22r;
    a22__ = a22_;
  }

  // <-compare a11__ and a21__
  const bool r = (a11__ < a21__);

  // row-permute
  if (r) {
    a11r = a21r_;
    a11_ = a21__;
    a21r = a11r_;
    a21_ = a11__;
    a12r = a22r_;
    a12_ = a22__;
    a22r = a12r_;
    a22_ = a12__;
  }
  else {
    a11r = a11r_;
    a11_ = a11__;
    a21r = a21r_;
    a21_ = a21__;
    a12r = a12r_;
    a12_ = a12__;
    a22r = a22r_;
    a22_ = a22__;
  }

  // d11
  a11r_ = copysign(1.0, a11r);

  // d22
  a21r_ = copysign(1.0, a21r);

  // a12'''
  a12r_ = a11r_ * a12r;

  // a22'''
  a22r_ = a21r_ * a22r;

  // functions of \alpha
  const double
    ta = -fmax(a21_ / a11_, 0.0),
    ca = invsqrt(fma(ta, ta, 1.0)),
    sa = ca * ta;

  // r11
  a11r = (c ? a2_ : a1_);

  // r12'
  a12r = ca * fma(-ta, a22r_, a12r_);

  // r22''
  a22r = ca * fma(ta, a12r_, a22r_);

  // \tilde{d}22
  a12r_ = copysign(1.0, a12r);

  // r12
  a12r = fabs(a12r);

  // r22'
  a22r_ = a22r * a12r_;

  // r22
  a22r = fabs(a22r_);

  // \hat{d}22
  a22r_ = copysign(1.0, a22r_);

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
  a21r = -a12r_ * sv;
  a12r = sv;
  a22r = a12r_ * cv;

  if (c) {
    *V11r = a21r;
    *V21r = a11r;
    *V12r = a22r;
    *V22r = a12r;
  }
  else {
    *V11r = a11r;
    *V21r = a21r;
    *V12r = a12r;
    *V22r = a22r;
  }

  const double
    cacu = ca * cu,
    casu = ca * su,
    sacu = sa * cu,
    sasu = sa * su;

  // P_r^T U
  a11r = a11r_ * fma(-a22r_, sasu, cacu);
  a21r = -a21r_ * fma(a22r_, casu, sacu);
  a12r = a11r_ * fma(a22r_, sacu, casu);
  a22r = a21r_ * fma(a22r_, cacu, -sasu);

  if (r) {
    *U11r = a21r;
    *U21r = a11r;
    *U12r = a22r;
    *U22r = a12r;
  }
  else {
    *U11r = a11r;
    *U21r = a21r;
    *U12r = a12r;
    *U22r = a22r;
  }
}
