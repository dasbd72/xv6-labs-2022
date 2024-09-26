#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipefd[2];
  int cpid;
  char buf;
  
  if(pipe(pipefd) == -1) {
    printf("pipe failed\n");
    exit(1);
  }

  cpid = fork();
  if (cpid == -1) {
    printf("fork failed\n");
    exit(1);
  }

  if (cpid == 0) { // Child reads from pipe
    // close(pipefd[1]); // Close unused write end
    read(pipefd[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(pipefd[1], "0", 1);
  } else { // Parent writes to pipe
    // close(pipefd[0]); // Close unused read end
    write(pipefd[1], "0", 1);
    read(pipefd[0], &buf, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}
