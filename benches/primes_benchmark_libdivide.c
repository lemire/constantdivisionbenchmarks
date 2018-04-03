// divisibility using libdivide, branchy
//gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_libdivide.c

  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "libdivide.h"

#define N 40000
#define REPTS 1000

bool divisible( const uint32_t v, const struct libdivide_u32_t *denom, uint32_t d) {
  return libdivide_u32_do(v, denom) * d == v;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static struct libdivide_u32_t prime_magics[N];
  static uint32_t primes[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (uint32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_magics + j, primes[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      primes[primectr] = n;
      prime_magics[primectr++] = libdivide_u32_gen(n);
    }
  }
  return (1+primectr)^junkparam;  // allow for 2.
}


int  main() {
  int acc = 0;

  // seems enough to confuse compiler into looping
  for (int rept=0; rept < REPTS; ++rept)
    acc ^= count_primes_under_N(acc);

   printf("There are %d\n",acc);
   return 0;
}

/*
gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_libdivide.c
owen@skylake:~/libdivide$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

      13694.702296      task-clock (msec)         #    1.000 CPUs utilized          
                10      context-switches          #    0.001 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                60      page-faults               #    0.004 K/sec                  
    46,453,322,641      cycles                    #    3.392 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
   157,321,728,421      instructions              #    3.39  insns per cycle        
    35,659,840,466      branches                  # 2603.915 M/sec                  
       594,494,016      branch-misses             #    1.67% of all branches        

      13.695531750 seconds time elapsed
*/
