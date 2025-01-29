/****************************************************************************

COPYRIGHT NOTICE:

  The source code in this file is provided free of charge
  to the author's consulting clients.  It is in the
  public domain and therefore may be used by anybody for
  any purpose.

AUTHOR:

  Will Naylor

****************************************************************************/

#include "wnlib.h"

#include "wnvect.h"



/*****************************************************************

  This code is the inner loop of various n^3 algorithms, so it must
  be fast.  That is why this code is so ugly.

*****************************************************************/
double wn_dot_vects
(
  double *vect1,
  double *vect2,
  int len
)
{
  double result;
  int i;

  result = 0.0;
  for (i = 0; i < len; ++i)
  {
    result += vect1[i] * vect2[i];
  }
  return result;
}
