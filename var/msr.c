#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* !_GNU_SOURCE */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int msr_open(const int cpu)
{
  char fn[24];
  return ((cpu >= 0) ? ((sprintf(fn, "/dev/cpu/%d/msr", cpu) > 13) ? open(fn, O_RDONLY) : -3) : -2);
}

static int msr_read(const int cfd, const uint32_t msr, uint64_t *const val)
{
  return (val ? ((pread(cfd, val, sizeof(*val), (off_t)msr) == (ssize_t)sizeof(*val)) ? 0 : -1) : -2);
}

static int msr_write(const int cfd, const uint32_t msr, const uint64_t val)
{
  return ((pwrite(cfd, &val, sizeof(val), (off_t)msr) == (ssize_t)sizeof(val)) ? 0 : -1);
}

static int msr_close(const int cfd)
{
  return close(cfd);
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    (void)fprintf(stderr, "%s CPU MSR\n", *argv);
    return EXIT_FAILURE;
  }

  const int cpu = atoi(argv[1]);
  const uint32_t msr = (uint32_t)strtoul(argv[2], (char**)NULL, 0);
  const int cfd = msr_open(cpu);
  (void)fprintf(stdout, "msr_open(%d)=%d\n", cpu, cfd);
  if (cfd < 0)
    return EXIT_FAILURE;
  uint64_t val = UINT64_C(0);
  const int ret = msr_read(cfd, msr, &val);
  (void)fprintf(stdout, "msr_read(%d,%X,%p)=%d; msr=%lu\n", cfd, msr, &val, ret, val);
  (void)fprintf(stdout, "msr_close(%d)=%d\n", cfd, msr_close(cfd));
  return (ret ? EXIT_FAILURE : EXIT_SUCCESS);
}
