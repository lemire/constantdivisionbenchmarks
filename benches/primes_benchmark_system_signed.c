// use signed % operator to determine divisibility
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

bool divisible( const int32_t v, const int32_t d) {
  return v%d == 0;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static int32_t prime_vals[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (int32_t n=3; n < N; n += 2) {
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
