/**
 *   @file     11fig13.c
 *   @date     2019-11-08
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    use pthread_mutex_timedlock() to avoid blocking indefinitely
 */
#include <pthread.h>

#include "apue.h"

int main() {
#if defined(__linux__)
    int             err;
    struct timespec tout;
    struct tm*      tmp;
    char            buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked");
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);

    tout.tv_sec += 10;  // 10 seconds from now

    err = pthread_mutex_timedlock(&lock, &tout);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n", buf);
    if (err == 0) {
        printf("mutex locked again!\n");
    } else {
        printf("can't lock mutex again: %s\n", strerror(err));
    }
    exit(0);

#endif  // __linux__
}
