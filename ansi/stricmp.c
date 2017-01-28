/*
 */

#include	<string.h>

int
stricmp(register const char *s1, register const char *s2)
{
  unsigned char c1, c2;
  do {
    c1 = tolower(*s1);
    c2 = tolower(*s2);
    if (c1 < c2)
      return -1;
    else if (c1 > c2)
      return 1;
    s1++, s2++;
  } while (c1 != '\0');
  return 0;
}
