#ifndef MSR_H
#define MSR_H
#include "common.h"

#ifndef IA32_MPERF
#define IA32_MPERF 0xE7u
#else /* IA32_MPERF */
#error IA32_MPERF already defined
#endif /* ?IA32_MPERF */

#ifndef IA32_APERF
#define IA32_APERF 0xE8u
#else /* IA32_APERF */
#error IA32_APERF already defined
#endif /* ?IA32_APERF */

extern int msr_mycpu();
extern int msr_open(const int cpu);
extern int msr_read(const int cfd, const uint32_t msr, uint64_t *const val);
extern int msr_write(const int cfd, const uint32_t msr, const uint64_t val);
extern int msr_close(const int cfd);

#endif /* !MSR_H */
