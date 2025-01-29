#include "wnvect.h"

void wn_scale_vect(double *vect, double scalar, int len)
{
small:
  switch(len)
  {
    case(16):   *(vect++) *= scalar;
    case(15):   *(vect++) *= scalar;
    case(14):   *(vect++) *= scalar;
    case(13):   *(vect++) *= scalar;
    case(12):   *(vect++) *= scalar;
    case(11):   *(vect++) *= scalar;
    case(10):   *(vect++) *= scalar;
    case(9):    *(vect++) *= scalar;
    case(8):    *(vect++) *= scalar;
    case(7):    *(vect++) *= scalar;
    case(6):    *(vect++) *= scalar;
    case(5):    *(vect++) *= scalar;
    case(4):    *(vect++) *= scalar;
    case(3):    *(vect++) *= scalar;
    case(2):    *(vect++) *= scalar;
    case(1):    *(vect++) *= scalar;
    case(0):    return;
    default:
    {
      do
      {
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;
        *(vect++) *= scalar;

        len -= 16;
      }
      while(len > 16);

      goto small;
    }
  }
}

void wn_add_scaled_vect(double *to_vect, double *from_vect, double scalar, int len)
{
small:
  switch(len)
  {
    case(16):   *(to_vect++) += (*(from_vect++))*scalar;
    case(15):   *(to_vect++) += (*(from_vect++))*scalar;
    case(14):   *(to_vect++) += (*(from_vect++))*scalar;
    case(13):   *(to_vect++) += (*(from_vect++))*scalar;
    case(12):   *(to_vect++) += (*(from_vect++))*scalar;
    case(11):   *(to_vect++) += (*(from_vect++))*scalar;
    case(10):   *(to_vect++) += (*(from_vect++))*scalar;
    case(9):    *(to_vect++) += (*(from_vect++))*scalar;
    case(8):    *(to_vect++) += (*(from_vect++))*scalar;
    case(7):    *(to_vect++) += (*(from_vect++))*scalar;
    case(6):    *(to_vect++) += (*(from_vect++))*scalar;
    case(5):    *(to_vect++) += (*(from_vect++))*scalar;
    case(4):    *(to_vect++) += (*(from_vect++))*scalar;
    case(3):    *(to_vect++) += (*(from_vect++))*scalar;
    case(2):    *(to_vect++) += (*(from_vect++))*scalar;
    case(1):    *(to_vect++) += (*(from_vect++))*scalar;
    case(0):    return;
    default:
    {
      do
      {
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;
        *(to_vect++) += (*(from_vect++))*scalar;

        len -= 16;
      }
      while(len > 16);

      goto small;
    }
  }
}

void wn_multiply_vect_by_vect(double *v1, double *v2, int len)
{
small:
  switch(len)
  {
    case(16):   *(v1++) *= *(v2++);
    case(15):   *(v1++) *= *(v2++);
    case(14):   *(v1++) *= *(v2++);
    case(13):   *(v1++) *= *(v2++);
    case(12):   *(v1++) *= *(v2++);
    case(11):   *(v1++) *= *(v2++);
    case(10):   *(v1++) *= *(v2++);
    case(9):    *(v1++) *= *(v2++);
    case(8):    *(v1++) *= *(v2++);
    case(7):    *(v1++) *= *(v2++);
    case(6):    *(v1++) *= *(v2++);
    case(5):    *(v1++) *= *(v2++);
    case(4):    *(v1++) *= *(v2++);
    case(3):    *(v1++) *= *(v2++);
    case(2):    *(v1++) *= *(v2++);
    case(1):    *(v1++) *= *(v2++);
    case(0):    return;
    default:
    {
      do
      {
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);
        *(v1++) *= *(v2++);

        len -= 16;
      }
      while(len > 16);

      goto small;
    }
  }
}

void wn_divide_vect_by_vect(double *v1, double *v2, int len)
{
small:
  switch(len)
  {
    case(16):   *(v1++) /= *(v2++);
    case(15):   *(v1++) /= *(v2++);
    case(14):   *(v1++) /= *(v2++);
    case(13):   *(v1++) /= *(v2++);
    case(12):   *(v1++) /= *(v2++);
    case(11):   *(v1++) /= *(v2++);
    case(10):   *(v1++) /= *(v2++);
    case(9):    *(v1++) /= *(v2++);
    case(8):    *(v1++) /= *(v2++);
    case(7):    *(v1++) /= *(v2++);
    case(6):    *(v1++) /= *(v2++);
    case(5):    *(v1++) /= *(v2++);
    case(4):    *(v1++) /= *(v2++);
    case(3):    *(v1++) /= *(v2++);
    case(2):    *(v1++) /= *(v2++);
    case(1):    *(v1++) /= *(v2++);
    case(0):    return;
    default:
    {
      do
      {
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);
        *(v1++) /= *(v2++);

        len -= 16;
      }
      while(len > 16);

      goto small;
    }
  }
}
