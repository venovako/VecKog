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
  u11* u21*  u11 u12
  u12* u22*  u21 u22
 */
wide wzor
(const double u11r, const double u11i,
 const double u21r, const double u21i,
 const double u12r, const double u12i,
 const double u22r, const double u22i)
{
  wide D11, D22, D21r, D21i, D12r, D12i, tr, ti;

  const wide
    U11r = (wide)u11r, U11i = (wide)u11i,
    U21r = (wide)u21r, U21i = (wide)u21i,
    U12r = (wide)u12r, U12i = (wide)u12i,
    U22r = (wide)u22r, U22i = (wide)u22i;

  D11 = fmaw(U11r, U11r, fmaw(U11i, U11i, fmaw(U21r, U21r, fmaw(U21i, U21i, W_MONE))));
  wxmul(&tr, &ti, U22r, -U22i, U21r, U21i);
  wfma(&D21r, &D21i, U12r, -U12i, U11r, U11i, tr,  ti);
  wfma(&D12r, &D12i, U11r, -U11i, U12r, U12i, tr, -ti);
  D22 = fmaw(U12r, U12r, fmaw(U12i, U12i, fmaw(U22r, U22r, fmaw(U22i, U22i, W_MONE))));

  return hypotw(hypotw(D11, hypotw(D21r, D21i)), hypotw(hypotw(D12r, D12i), D22));
}
