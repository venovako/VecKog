#ifdef USE_DLASV2
VI(store)(U22r, a11r);
VI(store)(U12r, a12r);
VI(store)(V22r, a22r);

for (unsigned i = 0u; i < VL; ++i) {
  LAPACK_D(lasv2)((U22r + i), (U12r + i), (V22r + i), (S2 + i), (S1 + i), (V21r + i), (V11r + i), (U21r + i), (U11r + i));
  V12r[i] = -V21r[i];
}

register VD s1 = VI(load)(S1); VP(s1);
register VD s2 = VI(load)(S2); VP(s2);

// cu
register const VD cu = VI(load)(U11r); VP(cu);
// tu
register const VD tu = VI(div)(VI(load)(U21r), cu); VP(tu);
// cv
register const VD cv = VI(load)(V11r); VP(cv);
// tv
register const VD tv = VI(div)(VI(load)(V12r), cu); VP(tv);
#else /* !USE_DLASV2 */
// x, y
register const VD x = VI(max)(VI(div)(a12r, a11r), p0); VP(x);
register const VD y = VI(max)(VI(div)(a22r, a11r), p0); VP(y);

// tan(2\varphi), tan(\varphi)
register const VD t2u = OR(VI(min)(VI(max)(VI(div)(VI(mul)(VI(scalef)(VI(min)(x, y), p1), VI(max)(x, y)), VI(fmadd)(VI(sub)(x, y), VI(add)(x, y), p1)), p0), twof), m0); VP(t2u);
register const VD tu = VI(div)(t2u, VI(add)(p1, VI(sqrt)(VI(fmadd)(t2u, t2u, p1)))); VP(tu);

// sec^2(\varphi), cos(\varphi)
register const VD ssu = VI(fmadd)(tu, tu, p1); VP(ssu);
register const VD cu = VI(invsqrt)(ssu); VP(cu);

// tan(\psi), sec^2(\psi)
register const VD tv = VI(fmsub)(y, tu, x); VP(tv);
register const VD ssv = VI(fmadd)(tv, tv, p1); VP(ssv);

// cos(\psi), cos(\varphi) * cos(\psi)
register const VD cv = VI(invsqrt)(ssv); VP(cv);
register const VD cucv = VI(mul)(cu, cv); VP(cucv);

// sigma_max', sigma_min'
register VD s1 = VI(mul)(VI(mul)(cucv, ssv), a11r);
register VD s2 = VI(mul)(VI(mul)(cucv, ssu), a22r);
#endif /* ?USE_DLASV2 */

#ifdef BACKSCALE
// optional backscaling by -s
s = XOR(s, m0); VP(s);
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
