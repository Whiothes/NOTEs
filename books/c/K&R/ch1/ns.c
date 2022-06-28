#include <stdio.h>

int main(void)
{
  int ns;
  int c;

  ns = 0;
  while ((c = getchar())!= EOF) {
    switch(c) {
      case ' ':
      case '\t':
      case '\n':
        ns++;
        break;
    }
  }

  printf("%d\n", ns);
  return 0;
}
