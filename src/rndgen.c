// Generates a sequence of N random double precision values.
// For each value x holds isfinite(x) == true but x is otherwise arbitrary.
#include "common.h"

int main(int argc, char *argv[])
{
  if (3 != argc) {
    (void)fprintf(stderr, "%s N FileName\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = atoz(argv[1]);
  if (!n) {
    perror("atoz");
    return EXIT_FAILURE;
  }
  FILE *const r = fopen("/dev/urandom", "rb");
  if (!r) {
    perror("fopen(/dev/urandom)");
    return EXIT_FAILURE;
  }
  FILE *const f = ((argv[2] && *(argv[2])) ? fopen(argv[2], "wb") : (FILE*)NULL);
  if (!f) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  double *const d = (double*)calloc(n, sizeof(double));
  if (!d) {
    perror("calloc");
    return EXIT_FAILURE;
  }

  (void)fprintf(stdout, "reading %zu bytes from /dev/urandom to memory... ", (n * sizeof(double)));
  (void)fflush(stdout);
  if (n != fread(d, sizeof(double), n, r)) {
    perror("fread");
    return EXIT_FAILURE;
  }
  (void)fprintf(stdout, "done\n");
  (void)fflush(stdout);

  (void)fprintf(stdout, "checking for NaNs and infinities with %d threads... ", omp_get_max_threads());
  (void)fflush(stdout);
  size_t j = 0u;
  bool k = true;
#ifdef _OPENMP
#pragma omp parallel for default(none) shared(n,d,r,j,k)
#endif /* _OPENMP */
  for (size_t i = (size_t)0u; i < n; ++i) {
    while (!isfinite(d[i]) && k) {
#ifdef _OPENMP
#pragma omp critical
#endif /* _OPENMP */
      if (k) {
        if ((size_t)1u != fread(d + i, sizeof(double), (size_t)1u, r)) {
          k = false;
          perror("fread");
        }
        else
          ++j;
      }
    }
  }
  (void)fprintf(stdout, "%zu found and replaced\n", j);
  (void)fflush(stdout);
  if (!k)
    return EXIT_FAILURE;

  (void)fprintf(stdout, "writing %s file... ", argv[2]);
  (void)fflush(stdout);

  if (n != fwrite(d, sizeof(double), n, f))
    perror("fwrite");
  else if (fclose(f))
    perror("fclose");
  else if (fclose(r))
    perror("fclose(/dev/urandom)");
  else {
    (void)fprintf(stdout, "done\n");
    (void)fflush(stdout);
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
