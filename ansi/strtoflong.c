/* strtoflong.c - Special number conversion for embedded Lua.
 *
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

#define MAX_DECIMAL_DIGITS 8

static const float pow10[MAX_DECIMAL_DIGITS] = {((float)1.0e-1),  ((float)1.0e-2),
	                                        ((float)1.0e-3),  ((float)1.0e-4),
	                                        ((float)1.0e-5),  ((float)1.0e-6),
	                                        ((float)1.0e-7),  ((float)1.0e-8)  };

union float_long
{
    float f;
    long l;
};
                                         
long strtoflong(const char *s, const char **endp)
  {
  union float_long val;
  
  float decimal   = (float)0.0;
  int   exp       = 0;

  int   expsign   = 0;
  int   point     = 0;
  int   mantsign;
  
  char i;
  const float *fp;

  // Scan past blanks
  while (isspace(*s))
    ++s;
  
  mantsign = 1;  /* assume positive */
 
  switch( *s )
    {
    case '-': mantsign = -1; // Note fallthrough to increment!
    case '+': s++;
    }
    
  // Now we're pointing at the first digits, so convert to a number
  // until we reach a non-digit
  
  for( val.l = 0; isdigit(i = *s); ++s )
    val.l = (val.l * 10) + (i - '0');
  
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
  // done, but check for an exponent and covert digitra after that...
  
  if (tolower(*s) == 'e')
    {
    // We've got either an E or an e, so skip past it and look for a
    // sign character...
    ++s;
    
    expsign = 1;

    switch( *s )
      {
      case '-': expsign = -1; // Note fallthrough to increment!
      case '+': s++;
      }
    
    // Now convert all of the exponent digits, but first add the decimal part
    // of the number to the value so far...
    
    val.f = (val.l * ((float)1.0)) + decimal;

    for( exp = 0; isdigit(i = *s); ++s )
      exp = (exp * 10) + (i - '0');
    
    // And now scale the result - do it using brute force division or
    // multiplication by 10
    
    while( 0 != exp )
      val.f = val.f * ((float)(1 == expsign ? ((float)10.0) : ((float)0.1)));
    }
  
  // Now we're done converting the result - so return the value that makes the
  // most sense for the number that was passed as a string...
  
  // NOTE WELL THAT LUA USES UNARY MINUS TO NEGATE NUMBERS RETURNED BY THIS
  // FUNCTION, AND IT IS IMPOSSIBLE TO FIGURE OUT IF WE'RE LOOKING AT A FLOAT
  // OR A LONG AT THAT LEVEL!!!
  //
  // IT'S USELESS TO USE THE MANTISSA SIGN HERE, SO MAKE SURE THAT IF YOU
  // WANT NEGATIVE FLOATS TO MULTIPLY BY -1.0 SEPARATELY, AND FOR GOODNESS
  // SAKE DON'T PUT A UNARY MINUS IN FRONT OF THE NUMBER!
  
  if( 0 != expsign )
    // already converted to floating value!
    val.f = val.f;
  else if( (0 != decimal) || (0 != point) )
    // not converted yet!
    val.f = ((val.l * ((float)1.0)) + decimal);
  else
    // No conversion necessary!
    val.l = val.l;

  // Don't forget to update the endpointer if it's non-NULL

  if (endp != (const char **)NULL)
    *endp = s;

  // This part is wierd, we always return a long, but if you KNOW that
  // the number has decimal formatting, you can use it as a float...
  
  return val.l;
  }
