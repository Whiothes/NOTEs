#include <stdio.h>

#define TOTAL_ELEMENTS (sizeof(array))

int array[] = {23, 34, 12, 17, 204, 99, 16};

int main()
{
  int d = -1, x;
  if (d <= TOTAL_ELEMENTS - 2) {
    printf("hello");
    x = array[d + 1];
  };
  printf("%d\n", x);
}
