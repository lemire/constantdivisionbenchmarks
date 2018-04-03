// divisibility using libdivide, branchy and signed
//gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_libdivide_signed.c

  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "libdivide.h"

#define N 40000
#define REPTS 1000

bool divisible( const int32_t v, const struct libdivide_s32_t *denom, int32_t d) {
  return libdivide_s32_do(v, denom) * d == v;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static struct libdivide_s32_t prime_magics[N];
  static int32_t primes[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (int32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_magics + j, primes[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      primes[primectr] = n;
      prime_magics[primectr++] = libdivide_s32_gen(n);
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
