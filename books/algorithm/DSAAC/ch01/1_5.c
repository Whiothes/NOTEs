#include <math.h>
#include <stdio.h>

void X_cmp() {

  for (int i = 1; i < 10; i++) {
    printf("log(%d) < %d: ", i, i);
    float x = log(i);
    float y = i;
    printf("%f < %f is", x, y);
    if (x < y)
      printf("true");
    else
      printf("false");
    printf("\n");
  }

}


void AB_cmp()
{
  for (int i = 1; i < 10; i++) {
    /* if (logX_cmp(log2(i), i) < 0) { */
    /*   printf("%f < %d : true\n", log2(i), i); */
    /* } */

    for (int j = 1; j < 3; j++) {
      printf("log(%d^%d) = %dlog%d: ", i, j, j, i);
      float x = log(pow(i, j));
      float y = j * log(i);
      printf("%f == %f is ", x, y);
      if (x == y)
        printf("true");
      else
        printf("false");
      printf("\n");
    }
  }

}


int main()
{
  X_cmp();
  AB_cmp();
}
