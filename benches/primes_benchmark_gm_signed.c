// Granlund and Montgomery signed divisibility,
// knowing d is odd, but dividends
// are potentially negative (even though that won't happen)
// for odd divisors only

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

// it is massively faster (mostly due to better instr/cycle than reduced instr)
// to use the unsigned form, at least on Ryzen and GCC
#define USE_UNSIGNED

#ifdef USE_UNSIGNED

bool gm_divisible( const int32_t v, const  int32_t dbar, const uint32_t thresh1) {
  uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  uint32_t q0 = abs_v*dbar;
  return q0 <= thresh1;
}
  
#else

bool gm_divisible( const int32_t v, const  int32_t dbar, const int32_t thresh1, const int32_t thresh2) {
  return (uint32_t) (v*dbar-thresh1) <= (uint32_t) thresh2;
}

#endif

// Newton's method per Warren p 246 & 247
int32_t gm_multiplicative_inverse(int32_t d) {
  int32_t abs_d_odd = (d ^ (d>>31)) - (d>>31); // -2**31 might be issue
  int32_t x0 = abs_d_odd + 2*((abs_d_odd+1) & 4);
  int32_t x1 = x0 * (2 - abs_d_odd *x0);
  int32_t x2 = x1 * (2 - abs_d_odd *x1);
  return x2 * (2 -abs_d_odd *x2);
}


int count_primes_under_N(int junkparam) {
  int primectr=0;
#ifdef USE_UNSIGNED
  static int32_t prime_inv_vals[N];
  static uint32_t prime_thresh[N];
#else
  static int32_t prime_inv_vals[N], prime_thresh_low[N], prime_thresh2[N];
#endif
  
  // 2 is a prime, but add it to count later.
  primectr=0;

  for (int32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
#ifdef USE_UNSIGNED
      if (gm_divisible(n, prime_inv_vals[j], prime_thresh[j])) {
#else
	      if (gm_divisible(n, prime_inv_vals[j], prime_thresh_low[j], prime_thresh2[j])) {
#endif		
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      uint32_t abs_d = (n ^ (n>>31)) - (n>>31); // -2**31 might be issue
#ifdef USE_UNSIGNED
      prime_thresh[primectr] = (0xffffffff / n);
#else
      prime_thresh_low[primectr]  = -((0x80000000U / abs_d));
      prime_thresh2[primectr]  = -prime_thresh_low[primectr] + ((0x7fffffff / abs_d));
#endif

      prime_inv_vals[primectr++] = gm_multiplicative_inverse(n);
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

