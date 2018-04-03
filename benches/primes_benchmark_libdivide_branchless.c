// divisibility using libdivide, branchless
//gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_libdivide_branchless.c

  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "libdivide.h"

#define N 40000
#define REPTS 1000

bool divisible( const uint32_t v, const struct libdivide_u32_branchfree_t *denom, uint32_t d) {
  return libdivide_u32_branchfree_do(v, denom) * d == v;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static struct libdivide_u32_branchfree_t prime_magics[N];
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
      prime_magics[primectr++] = libdivide_u32_branchfree_gen(n);
    }
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
owen@skylake:~/libdivide$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

      10254.063735      task-clock (msec)         #    1.000 CPUs utilized          
                 5      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                61      page-faults               #    0.006 K/sec                  
    34,782,458,176      cycles                    #    3.392 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
   142,654,735,398      instructions              #    4.10  insns per cycle        
    17,854,788,310      branches                  # 1741.240 M/sec                  
        16,831,434      branch-misses             #    0.09% of all branches        

      10.254204799 seconds time elapsed
*/
