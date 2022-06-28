#include <stdio.h>
void *
bsearch(key, base0, nmemb, size, compar)
    register const void *key;
const void *base0;
size_t nmemb;
register size_t size;
register int (*compar) __P((const void *, const void *));
{
  register const char *base = base0;
  register int lim, cmp;
  register const void *p;

  for (lim = nmemb; lim != 0; lim >>= 1) {
    p = base + (lim >> 1) * size;
    cmp = *(compar)(key, p);
    if (cmp == 0) {
      return ((void *)p);
    }
    if (cmp > 0) {  /* key > p; move right. */
      base = (char *)p + size;
      lim--;
    }  /* else move left */
    else {

    }
  }
  return NULL;
}
