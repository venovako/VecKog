#include "vec.h"

int Vprintf(FILE f[static 1], const char *const h, const VD v)
{
  alignas(VA) double d[VL];

  if (fflush(f)) {
    perror("fflush");
    return -1;
  }

  int ret = (h ? fprintf(f, "\nL: %s\n", h) : 0);
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
    if (fprintf(f, "%u: %s\n", i, p) != 29) {
      perror("fprintf");
      return -(int)(i + 4u);
    }
    ret += 29;
  }

  return (fflush(f) ? -3 : ret);
}

int Mprintf(FILE f[static 1], const char *const h, const MD m)
{
  if (fflush(f)) {
    perror("fflush");
    return -1;
  }

  int ret = (h ? fprintf(f, "\n%s: ", h) : 0);
  if (ret < 0) {
    perror("fprintf");
    return -2;
  }

  const unsigned u = _cvtmask8_u32(m);
  for (unsigned i = 0u, o = (1u << VL_1); i < VL; ++i) {
    if (fprintf(f, "%c", ((u & o) ? '1' : '0')) != 1) {
      perror("fprintf");
      return -(int)(i + 4u);
    }
    o >>= 1u;
    ++ret;
  }

  if (fprintf(f, " (%u)\n", u) != 5) {
    perror("fprintf");
    return -(int)(VL + 4u);
  }
  ret += 5;

  return (fflush(f) ? -3 : ret);
}
