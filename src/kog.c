#include "kog.h"

#ifdef TEST
#if (TEST & 1)
#ifndef PRINTOUT
#define PRINTOUT stderr
#endif /* !PRINTOUT */
#endif /* TEST & 1 */
#if (TEST & 2)
#ifndef BACKSCALE
#define BACKSCALE TEST
#endif /* !BACKSCALE */
#endif /* TEST & 2 */
#if (TEST & 4)
#ifndef POINTWISE
#define POINTWISE TEST
#endif /* !POINTWISE */
#endif /* TEST & 4 */
#endif /* TEST */

#ifdef VP
#error VP already defined
#else /* !VP */
#ifdef PRINTOUT
#define VP(v) (void)Vprintf(PRINTOUT, #v, (v))
#else /* !PRINTOUT */
#define VP(v) (void)0
#endif /* ?PRINTOUT */
#endif /* ?VP */

#ifdef MP
#error MP already defined
#else /* !MP */
#ifdef PRINTOUT
#define MP(m) (void)Mprintf(PRINTOUT, #m, (m))
#else /* !PRINTOUT */
#define MP(m) (void)0
#endif /* ?PRINTOUT */
#endif /* ?MP */

#include "dkog1.c"
#include "dkog.c"
#include "zkog1.c"
#include "zkog.c"
