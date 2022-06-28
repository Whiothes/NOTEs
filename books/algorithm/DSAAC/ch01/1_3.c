#include <stdio.h>

void PrintDigit(unsigned int x) { printf("%d", x); }

void PrintOut(unsigned int N)
{
  if (N >= 10) {
    PrintOut(N/10);
  }
  PrintDigit(N);
}

int main() {
  PrintOut(2);
  printf("\n");
  PrintOut(1111);
  printf("\n");
  return 0;
}
