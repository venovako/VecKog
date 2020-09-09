#include "kog.h"

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
#include "zkog1.c"

#include "dkog8.c"
#include "zkog8.c"
