// using the Lemire divisibility check.
// Specialized version that does not handle division by +-1 properly

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 40000
#define REPTS 1000

#if 0
/* VERSION DOESN'T MATCH MATH and might not handle -2^31 right */

uint64_t lkk_mvalue_alt(const int32_t d) {
  // to handle negative divisors can just take absolute value of d
#if 1
  // faster than alternative on Haswell
  uint64_t temp = 1 + (0xffffffffffffffffULL / (uint64_t)d);
  return (d & (d - 1) == 0) + temp;
#else
  return 1 + (((__uint128_t)1) << 64) / d;
#endif
}

/* when v is negative, we want prod (as a signed quantity)
   to be slightly negative (more than -M).
   when v is positive, we want prod to be only slightly positive
*/

bool lkk_divisible_alt(const int32_t v, const uint64_t mval) {
  uint64_t prod = v * mval;

  /*
  if (v < 0)
    return prod > (uint64_t)(-mval);
  return prod < mval;
  */

  // if v is negative, we want to negate product
  // using 1s complement, not sure if omitted +1 can bite us
  // yes, it does for -1 / 3.  So have to use 2's complement.
  int64_t maybe_negater = v >> 31;

  // unsure about strict inequality.  Think I need unsigned <
  // trying unsigned.... only have nonneg in this application anyway
  return ((prod ^ maybe_negater) + (maybe_negater & 1)) < mval;
}
#endif

/* version matching paper. Reduction to the unsigned case */


uint64_t lkk_mvalue(const int32_t d) {
  uint32_t abs_d = (d ^ (d>>31)) - (d>>31);
  return 1 + (UINT64_C(0xffffffffffffffff) / abs_d);
}

// d==1 gives M=0 and wrong results. 
bool lkk_divisible(const int32_t v, const uint64_t mval) {
  const uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  return abs_v*mval < mval;  
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

int main() {
  int acc = 0;

  // seems enough to confuse compiler into looping
  for (int rept = 0; rept < REPTS; ++rept)
    acc ^= count_primes_under_N(acc);

  printf("There are %d\n", acc);
  return 0;
}
