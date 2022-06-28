#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void do_pragma()
{
  close(0);
  if (open("/dev/tty", O_RDONLY, 0666) != 0) {
    goto nope;
  }

  close(1);
  if (open("/dev/tty", O_WRONLY, 0666) != 1) {
    goto nope;
  }

  execl("emacs", "-nw", "hello.txt", 0);

nope:
  printf("You are in a maze of twisty compiler features, all different");
}

int main()
{
  do_pragma();
  return 0;
}
