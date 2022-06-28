/**
 *   @file     01fig09.c
 *   @date     2020-05-20
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    TCP daytime server
 */

#include <time.h>

#include "unp.h"

int main(int argc, char **argv) {
    int                listenfd, connfd;
    struct sockaddr_in serveraddr;
    char               buff[MAXLINE];
    time_t             ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family      = AF_INET;
    serveraddr.sin_port        = htons(AF_INET);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    Listen(listenfd, LISTENQ);

    for (;;) {
        connfd = Accept(listenfd, NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
}
