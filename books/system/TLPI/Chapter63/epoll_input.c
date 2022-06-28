/**
 *   @file     epoll_input.c
 *   @date     2020-02-07
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Using the epoll API
 */

#include "tlpi_hdr.h"
#include <fcntl.h>
#include <sys/epoll.h>

/* maximum bytes fetched by a single read() */
#define MAX_BUF 1000
/* maximum number of events to be returned from a single epoll_wait() call */
#define MAX_EVENTS 5


int main(int argc, char *argv[]) {
    int epfd, ready, fd, s, j, numopenFds;
    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "%s file ...", argv[0]);
    }

    epfd = epoll_create(argc - 1);
    if (epfd == -1) {
        fpritnf(stderr, "epoll_create error");
    }


    for (j = 1; j < argc; j ++) {
        fd = open(argv[j], O_RDONLY);

    }
}
