#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/conf.h>

int iteration = 0;
char crlf[] = {0xd, 0xa, 0};

void handler(int s)
{
  int c = getchar();
  printf("got char %c, at count %d %s", c, iteration, crlf);
  if (c == 'q') {
    system("stty sane");
    exit(0);
  }
}


int main()
{
  sigset(SIGPOLL, handler);
  system("stty raw -echo");
  ioctl(0, I_SETSIG, S_RDNORM);
  for (;; iteration++);
}
