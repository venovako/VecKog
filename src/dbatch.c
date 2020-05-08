#include "kog.h"
#include "mem.h"
#include "wre.h"

int main(int argc, char *argv[])
{
  if (5 != argc) {
    (void)fprintf(stderr, "%s n #batches in out\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = atoz(argv[1]);
  if (!n) {
    perror("atoz(n)");
    return EXIT_FAILURE;
  }
  const size_t b = atoz(argv[2]);
  if (!b) {
    perror("atoz(b)");
    return EXIT_FAILURE;
  }
  FILE *const fi = fopen(argv[3], "rb");
  if (!fi) {
    perror("fopen(fi)");
    return EXIT_FAILURE;
  }
  FILE *const fo = fopen(argv[4], "wb");
  if (!fo) {
    perror("fopen(fo)");
    return EXIT_FAILURE;
  }
  Dmem *const d = Dalloc(n);
  if (!d)
    return EXIT_FAILURE;
  Tout *const t = Talloc(n);
  if (!t)
    return EXIT_FAILURE;

  const size_t V = n2V(n);
  for (size_t j = (size_t)0u; j < b; ++j) {
    (void)fprintf(stdout, "dbatch %10zu ", j);
    (void)fflush(stdout);
    if (n != fread(d->r.A11, sizeof(double), n, fi)) {
      perror("fread(A11r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A21, sizeof(double), n, fi)) {
      perror("fread(A21r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A12, sizeof(double), n, fi)) {
      perror("fread(A12r)");
      return EXIT_FAILURE;
    }
    if (n != fread(d->r.A22, sizeof(double), n, fi)) {
      perror("fread(A22r)");
      return EXIT_FAILURE;
    }
    (void)fprintf(stdout, "...");
    (void)fflush(stdout);
    double w = omp_get_wtime();
#pragma omp parallel for default(none) shared(V,d)
    for (size_t i = (size_t)0u; i < V; ++i) {
      const size_t k = (i << VLlg);
      d8svd2_
        ((d->r.A11 + k), (d->r.A21 + k), (d->r.A12 + k), (d->r.A22 + k),
         (d->r.U11 + k), (d->r.U21 + k), (d->r.U12 + k), (d->r.U22 + k),
         (d->r.V11 + k), (d->r.V21 + k), (d->r.V12 + k), (d->r.V22 + k),
         (d->v.S1 + k), (d->v.S2 + k), (d->v.s + k));
    }
    w = omp_get_wtime() - w;
    (void)fprintf(stdout, "%# 13.6f ", w);
    (void)fflush(stdout);
    wdre
      (n, t->K2, t->RE, t->OU, t->OV,
       d->r.A11, d->r.A21, d->r.A12, d->r.A22,
       d->r.U11, d->r.U21, d->r.U12, d->r.U22,
       d->r.V11, d->r.V21, d->r.V12, d->r.V22,
       d->v.S1, d->v.S2, d->v.s);
    (void)fprintf(stdout, "s");
    (void)fflush(stdout);
    if (n != fwrite(t->K2, sizeof(wide), n, fo)) {
      perror("fwrite(K2)");
      return EXIT_FAILURE;
    }
    if (n != fwrite(t->RE, sizeof(wide), n, fo)) {
      perror("fwrite(RE)");
      return EXIT_FAILURE;
    }
    if (n != fwrite(t->OU, sizeof(wide), n, fo)) {
      perror("fwrite(OU)");
      return EXIT_FAILURE;
    }
    if (n != fwrite(t->OV, sizeof(wide), n, fo)) {
      perror("fwrite(OV)");
      return EXIT_FAILURE;
    }
    if (fflush(fo)) {
      perror("fflush(fo)");
      return EXIT_FAILURE;
    }
    (void)fprintf(stdout, "\n");
    (void)fflush(stdout);
  }

  (void)Tfree(t);
  (void)Dfree(d);
  if (fclose(fo)) {
    perror("fclose(fo)");
    return EXIT_FAILURE;
  }
  if (fclose(fi)) {
    perror("fclose(fi)");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
