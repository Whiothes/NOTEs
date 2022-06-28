#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float sum (int N)
{
  float sum = 0;
  for (int i = abs(N/2); i <= N; ++i)
  {
    sum += (float) 1/i;
  }
  return sum;
}

int main(int argc, char *argv[])
{
  printf("sum is %f\n", sum(atoi(argv[1])));
}
