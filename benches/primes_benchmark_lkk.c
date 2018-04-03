// using the Lemire divisibility check, version does not handle
// divisor 1.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

uint64_t lkk_mvalue(const uint32_t d) {
  return 1 + (UINT64_C(0xffffffffffffffff) / d);
}

// does not properly handle 1 (M=0, consistenly would return false)
bool lkk_divisible( const uint32_t v, const uint64_t mval) {
  return v*mval < mval;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static uint64_t prime_mvals[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (uint32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (lkk_divisible(n, prime_mvals[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime)
      prime_mvals[primectr++] = lkk_mvalue(n);
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
owen@skylake:~/libdivide$ gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_lkk.c
owen@skylake:~/libdivide$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

       4547.753913      task-clock (msec)         #    1.000 CPUs utilized          
                 3      context-switches          #    0.001 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                57      page-faults               #    0.013 K/sec                  
    15,426,275,612      cycles                    #    3.392 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
    71,310,608,100      instructions              #    4.62  insns per cycle        
    17,837,059,952      branches                  # 3922.169 M/sec                  
        14,305,085      branch-misses             #    0.08% of all branches        

       4.547894649 seconds time elapsed

*/
