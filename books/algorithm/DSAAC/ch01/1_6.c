#include <errno.h>
#include <math.h>
#include <stdio.h>

float func_a(int n)
{
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += 1 / (pow(4, i));
    }
    return sum;
}
float func_b(int n)
{
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i / (pow(4, i));
    }
    return sum;
}

float func_c(int n)
{
    float sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += pow(i, 2) / (pow(4, i));
    }
    return sum;
}
float func_d(int n)
{
    float sum = 0;
    for (int i = 0; i < n; ++i) {
      sum += pow(i, 3) / (pow(4, i));
    }
    return sum;
}

int main()
{
    int n = 1000;
    printf("sum of a(%d) is %f\n", n, func_a(n));
    printf("sum of b(%d) is %f\n", n, func_b(n));
    printf("sum of c(%d) is %f\n", n, func_c(n));
}
