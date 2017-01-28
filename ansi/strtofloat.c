/* strtofloat.c - Special number conversion for embedded Lua.
 *
 * FIXME - UPDATE THIS DOC!!!
 * All Lua numbers fit into 32 bits, and depending on the context they are
 * interpreted as signed integers or signle precision floats.
 *
 * The problem is that if we need to figure out if the number being converted
 * is an integer or a floating point number, so we have a special routine that
 * returns a 32 bit value that can be formatted either way.
 *
 * If the source text has no decimal point, then the result is interpreted as
 * an integer, otherwise we return a float.
*/

#include <stdlib.h>
#include <ctype.h>

#define MAX_DECIMAL_DIGITS 6

static const float pow10[MAX_DECIMAL_DIGITS] = {((float)1.0e-1),  ((float)1.0e-2),
                                                ((float)1.0e-3),  ((float)1.0e-4),
                                                ((float)1.0e-5),  ((float)1.0e-6)    };
//                                                ((float)1.0e-7),  ((float)1.0e-8)  };

union float_long
{
    float f;
    long l;
};

// This function is only called when there is no chance that the string can be an
// integer...

float strtofloat(const char *s )
  {
//  union float_long val;

  float decimal   = (float)0.0;
  float mantsign  = (float)1.0; /* assume positive */
  int   expsign   = 1;
  
  int   exp       = 0;
  int   point     = 0;

  char i;
  const float *fp;

  // Scan past blanks
  while (isspace(*s))
    ++s;

  switch( *s )
    {
    case '-': mantsign = (float)-1.0; // Note fallthrough to increment!
    case '+': s++;
    }

  // Now we're pointing at the first digits, so convert to a number
  // until we reach a non-digit

  for( decimal = 0; isdigit(i = *s); ++s )
    decimal = (decimal * 10) + (i - '0');

  // Now we're done converting a string of digits, and we may be
  // done, but check for a decimal point and convert any digits
  // after that...

  if (*s == '.')
    {
    // We've got a decimal point! So increment past it and convert the
    // part after the decimal point...

    point = 1;

    for( ++s, fp = &pow10[0]; isdigit(i = *s) && (fp < &pow10[MAX_DECIMAL_DIGITS]); ++s )
      {
      decimal = decimal + (*fp++ * (i - '0'));
      }

    // We've got all the significant digits we can use - scan past the rest
    // of the digits if any...

    while (isdigit(*s))     /* scan past insignificant digits */
      ++s;
    }

  // Now we're done converting all the decimal digits, and we may be
  // done, but check for an exponent and covert digits after that...

  if (tolower(*s) == 'e')
    {
    // We've got either an E or an e, so skip past it and look for a
    // sign character...
    ++s;

    switch( *s )
      {
      case '-': expsign = -1; // Note fallthrough to increment!
      case '+': s++;
      }

    // Now convert all of the exponent digits
    
    //, but first add the decimal part
    // of the number to the value so far...
    //    val.f = (val.l * ((float)1.0)) + decimal;

    for( exp = 0; isdigit(i = *s); ++s )
      exp = (exp * 10) + (i - '0');

    // And now scale the result - do it using brute force division or
    // multiplication by 10

    while( 0 != exp-- )
      decimal = decimal * (1 == expsign ? ((float)10.0) : ((float)0.1));
    }

  return( decimal * mantsign );
  }
