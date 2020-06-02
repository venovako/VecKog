#ifndef WCMPLX_H
#define WCMPLX_H

#include "common.h"

static inline void wwfma(wide dr[static restrict 1], wide di[static restrict 1], const wide a, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(a, br, cr);
  *di = fmaw(a, bi, ci);
}

static inline void wjfma(wide dr[static restrict 1], wide di[static restrict 1], const wide a, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(-a, bi, cr);
  *di = fmaw( a, br, ci);
}

static inline void wxfma(wide dr[static restrict 1], wide di[static restrict 1], const wide ar, const wide ai, const wide br, const wide bi, const wide cr, const wide ci)
{
  *dr = fmaw(ar, br, fmaw(-ai, bi, cr));
  *di = fmaw(ar, bi, fmaw( ai, br, ci));
}

static inline void wfma(wide dr[static restrict 1], wide di[static restrict 1], const wide ar, const wide ai, const wide br, const wide bi, const wide cr, const wide ci)
{
  if (ai == W_ZERO)
    wwfma(dr, di, ar, br, bi, cr, ci);
  else if (ar == W_ZERO)
    wjfma(dr, di, ai, br, bi, cr, ci);
  else
    wxfma(dr, di, ar, ai, br, bi, cr, ci);
}

static inline void wxmul(wide cr[static restrict 1], wide ci[static restrict 1], const wide ar, const wide ai, const wide br, const wide bi)
{
  *cr = fmaw(ar, br, -ai * bi);
  *ci = fmaw(ar, bi,  ai * br);
}

#endif /* !WCMPLX_H */
