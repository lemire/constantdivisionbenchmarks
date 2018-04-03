// using the Lemire divisibility check

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define N 40000
#define REPTS 1000

uint32_t lkk_mvalue(const uint16_t d) { return 1 + (0xffffffffULL / d); }

bool lkk_divisible(const uint16_t v, const uint32_t mval) {
  return v * mval < mval;
}

int count_primes_under_N(int junkparam) {
  int primectr = 0;
  static uint32_t prime_mvals[N];

  // 2 is a prime, but add it to count later.
  primectr = 0;

  for (uint16_t n = 3; n < N; n += 2) {
    bool isprime = true;
    for (int j = 0; j < primectr; ++j) {
      if (lkk_divisible(n, prime_mvals[j])) {
        isprime = false;
        break;
      }
    }
    if (isprime)
      prime_mvals[primectr++] = lkk_mvalue(n);
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
/*

gcc -O3 -march=native -mbmi2 primes_benchmark_16_lkk.c
owen@strife:~/lemur-git/FasterModulo/code/benches$ perf stat ./a.out
There are 4203

 Performance counter stats for './a.out':

       3627.992253      task-clock (msec)         #    1.000 CPUs utilized
                 3      context-switches          #    0.001 K/sec
                 0      cpu-migrations            #    0.000 K/sec
                53      page-faults               #    0.015 K/sec
    14,045,503,255      cycles                    #    3.871 GHz
   <not supported>      stalled-cycles-frontend
   <not supported>      stalled-cycles-backend
    71,310,304,248      instructions              #    5.08  insns per cycle
    17,837,001,683      branches                  # 4916.494 M/sec
        16,046,660      branch-misses             #    0.09% of all branches

       3.628693118 seconds time elapsed
               */
