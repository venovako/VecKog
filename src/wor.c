#include "wor.h"

wide wdor
(const double u11, const double u21, const double u12, const double u22)
{
  const wide
    U11 = (wide)u11, U21 = (wide)u21, U12 = (wide)u12, U22 = (wide)u22;

  const wide t = U22 * U21,
    D11 = fmaw(U11, U11, fmaw(U21, U21, W_MONE)),
    D21 = fmaw(U12, U11, t),
    D12 = fmaw(U11, U12, t),
    D22 = fmaw(U12, U12, fmaw(U22, U22, W_MONE));

  return hypotw(hypotw(D11, D21), hypotw(D12, D22));
}

/*
  u11 u21  u11 u12
  u12 u22  u21 u22
 */
wide wzor
(const double u11r, const double u11i,
 const double u21r, const double u21i,
 const double u12r, const double u12i,
 const double u22r, const double u22i)
{
  return W_ZERO;
}
