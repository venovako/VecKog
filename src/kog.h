#ifndef KOG_H
#define KOG_H

#ifdef TEST
#if (TEST == 1)
#ifndef BACKSCALE
#define BACKSCALE
#endif /* !BACKSCALE */
#elif (TEST == 2)
#ifndef USE_DLASV2
#define USE_DLASV2
#endif /* !USE_DLASV2 */
#endif /* ?TEST */
#endif /* TEST */

#include "vec.h"

#include "dkog.h"
#include "zkog.h"

#endif /* !KOG_H */
