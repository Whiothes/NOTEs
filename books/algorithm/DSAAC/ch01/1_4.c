#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PrintContent(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        perror(fname);
    }

    char line[BUFSIZ];
    bzero(line, BUFSIZ);
    while (fgets(line, BUFSIZ, fp)) {
        char *p = strstr(line, "#include");
        if (p) {
            char *p1 = strstr(p, "<");
            if (p1) {
                char *p2 = strstr(p, ">");
                printf("%ld\n", p1 - p);
                printf("%ld\n", p2 - p);
                char *fn = (char *)malloc(sizeof(char) * (p2 - p1 + 5));
                strncpy(fn, p1 + 1, p2 - 1 - p1);
                PrintContent(fn);
            }
        }
        printf("%s\n", line);
    }

    return 0;
}

int main() { PrintContent("test.c"); }
