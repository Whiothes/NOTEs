#include <stdlib.h>

char          pear[40];
static double peach;
int           mango = 13;
static long   melon = 2001;

int main() {
    int i   = 3, j, *ip;
    ip      = malloc(sizeof(i));
    pear[5] = i;
    peach   = 2.8 * mango;
    printf("The stack top is near: %p\n", &i);
}
