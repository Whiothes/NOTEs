#include <stdio.h>

int main() {
    int a = 1;
    int b = 1;

    /* 编译不通过 */
    /* printf("%d\n", a+++++b); */
    printf("%d\n", a++ + ++b);
}
