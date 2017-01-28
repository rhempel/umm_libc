/*
 * (c) Copyright 2007 Ralph Hempel
 */
#include	<string.h>

void *
memfind(const void *s1, const void *s2, size_t n1)
{
	register const unsigned char *p1 = s1, *p2 = s2, *e1;

  size_t n2 = strlen(s2);
  
  if( n2 > n1 )
  	return( (void *)0 );
  	
  if( n1 < 1 )
  	return( (void *)s1 );
   else {
   	// Set up the end of the search...
   	e1 = &(p1[n1-n2+1]);

		while( p1 < e1 ) {
			if( *p1 == *p2 ) {
				if( 0 == memcmp(p1+1,p2+1,n2-1) )
					return( (void *)p1 );
			  }
	    p1++;
			}
	  }
	
  return( (void *)0 );
}
