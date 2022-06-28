#include <stdio.h>
#include <string.h>

#define DUMBCOPY                                                               \
    do {                                                                       \
        for (i = 0; i < 65536; ++i)                                            \
            dst[i] = src[i];                                                   \
    } while (0)

#define SMARTCOPY memcpy(dst, src, 65536)

int main() {
    char src[65536], dst[65536];
    int i, j;


    for (j = 0; j < 100; j++) {
        /* SMARTCOPY; */
        DUMBCOPY;
    }
}
