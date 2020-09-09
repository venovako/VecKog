#ifndef KOG_H
#define KOG_H

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
#if (TEST & 8)
#ifndef USE_MSR
#define USE_MSR TEST
#endif /* !USE_MSR */
#endif /* TEST & 8 */
#endif /* TEST */

#include "vec.h"

#include "dkog1.h"
#include "zkog1.h"

#include "dkog8.h"
#include "zkog8.h"

#endif /* !KOG_H */
