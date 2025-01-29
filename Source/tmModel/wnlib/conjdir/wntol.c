#include "wntol.h"
#include <float.h>

double wn_machine_tolerance(void)
{
  return DBL_EPSILON;  // Machine epsilon for double precision
}
