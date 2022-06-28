/**
 *   @file     01fig06.c
 *   @date     2020-05-20
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Version of Figure 1.5 for IPv6
 */

#include "unp.h"

int main(int argc, char **argv) {
    int                 sockfd, n;
    char                recvline[MAXLINE + 1];
    struct sockaddr_in6 serveraddr;

    if (argc != 2) {
        err_quit("usage: %s <IP address>", argv[0]);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin6_family = AF_INET6;
    serveraddr.sin6_port   = htons(AF_INET6);
    if (inet_pton(AF_INET6, argv[1], serveraddr.sin6_addr) < 0) {
        err_quit("inet_pton error");
    }

    if (connect(sockfd, (const struct sockaddr *)&serveraddr,
                sizeof(serveraddr)) < 0) {
        err_sys("conenct error");
    }

    while ((n = read(sockfd, recvline, sizeof(recvline) - 1)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    exit(0);
}
