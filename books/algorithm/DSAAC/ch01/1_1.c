#include <stdio.h>
#include <stdlib.h>


int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int a[n];
    for (int i = 0; i < n; ++i) {
        a[i] = rand();
    }

    qsort(a, n, sizeof(int), cmp);

    return 0;
}
