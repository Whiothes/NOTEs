#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/filio.h>
#include <sys/ioctl.h>

int kbhit()
{
    int i;
    if (ioctl(0, FIONREAD, &i) < 0) {
        if (errno == EBADF) {
            perror("");
        }
    }
    return i;
}

int main()
{
    int i = 0;
    int c = ' ';
    system("stty raw -echo");
    printf("enter 'q' to quit \n");
    for (; c != 'q'; ++i) {
        if (kbhit()) {
            c = getchar();
            printf("\n got %c, on iteration %d", c, i);
        }
    }
    system("stty cooked echo");
}
