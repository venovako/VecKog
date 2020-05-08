#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  (void)printf("h=%d\n", (DBL_MAX_EXP - 3));
  const double x = sqrt(DBL_MAX);
  (void)printf("sqrt(DBL_MAX)=%#.17e\n", x);
  const double y = fma(x, x, 1.0);
  (void)printf("fma(sqrt(DBL_MAX),sqrt(DBL_MAX),1)=%#.17e\n", y);
  const double z = 1.0 + sqrt(y);
  (void)printf("d=%#.17e\n", z);
  return EXIT_SUCCESS;
}
