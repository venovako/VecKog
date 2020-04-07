#include "common.h"

static double next_drn()
{
  union {
    double d;
    struct {
      uint32_t lo, hi;
    } u;
  } r;
  do {
    r.u.hi = arc4random();
  } while (!isfinite(r.d));
  return r.d;
}

int main(int argc, char *argv[])
{
  if (3 != argc) {
    (void)fprintf(stderr, "%s N FileName\n", argv[0]);
    return EXIT_FAILURE;
  }
  const size_t n = (size_t)strtoull(argv[1], (char**)NULL, 0);
  if (!n) {
    perror("strtoull");
    return EXIT_FAILURE;
  }
  FILE *const f = fopen(argv[2], "wb");
  if (!f) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  double *const d = (double*)calloc(n, sizeof(double));
  if (!d) {
    perror("calloc");
    return EXIT_FAILURE;
  }

  const size_t nd = n * sizeof(double);
  (void)fprintf(stdout, "arc4random_buf(%zu B)... ", nd);
  (void)fflush(stdout);

  arc4random_buf(d, nd);
  (void)fprintf(stdout, "done\n");
  (void)fflush(stdout);

  (void)fprintf(stdout, "checking for NaNs and infinities... ");
  (void)fflush(stdout);
  size_t j = 0u;
  for (size_t i = 0u; i < n; ++i) {
    if (!isfinite(d[i])) {
      d[i] = next_drn();
      ++j;
    }
  }
  (void)fprintf(stdout, "%zu found and replaced\n", j);
  (void)fflush(stdout);

  (void)fprintf(stdout, "writing %s file... ", argv[2]);
  (void)fflush(stdout);

  if (n != fwrite(d, sizeof(double), n, f))
    perror("fwrite");
  else if (fclose(f))
    perror("fclose");
  else {
    (void)fprintf(stdout, "done\n");
    (void)fflush(stdout);
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}
