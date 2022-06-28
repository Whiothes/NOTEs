#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double F(int n)
{
  return 1 / sqrt(5) * pow(((1 + sqrt(5)) / 2), n) -
         1 / sqrt(5) * pow(((1 - sqrt(5)) / 2), n);
}

int main(int argc, char **argv)
{
  printf("%f\n", F(atoi(argv[1])));
}
