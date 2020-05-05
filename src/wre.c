#include "wre.h"

#include "wmm.h"
#include "wor.h"

void wdre
(const size_t n, wide K2[static 1], wide RE[static 1], wide OU[static 1], wide OV[static 1],
 const double A11[static 1], const double A21[static 1], const double A12[static 1], const double A22[static 1],
 const double U11[static 1], const double U21[static 1], const double U12[static 1], const double U22[static 1],
 const double V11[static 1], const double V21[static 1], const double V12[static 1], const double V22[static 1],
 const double S1[static 1], const double S2[static 1], const double *const S)
{
  if (S) {
#pragma omp parallel for default(none) shared(n,K2,RE,OU,OV,A11,A21,A12,A22,U11,U21,U12,U22,V11,V21,V12,V22,S1,S2,S)
    for (size_t i = (size_t)0u; i < n; ++i) {
      RE[i] = wdmm
        (A11[i], A21[i], A12[i], A22[i], U11[i], U21[i], U12[i], U22[i], V11[i], V21[i], V12[i], V22[i], S1[i], S2[i], S[i], (K2 + i));
      OU[i] = wdor(U11[i], U21[i], U12[i], U22[i]);
      OV[i] = wdor(V11[i], V21[i], V12[i], V22[i]);
    }
  }
  else {
#pragma omp parallel for default(none) shared(n,K2,RE,OU,OV,A11,A21,A12,A22,U11,U21,U12,U22,V11,V21,V12,V22,S1,S2)
    for (size_t i = (size_t)0u; i < n; ++i) {
      RE[i] = wdmm
        (A11[i], A21[i], A12[i], A22[i], U11[i], U21[i], U12[i], U22[i], V11[i], V21[i], V12[i], V22[i], S1[i], S2[i], +0.0, (K2 + i));
      OU[i] = wdor(U11[i], U21[i], U12[i], U22[i]);
      OV[i] = wdor(V11[i], V21[i], V12[i], V22[i]);
    }
  }
}

void wzre
(const size_t n, wide K2[static 1], wide RE[static 1], wide OU[static 1], wide OV[static 1],
 const double A11r[static 1], const double A11i[static 1], const double A21r[static 1], const double A21i[static 1],
 const double A12r[static 1], const double A12i[static 1], const double A22r[static 1], const double A22i[static 1],
 const double U11r[static 1], const double U11i[static 1], const double U21r[static 1], const double U21i[static 1],
 const double U12r[static 1], const double U12i[static 1], const double U22r[static 1], const double U22i[static 1],
 const double V11r[static 1], const double V11i[static 1], const double V21r[static 1], const double V21i[static 1],
 const double V12r[static 1], const double V12i[static 1], const double V22r[static 1], const double V22i[static 1],
 const double S1[static 1], const double S2[static 1], const double *const S)
{
  if (S) {
#pragma omp parallel for default(none) shared(n,K2,RE,OU,OV,A11r,A11i,A21r,A21i,A12r,A12i,A22r,A22i,U11r,U11i,U21r,U21i,U12r,U12i,U22r,U22i,V11r,V11i,V21r,V21i,V12r,V12i,V22r,V22i,S1,S2,S)
    for (size_t i = (size_t)0u; i < n; ++i) {
      RE[i] = wzmm
        (A11r[i], A11i[i], A21r[i], A21i[i], A12r[i], A12i[i], A22r[i], A22i[i],
         U11r[i], U11i[i], U21r[i], U21i[i], U12r[i], U12i[i], U22r[i], U22i[i],
         V11r[i], V11i[i], V21r[i], V21i[i], V12r[i], V12i[i], V22r[i], V22i[i],
         S1[i], S2[i], S[i], (K2 + i));
      OU[i] = wzor(U11r[i], U11i[i], U21r[i], U21i[i], U12r[i], U12i[i], U22r[i], U22i[i]);
      OV[i] = wzor(V11r[i], V11i[i], V21r[i], V21i[i], V12r[i], V12i[i], V22r[i], V22i[i]);
    }
  }
  else {
#pragma omp parallel for default(none) shared(n,K2,RE,OU,OV,A11r,A11i,A21r,A21i,A12r,A12i,A22r,A22i,U11r,U11i,U21r,U21i,U12r,U12i,U22r,U22i,V11r,V11i,V21r,V21i,V12r,V12i,V22r,V22i,S1,S2)
    for (size_t i = (size_t)0u; i < n; ++i) {
      RE[i] = wzmm
        (A11r[i], A11i[i], A21r[i], A21i[i], A12r[i], A12i[i], A22r[i], A22i[i],
         U11r[i], U11i[i], U21r[i], U21i[i], U12r[i], U12i[i], U22r[i], U22i[i],
         V11r[i], V11i[i], V21r[i], V21i[i], V12r[i], V12i[i], V22r[i], V22i[i],
         S1[i], S2[i], +0.0, (K2 + i));
      OU[i] = wzor(U11r[i], U11i[i], U21r[i], U21i[i], U12r[i], U12i[i], U22r[i], U22i[i]);
      OV[i] = wzor(V11r[i], V11i[i], V21r[i], V21i[i], V12r[i], V12i[i], V22r[i], V22i[i]);
    }
  }
}

int Pwre(FILE f[static 1], const size_t n, const wide K2[static 1], const wide RE[static 1], const wide OU[static 1], const wide OV[static 1])
{
  int ret = fprintf(f, "\n\"N\",\"K2\",\"RE\",\"OU\",\"OV\"\n");
  if (25 != ret)
    return -1;

  char s[31];
  for (size_t i = (size_t)0u; i < n; ++i) {
    ret += fprintf(f, "%zu,%s,", i, xtos(s, (long double)(K2[i])));
    ret += fprintf(f, "%s,", xtos(s, (long double)(RE[i])));
    ret += fprintf(f, "%s,", xtos(s, (long double)(OU[i])));
    ret += fprintf(f, "%s\n", xtos(s, (long double)(OV[i])));
  }

  return (fflush(f) ? -2 : ret);
}
