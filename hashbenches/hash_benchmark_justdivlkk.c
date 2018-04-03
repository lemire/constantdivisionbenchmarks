#include "common.h"


//#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))



static inline uint32_t fastmodD(uint32_t a, uint64_t M, uint32_t d) {
  uint64_t quotient = ( (__uint128_t) M * a ) >> 64;// this is the division
  return a - quotient * D;
}

int main() {
  uint32_t seed = INITSEED;
  // fails for D = 1?
  uint64_t M = UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmodD(seed * MULTIPLIER + CONSTANTADD, M, D) ;
  }
  return seed;
}
