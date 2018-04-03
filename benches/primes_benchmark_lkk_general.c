// using the Lemire divisibility check

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

uint64_t lkk_mvalue(const uint32_t d) {
  return 1 + (UINT64_C(0xffffffffffffffff) / d);
}


// pedantic version.  A branchfree version with | is an option, or branchy ||
bool lkk_divisible_slow( const uint32_t v, const uint64_t mval) {
  return !mval || (v*mval < mval);  
}

// pedantic branchless version that's as fast as branchy with perfect
// prediction, thanks to Daniel
bool lkk_divisible( const uint32_t v, const uint64_t mval) {
  return v*mval <= mval-1; // rhs gets really big when mval=0  
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

