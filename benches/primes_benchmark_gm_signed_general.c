// Granlund and Montgomery signed divisibility,
// general version for all dividends and divisors, hopefully.
// Some doubt about divisor -2**31.

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
// GCC-6 on Skylake finds a rorl instruction.
uint32_t rotr32 (uint32_t x, uint32_t n)
{
  return (x>>n) | (x<<(32-n));
}

struct intpair {uint32_t e; int32_t dbar;};

// signed version has 2 thresholds and an addition
// could reduce to unsigned, but would require instr for abs,
// which is probably more expensive
bool divisible( const int32_t v, const struct intpair ip, const int32_t thresh1, const int32_t thresh2) {
  int32_t q0 = v*ip.dbar;
  return (uint32_t) (rotr32(q0,ip.e)+thresh1) <= (uint32_t) thresh2;
}



// Newton's method per Warren p 246 & 247
struct intpair gm_multiplicative_inverse(int32_t d) {
  struct intpair retval;
  int32_t abs_d = d ^ (d>>31) - (d>>31); // -2**31 might be issue
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
  static int32_t prime_thresh_low[N], prime_thresh2[N];
           

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (int32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_inv_vals[j], prime_thresh_low[j], prime_thresh2[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      prime_thresh_low[primectr] = (0x80000000U / (uint32_t) n);
      prime_thresh2[primectr] = prime_thresh_low[primectr] + (0x7fffffff / n);
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
}

