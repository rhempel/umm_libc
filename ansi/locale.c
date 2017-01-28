#include <locale.h>
#include <limits.h>

static struct lconv lconv = 
{
  ".", "", "", "", "", "", "", "", "", "",
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
};

struct lconv *localeconv()
{
  return (struct lconv *) &lconv;
}
