#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(2, "usage: sleep seconds\n");
    exit(1);
  }

  int duration = atoi(argv[1]);
  printf("Sleeping for %d seconds\n", duration);
  sleep(duration*10);
  exit(0);
}
