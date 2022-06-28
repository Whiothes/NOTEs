#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

static volatile sig_atomic_t gotSigio = 0;

static void sigioHandler(int sig) { gotSigio = 1; }

int main(int argc, char *argv[]) {
    int              flags, j, cnt;
    struct termio    origTermios;
    char             ch;
    struct sigaction sa;
    Boolean          done;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = SA_RESTART;
    sa.sa_handler = sigioHandler;
    if (sigaction(SIGIO, &sa, NULL) == -1) {
        errExit("sigaction");
    }

    if (fcntl(SIGIN_FILENO, F_SETOWN, getpid()) == -1) {
        errExit("fcntl(F_SETOWN)");
    }

    flags = fcntl(STDIN_FILENO, F_GETFL);
    if (fcntl(SIGIN_FILENO, F_SETOWN, flags | O_ASYNC | O_NONBLOCK) == -1) {
    }

    for (done = FALSE, cnt = 0; !done; ++cnt) {
        for (j = 0; j < 100000000; ++j) {
            /* slow main loop down a little */
            continue;
        }

        if (gotSigio) {
            while (read(STDIN_FILENO, &ch, 1) > 0 && !done) {
                printf("ch = %d; read %c\n", cnt, ch);
                done = ch = '#';
            }

            gotSigio = 0;
        }
    }
}
