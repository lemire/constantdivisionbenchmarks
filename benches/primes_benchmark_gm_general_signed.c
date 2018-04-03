// Granlund and Montgomery signed divisibility,
// general version for all dividends and divisors, hopefully.
// This had bugs for a long time.   See sanitycheck_primes_gm.c
// and sanitycheck_primes_gm1.c


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 40000
#define REPTS 1000

// bitwise rotation, hopefully recognized by compiler
// 1 <= n <= 31.
// See Regehr blog on how n=0 is officially undefined behaviour
// https://blog.regehr.org/archives/1063
// but, if the compiler generates the right instruction, we can
// get away without without artificially hurting the GM implementation.
uint32_t rotr32 (uint32_t x, uint32_t n)
{
  return (x>>n) | (x<<(32-n));
}

struct intpair {uint32_t e; int32_t dbar;};


// cf sanity_check_primes_gm for a "more signed" version that is probably
// costlier.
// just use absolute values.
bool divisible( const int32_t v, const struct intpair ip, const uint32_t thresh) {
  uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  uint32_t q0 = abs_v*ip.dbar;
  return rotr32(q0, ip.e) <= thresh;
}



// Newton's method per Warren p 246 & 247
struct intpair gm_multiplicative_inverse(int32_t d) {
  struct intpair retval;
  int32_t abs_d = (d ^ (d>>31)) - (d>>31); // -2**31 might be issue, but tests ok
  retval.e = __builtin_ctz(abs_d);
  int32_t d_odd = abs_d >> retval.e;
  int32_t x0 = d_odd + 2*((d_odd+1) & 4);
  int32_t x1 = x0 * (2 - d_odd *x0);
  int32_t x2 = x1 * (2 - d_odd *x1);
  retval.dbar = x2 * (2 - d_odd *x2);
  return retval;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static struct intpair prime_inv_vals[N];
  static int32_t prime_thresh[N];
           

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (int32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_inv_vals[j], prime_thresh[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      int32_t abs_n = (n ^ (n>>31)) - (n>>31); 
      prime_thresh[primectr] = 0xffffffffU / abs_n;
      prime_inv_vals[primectr++] = gm_multiplicative_inverse(n);
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

