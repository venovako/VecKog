#include "vec.h"

int Vprintf(FILE f[static 1], const char *const h, const VD v)
{
  alignas(VA) double d[VL];

  int ret = (h ? fprintf(f, "\nL: %s\n", h) : 0);
  if (ret < 0) {
    perror("fprintf");
    return -1;
  }

  if (fflush(f)) {
    perror("fflush");
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
    if (29 != fprintf(f, "%u: %s\n", i, p)) {
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

  const unsigned u =
#ifdef USE_AVX512DQ
    _cvtmask8_u32(m)
#else /* AVX512F only */
    _cvtmask16_u32((__mmask16)m)
#endif /* ?USE_AVX512DQ */
    ;
  for (unsigned i = 0u, o = (1u << VL_1); i < VL; ++i) {
    if (1 != fprintf(f, "%c", ((u & o) ? '1' : '0'))) {
      perror("fprintf");
      return -(int)(i + 4u);
    }
    o >>= 1u;
    ++ret;
  }

  if (6 != fprintf(f, " (%02X)\n", u)) {
    perror("fprintf");
    return -(int)(VL + 4u);
  }
  ret += 6;

  return (fflush(f) ? -3 : ret);
}
