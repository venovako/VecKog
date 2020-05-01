#include "vec.h"

int Vprintf(FILE f[static 1], const char *const h, const VD v)
{
  alignas(VA) double d[VL];
  int ret = fflush(f);
  if (ret) {
    perror("fflush");
    return -1;
  }

  ret = (h ? fprintf(f, "L: %s\n", h) : 0);
  if (ret < 0) {
    perror("fprintf");
    return -2;
  }

  VI(store)(d, v);
  char s[26];

  for (unsigned i = 0u; i < VL; ++i) {
    char *const p = dtos(s, d[i]);
    if (!p) {
      perror("sprintf");
      return -(int)(i + 4u);
    }
    const int r = fprintf(f, "%u: %s\n", i, p);
    if (r != 29) {
      perror("fprintf");
      return -(int)(i + 4u);
    }
    ret += r;
  }

  return (fflush(f) ? -3 : ret);
}
