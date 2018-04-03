// using the Lemire divisibility check.  General version for all
// divisors and dividends

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 40000
#define REPTS 1000

/* version matching paper. Reduction to the unsigned case */


uint64_t lkk_mvalue(const int32_t d) {
  uint32_t abs_d = (d ^ (d>>31)) - (d>>31);
  return 1 + (UINT64_C(0xffffffffffffffff) / abs_d);
}

// d==1 gives M=0 and wrong results. Have to check for it.
// if we expect this silly situation to be very rare, might
// go for the branchy version (|| in return stmt)
bool lkk_divisible(const int32_t v, const uint64_t mval) {
  const uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  //  return !mval || (abs_v*mval < mval);  // Owen's painful approach
  return abs_v*mval <= mval-1;  // Daniel's hack, rely on 0 mval wrapping
}


int count_primes_under_N(int junkparam) {
  int primectr = 0;
  static uint64_t prime_mvals[N];

  // 2 is a prime, but add it to count later.
  primectr = 0;

  for (int32_t n = 3; n < N; n += 2) {
    bool isprime = true;
    for (int j = 0; j < primectr; ++j) {
      if (lkk_divisible(n, prime_mvals[j])) {
        isprime = false;
        break;
      }
    }
    if (isprime) {
      prime_mvals[primectr++] = lkk_mvalue(n);
    }
  }
  return (1 + primectr) ^ junkparam; // allow for 2.
}

int  main() {
  int acc = 0;

  // seems enough to confuse compiler into looping
  for (int rept = 0; rept < REPTS; ++rept)
    acc ^= count_primes_under_N(acc);

  printf("There are %d\n", acc);
  return 0;
}
