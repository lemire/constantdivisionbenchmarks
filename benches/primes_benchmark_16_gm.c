// Granlund and Montgomery divisibility

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define N 40000
#define REPTS 1000

bool divisible(const uint16_t v, const uint16_t dbar, const uint16_t thresh) {
  uint16_t temp = v * dbar; // otherwise product is 32 bits per standard
  return temp < thresh;
}

// not sure if we can use one less iteration for 16 bits: assume not
// Newton's method per Warren p 246 & 247
uint16_t gm_multiplicative_inverse(uint16_t d) {
  uint16_t x0 = d + 2 * ((d + 1) & 4);
  uint16_t x1 = x0 * (2 - d * x0);
  uint16_t x2 = x1 * (2 - d * x1);
  // uint16_t x3 = x2 * (2 - d * x2);
  // if (x2 != x3)
  // printf("needed last iter");
  return x2;
}

int count_primes_under_N(int junkparam) {
  int primectr = 0;
  static uint16_t prime_inv_vals[N], prime_thresh[N];

  // 2 is a prime, but add it to count later.
  primectr = 0;

  for (uint16_t n = 3; n < N; n += 2) {
    bool isprime = true;
    for (int j = 0; j < primectr; ++j) {
      if (divisible(n, prime_inv_vals[j], prime_thresh[j])) {
        isprime = false;
        break;
      }
    }
    if (isprime) {
      prime_thresh[primectr] = (0xffff / n);
      prime_inv_vals[primectr++] = gm_multiplicative_inverse(n);
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

/*gcc -std=gnu99 -O3 -march=native -mbmi2 primes_benchmark_16_gm.c
owen@strife:~/lemur-git/FasterModulo/code/benches$ !per
 perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

       4368.343447      task-clock (msec)         #    1.000 CPUs utilized
                 3      context-switches          #    0.001 K/sec
                 0      cpu-migrations            #    0.000 K/sec
                55      page-faults               #    0.013 K/sec
    16,735,548,863      cycles                    #    3.831 GHz
   <not supported>      stalled-cycles-frontend
   <not supported>      stalled-cycles-backend
    80,298,380,278      instructions              #    4.80  insns per cycle
    17,837,133,636      branches                  # 4083.272 M/sec
        16,239,965      branch-misses             #    0.09% of all branches

       4.369155363 seconds time elapsed

 */
