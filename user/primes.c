#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 1){
    fprintf(2, "usage: primes\n");
    exit(1);
  }

  int base, val;
  int prev_num_primes;
  int num_primes = 0;
  int primes[35];
  for (int i = 2; i <= 35; i++) {
    primes[num_primes++] = i;
  }

  while(1) {
    int p[2];
    pipe(p);
    if(fork() == 0) {
      // Child reads from pipe

      close(p[1]);
      // Read prime numbers from pipe
      // The first number in the pipe is the base prime number
      // And the rest of the numbers are the numbers to be sieved
      prev_num_primes = num_primes;
      num_primes = 0;
      read(p[0], &base, sizeof(base));
      for(int i = 0; i < prev_num_primes - 1; i++) {
        read(p[0], &val, sizeof(val));
        if(val % base != 0) {
          primes[num_primes++] = val;
        }
      }
      close(p[0]);
      // Output the prime number
      printf("prime %d\n", base);
      // If there is only the base prime number left,
      // stop creating new processes
      if(prev_num_primes == 1) {
        break;
      }
    } else {
      // Parent writes to pipe

      close(p[0]);
      // Write prime numbers to pipe
      for(int i = 0; i < num_primes; i++) {
        write(p[1], &primes[i], sizeof(primes[i]));
      }
      close(p[1]);
      // Wait for child to finish
      wait(0);
      break;
    }
  }
}
