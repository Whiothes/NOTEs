#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void handler(int signo) {
    signal(signo, SIG_DFL);
    printf("caught %s\n", strsignal(signo));
    kill(getpid(), signo);
}

int main() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = handler;
    act.sa_flags = 0;

    sigaddset(&act.sa_mask, SIGUSR1); /* to test sigaction */

    sleep(10);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS, &act, NULL);

    int *p = 0;
    *p = 17; /* causes a segmentation fault */
}
