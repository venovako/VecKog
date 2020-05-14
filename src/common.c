#include "common.h"

static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");
#ifdef FINT64
static_assert(sizeof(fint) == 8, "sizeof(fint) != 8");
static_assert(sizeof(fnat) == 8, "sizeof(fnat) != 8");
#else /* FINT32 */
static_assert(sizeof(fint) == 4, "sizeof(fint) != 4");
static_assert(sizeof(fnat) == 4, "sizeof(fnat) != 4");
#endif /* ?FINT64 */
static_assert(sizeof(float) == 4, "sizeof(float) != 4");
static_assert(sizeof(double) == 8, "sizeof(double) != 8");
static_assert(sizeof(long double) >= 8, "sizeof(long double) < 8");
#ifndef NDEBUG
static_assert(sizeof(float _Complex) == 8, "sizeof(float _Complex) != 8");
static_assert(sizeof(double _Complex) == 16, "sizeof(double _Complex) != 16");
static_assert(sizeof(long double _Complex) >= 16, "sizeof(long double _Complex) < 16");
#endif /* !NDEBUG */
#ifndef USE_EXTENDED
static_assert(sizeof(__float128) == 16, "sizeof(__float128) != 16");
#ifndef NDEBUG
static_assert(sizeof(__float128 _Complex) == 32, "sizeof(__float128 _Complex) != 32");
#endif /* !NDEBUG */
#endif /* !USE_EXTENDED */

size_t atoz(const char *const s)
{
  char *e = (char*)NULL;
  const size_t z = ((s && *s) ? (size_t)strtoull(s, &e, 0) : (size_t)0u);
  return ((e && *e) ? (size_t)0u : z);
}

char *dtoa(char s[static 26], const double x)
{
  int l = sprintf((char*)memset(s, 0, (size_t)26u), "%# -25.17E", x);
  if (l <= 0)
    return (char*)NULL;
  char *d = s + 25;
  char *e = strrchr(s, 'E');
  if (e) {
    for (--d; isblank(*d); --d)
      *d = '\0';
    e += 2;
    l = (int)(strchr(e, '\0') - e);
    if (l >= 3)
      return s;
    d = s + 25;
    e += l;
    for (int i = 0; i < l; ++i)
      *--d = *--e;
    for (--d; isdigit(*d); --d)
      *d = '0';
  }
  else
    for (--d; !*d; --d)
      *d = ' ';
  return s;
}

char *xtoa(char s[static 31], const long double x)
{
  int l = sprintf((char*)memset(s, 0, 31u), "%# -30.21LE", x);
  if (l <= 0)
    return (char*)NULL;
  char *d = s + 30;
  char *e = strrchr(s, 'E');
  if (e) {
    for (--d; isblank(*d); --d)
      *d = '\0';
    e += 2;
    l = (int)(strchr(e, '\0') - e);
    if (l >= 4)
      return s;
    d = s + 30;
    e += l;
    for (int i = 0; i < l; ++i)
      *--d = *--e;
    for (--d; isdigit(*d); --d)
      *d = '0';
  }
  else
    for (--d; !*d; --d)
      *d = ' ';
  return s;
}
