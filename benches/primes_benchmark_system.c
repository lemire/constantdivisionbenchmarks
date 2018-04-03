// use % operator to determine divisibility
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

bool divisible( const uint32_t v, const uint32_t d) {
  return v%d == 0;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static uint32_t prime_vals[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (uint32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_vals[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime)
      prime_vals[primectr++] = n;
  }
  return (1+primectr)^junkparam;  // allow for 2.
}


int main() {
  int acc = 0;

  // seems enough to confuse compiler into looping
  for (int rept=0; rept < REPTS; ++rept)
    acc ^= count_primes_under_N(acc);

   printf("There are %d\n",acc);

   return 0;
}

/*
owen@skylake:~/libdivide$ gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_system.c
owen@skylake:~/libdivide$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

      21196.614785      task-clock (msec)         #    1.000 CPUs utilized          
                 8      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                51      page-faults               #    0.002 K/sec                  
    71,900,330,614      cycles                    #    3.392 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
    71,328,702,652      instructions              #    0.99  insns per cycle        
    17,839,653,713      branches                  #  841.627 M/sec                  
        16,928,026      branch-misses             #    0.09% of all branches        

      21.196753222 seconds time elapsed
*/
