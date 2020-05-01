#include "kog.h"
#include "wre.h"

static alignas(VA) double A11r[VL];
static alignas(VA) double A11i[VL];
static alignas(VA) double A21r[VL];
static alignas(VA) double A21i[VL];
static alignas(VA) double A12r[VL];
static alignas(VA) double A12i[VL];
static alignas(VA) double A22r[VL];
static alignas(VA) double A22i[VL];

static alignas(VA) double U11r[VL];
static alignas(VA) double U11i[VL];
static alignas(VA) double U21r[VL];
static alignas(VA) double U21i[VL];
static alignas(VA) double U12r[VL];
static alignas(VA) double U12i[VL];
static alignas(VA) double U22r[VL];
static alignas(VA) double U22i[VL];

static alignas(VA) double V11r[VL];
static alignas(VA) double V11i[VL];
static alignas(VA) double V21r[VL];
static alignas(VA) double V21i[VL];
static alignas(VA) double V12r[VL];
static alignas(VA) double V12i[VL];
static alignas(VA) double V22r[VL];
static alignas(VA) double V22i[VL];

static alignas(VA) double S1[VL];
static alignas(VA) double S2[VL];
static alignas(VA) double S[VL];

static wide RE[VL];
static wide OU[VL];
static wide OV[VL];

static unsigned Vfread(double v[static VL], FILE f[static 1])
{
  const unsigned ret = (unsigned)fread(v, sizeof(double), (size_t)VL, f);
  if (VL != ret) {
    perror("fread");
    return ret;
  }

  for (unsigned i = 0u; i < VL; ++i) {
    while (!isfinite(v[i])) {
      if ((size_t)1u != fread(v + i, sizeof(double), (size_t)1u, f)) {
        perror("fread");
        return i;
      }
    }
  }
  return ret;
}

int main(int argc, char *argv[])
{
  if (2 != argc) {
    (void)fprintf(stderr, "%s N\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = atoz(argv[1]);
  if (!n) {
    perror("atoz");
    return EXIT_FAILURE;
  }
  FILE *const r = fopen("/dev/urandom", "rb");
  if (!r) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  for (size_t i = (size_t)0u; i < n; ) {
    (void)fprintf(stdout, "run %zu ", i);
    (void)fflush(stdout);
    if (VL != Vfread(A11r, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A11i, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A21r, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A21i, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A12r, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A12i, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A22r, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".");
    (void)fflush(stdout);
    if (VL != Vfread(A22i, r))
      return EXIT_FAILURE;
    (void)fprintf(stdout, ".\n");
    (void)fflush(stdout);

    z8svd2_
      (A11r, A11i, A21r, A21i, A12r, A12i, A22r, A22i,
      U11r, U11i, U21r, U21i, U12r, U12i, U22r, U22i,
      V11r, V11i, V21r, V21i, V12r, V12i, V22r, V22i,
      S1, S2, S);

    wzre
      ((size_t)VL, RE, OU, OV,
      A11r, A11i, A21r, A21i, A12r, A12i, A22r, A22i,
      U11r, U11i, U21r, U21i, U12r, U12i, U22r, U22i,
      V11r, V11i, V21r, V21i, V12r, V12i, V22r, V22i,
      S1, S2, S);

    Pwre(stdout, (size_t)VL, RE, OU, OV);
    if (++i < n)
      (void)fprintf(stdout, "\n");
  }

  if (fclose(r)) {
    perror("fclose");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
