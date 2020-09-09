#include "msr.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>

// see https://github.com/intel/msr-tools

int msr_mycpu()
{
  return sched_getcpu();
}

int msr_open(const int cpu)
{
  char fn[24];
  return ((cpu >= 0) ? ((sprintf(fn, "/dev/cpu/%d/msr", cpu) > 13) ? open(fn, O_RDONLY) : -3) : -2);
}

int msr_read(const int cfd, const uint32_t msr, uint64_t *const val)
{
  return (val ? ((pread(cfd, val, sizeof(*val), (off_t)msr) == (ssize_t)sizeof(*val)) ? 0 : -1) : -2);
}

int msr_write(const int cfd, const uint32_t msr, const uint64_t val)
{
  return ((pwrite(cfd, &val, sizeof(val), (off_t)msr) == (ssize_t)sizeof(val)) ? 0 : -1);
}

int msr_close(const int cfd)
{
  return close(cfd);
}
