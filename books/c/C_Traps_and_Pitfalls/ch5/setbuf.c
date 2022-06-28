#include <stdio.h>
#include <string.h>

int main()
{
  int c;

  /* char buf[BUFSIZ]; */
  char buf[BUFSIZ];
  setbuf(stdout, buf);

  while ((c = getchar()) != EOF) putchar(c);
}
