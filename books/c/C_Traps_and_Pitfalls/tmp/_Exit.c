#include <stdio.h>
#include <string.h>

#include <unistd.h>

int  glob  = 6;
char buf[] = "anonymalias\n";

int main()
{
  int   var;
  pid_t pid;

  var = 8;

  if (write(STDOUT_FILENO, buf, strlen(buf)) != strlen(buf)) {
    fprintf(stderr, "write error");
    return 0;
  }

  printf("before fork() ... \n");

  if ((pid = fork()) == -1) {
    fprintf(stderr, "fork error");
  }

  if (pid == 0) {
    glob++;
    var++;
  } else {
    sleep(2);
  }

  printf("parent process id: %d ", getppid());

  printf("process id: %d, glob: %d, var: %d\n", getpid(), glob, var);

  return 0;
}
