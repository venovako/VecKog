#include "common.h"

typedef const double (*pmtx)[2][2];

static inline void dlas2f(const double F, const double G, const double H, double Smax[static 1], double Smin[static 1])
{
  LAPACK_D(las2)(&F, &G, &H, Smin, Smax);
}

static inline void dlas2c(const size_t i, const pmtx D, double Smax[static 1], double Smin[static 1])
{
  dlas2f(D[i][0][0], D[i][1][0], D[i][1][1], (Smax + i), (Smin + i));
}

int main(int argc, char *argv[])
{
  if ((3 > argc) || (4 < argc)) {
    (void)fprintf(stderr, "%s FileName NumberOfMatrices [StartFromMatrix#]\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = atoz(argv[2]);
  if (!n) {
    perror("atoz");
    return EXIT_FAILURE;
  }
  const size_t o = ((4 == argc) ? atoz(argv[3]) : (size_t)0u);
  if (o >= n) {
    (void)fprintf(stderr, "offset(%zu) >= count(%zu)\n", o, n);
    return EXIT_FAILURE;
  }
  FILE *f = ((argv[1] && *(argv[1])) ? fopen(argv[1], "rb") : (FILE*)NULL);
  if (!f) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  if (o) {
    if (fseek(f, (long)((o << 2u) * sizeof(double)), SEEK_SET)) {
      perror("fseek");
      return EXIT_FAILURE;
    }
  }

  double *const Smax = (double*)calloc(n, sizeof(double));
  if (!Smax) {
    perror("calloc(Smax)");
    return EXIT_FAILURE;
  }
  double *const Smin = (double*)calloc(n, sizeof(double));
  if (!Smin) {
    perror("calloc(Smin)");
    return EXIT_FAILURE;
  }

  const size_t n4 = n << 2u;
  const pmtx D = (pmtx)calloc(n4, sizeof(double));
  if (!D) {
    perror("calloc(D)");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "reading %zu doubles from %s to memory... ", n4, argv[1]);
  (void)fflush(stdout);
  if (n4 != fread(D, sizeof(double), n4, f)) {
    perror("fread");
    return EXIT_FAILURE;
  }
  if (fclose(f)) {
    perror("fclose");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "done\n");
  (void)fflush(stdout);

  (void)fprintf(stdout, "testing DLAS2 with %d threads... ", omp_get_max_threads());
  (void)fflush(stdout);
  double t = omp_get_wtime();
#pragma omp parallel for default(none) shared(n,D,Smax,Smin)
  for (size_t i = (size_t)0u; i < n; ++i) {
    dlas2c(i, D, Smax, Smin);
  }
  t = omp_get_wtime() - t;
  (void)fprintf(stdout, "%#13.6f s\n", t);
  (void)fflush(stdout);
  free(D);

  char fn[strlen(argv[1]) + 6u];
  if (!(f = fopen(strcat(strcpy(fn, argv[1]), ".Smin"), "wb"))) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "writing %s... ", fn);
  (void)fflush(stdout);
  if (n != fwrite(Smin, sizeof(double), n, f)) {
    perror("fwrite");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "done\n");
  (void)fflush(stdout);
  free(Smin);

  if (!(f = fopen(strcat(strcpy(fn, argv[1]), ".Smax"), "wb"))) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "writing %s... ", fn);
  (void)fflush(stdout);
  if (n != fwrite(Smax, sizeof(double), n, f)) {
    perror("fwrite");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "done\n");
  (void)fflush(stdout);
  free(Smax);

  return EXIT_SUCCESS;
}
