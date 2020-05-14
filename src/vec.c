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
    char *const p = dtoa(s, d[i]);
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

  const unsigned u = M2U(m);
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

size_t Vread(double d[static VL], const size_t V, FILE f[static 1])
{
  return fread(d, sizeof(double) * VL, V, f);
}

size_t Vwrite(const double d[static VL], const size_t V, FILE f[static 1])
{
  return fwrite(d, sizeof(double) * VL, V, f);
}
