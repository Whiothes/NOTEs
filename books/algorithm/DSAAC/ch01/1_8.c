#include <stdio.h>
#include <math.h>

/* int main() */
/* { */
/*   printf("%d\n", (int)pow(2, 100) % 5); */
/* } */


int main()
{
  int i, ans = 1;
  for (i=1; i<= 100; i++)
  {
    ans *= 2;
    //		ans %= 10;	if this sentence repalced with the next one, still right;
    ans %= 5;
  }

  printf("%d\n", ans % 5);

  return 0;
}
