// Granlund and Montgomery divisibility

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

struct intpair {uint32_t e; uint32_t dbar;};

bool divisible( const uint32_t v, const struct intpair ip, const uint32_t thresh) {
  return rotr32(v*ip.dbar, ip.e) <= thresh;  // or maybe < 
}

// Newton's method per Warren p 246 & 247
struct intpair gm_multiplicative_inverse(uint32_t d) {
  struct intpair retval;
  retval.e = __builtin_ctz(d);
  uint32_t d_odd = d >> retval.e;
  uint32_t x0 = d_odd + 2*((d_odd+1) & 4);
  uint32_t x1 = x0 * (2 - d_odd *x0);
  uint32_t x2 = x1 * (2 - d_odd *x1);
  retval.dbar = x2 * (2 - d_odd *x2);
  return retval;
}

int count_primes_under_N(int junkparam) {
  int primectr=0;
  static uint32_t prime_thresh[N];
  static struct intpair prime_inv_vals[N];

  // 2 is a prime, but add it to count later.
  primectr=0;

  for (uint32_t n=3; n < N; n += 2) {
    bool isprime=true;
    for (int j=0; j < primectr; ++j) {
      if (divisible(n, prime_inv_vals[j], prime_thresh[j])) {
	isprime = false;
	break;
      }
    }   
    if (isprime) {
      prime_thresh[primectr] = (0xffffffff / n);
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

/*
owen@skylake:~/libdivide$ gcc-6 -std=gnu99 -O3 -march=native primes_benchmark_gm.c
owen@skylake:~/libdivide$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

       4140.479464      task-clock (msec)         #    1.000 CPUs utilized          
                 4      context-switches          #    0.001 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                58      page-faults               #    0.014 K/sec                  
    14,044,767,918      cycles                    #    3.392 GHz                    
   <not supported>      stalled-cycles-frontend  
   <not supported>      stalled-cycles-backend   
    71,394,304,056      instructions              #    5.08  insns per cycle        
    17,836,999,637      branches                  # 4307.955 M/sec                  
        15,577,300      branch-misses             #    0.09% of all branches        

       4.140627056 seconds time elapsed
*/
