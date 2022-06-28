#include <stdio.h>

int main() {
  int i  = 0;
  int ch = 0;

  for (i = 1; ch != EOF; ++i) {
    printf("%d: ", i);

    while (ch = getchar(), putchar(ch), ch != EOF && ch != '\n')
      ;
  }
}
