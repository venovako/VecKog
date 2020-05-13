#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *line = (char*)NULL;
  size_t linecap = (size_t)0u;
  ssize_t linelen = (ssize_t)0;

  if ((linelen = getline(&line, &linecap, stdin)) <= 0)
    return EXIT_FAILURE;

  double min_t = INFINITY, max_t = 0.0, t = INFINITY;
  long double min_k = INFINITY, max_k = 0.0L, k = INFINITY, min_r = INFINITY, max_r = 0.0L, r = INFINITY, min_u = INFINITY, max_u = 0.0L, u = INFINITY, min_v = INFINITY, max_v = 0.0L, v = INFINITY;

  for (unsigned b; (linelen = getline(&line, &linecap, stdin)) > 0; ) {
    if (sscanf(line, "%u,%lf,%LE,%LE,%LE,%LE", &b, &t, &k, &r, &u, &v) != 6)
      return EXIT_FAILURE;
    min_t = fmin(min_t, t);
    max_t = fmax(max_t, t);
    min_k = fminl(min_k, k);
    max_k = fmaxl(max_k, k);
    min_r = fminl(min_r, r);
    max_r = fmaxl(max_r, r);
    min_u = fminl(min_u, u);
    max_u = fmaxl(max_u, u);
    min_v = fminl(min_v, v);
    max_v = fmaxl(max_v, v);
  }
  free(line);

  if (fprintf(stdout, "\"min\",%# 13.6f,%# .21LE,%# .21LE,%# .21LE,%# .21LE\n", min_t, min_k, min_r, min_u, min_v) <= 0)
    return EXIT_FAILURE;
  if (fprintf(stdout, "\"MAX\",%# 13.6f,%# .21LE,%# .21LE,%# .21LE,%# .21LE\n", max_t, max_k, max_r, max_u, max_v) <= 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
