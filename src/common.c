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
#ifdef USE_INTEL
static_assert(sizeof(extended) == 16, "sizeof(extended) != 16");
#endif /* USE_INTEL */
static_assert(sizeof(scomplex) == 8, "sizeof(scomplex) != 8");
static_assert(sizeof(dcomplex) == 16, "sizeof(dcomplex) != 16");
