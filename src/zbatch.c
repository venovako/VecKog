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
  Zmem *const z = Zalloc(n);
  if (!z)
    return EXIT_FAILURE;
  Tout *const t = Talloc(n);
  if (!t)
    return EXIT_FAILURE;

  const size_t V = n2V(n);
  for (size_t j = (size_t)0u; j < b; ++j) {
    (void)fprintf(stdout, "batch %10zu ", j);
    (void)fflush(stdout);
    if (n != fread(z->r.A11, sizeof(double), n, fi)) {
      perror("fread(A11r)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->i.A11, sizeof(double), n, fi)) {
      perror("fread(A11i)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->r.A21, sizeof(double), n, fi)) {
      perror("fread(A21r)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->i.A21, sizeof(double), n, fi)) {
      perror("fread(A21i)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->r.A12, sizeof(double), n, fi)) {
      perror("fread(A12r)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->i.A12, sizeof(double), n, fi)) {
      perror("fread(A12i)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->r.A22, sizeof(double), n, fi)) {
      perror("fread(A22r)");
      return EXIT_FAILURE;
    }
    if (n != fread(z->i.A22, sizeof(double), n, fi)) {
      perror("fread(A22i)");
      return EXIT_FAILURE;
    }
    (void)fprintf(stdout, "...");
    (void)fflush(stdout);
    double w = omp_get_wtime();
#pragma omp parallel for default(none) shared(V,z)
    for (size_t i = (size_t)0u; i < V; ++i) {
      const size_t k = (i << VLlg);
      z8svd2_
        ((z->r.A11 + k), (z->i.A11 + k), (z->r.A21 + k), (z->i.A21 + k), (z->r.A12 + k), (z->i.A12 + k), (z->r.A22 + k), (z->i.A22 + k),
         (z->r.U11 + k), (z->i.U11 + k), (z->r.U21 + k), (z->i.U21 + k), (z->r.U12 + k), (z->i.U12 + k), (z->r.U22 + k), (z->i.U22 + k),
         (z->r.V11 + k), (z->i.V11 + k), (z->r.V21 + k), (z->i.V21 + k), (z->r.V12 + k), (z->i.V12 + k), (z->r.V22 + k), (z->i.V22 + k),
         (z->v.S1 + k), (z->v.S2 + k), (z->v.s + k));
    }
    w = omp_get_wtime() - w;
    (void)fprintf(stdout, "%# 13.6f ", w);
    (void)fflush(stdout);
    wzre
      (n, t->K2, t->RE, t->OU, t->OV,
       z->r.A11, z->i.A11, z->r.A21, z->i.A21, z->r.A12, z->i.A12, z->r.A22, z->i.A22,
       z->r.U11, z->i.U11, z->r.U21, z->i.U21, z->r.U12, z->i.U12, z->r.U22, z->i.U22,
       z->r.V11, z->i.V11, z->r.V21, z->i.V21, z->r.V12, z->i.V12, z->r.V22, z->i.V22,
       z->v.S1, z->v.S2, z->v.s);
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
  (void)Zfree(z);
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
