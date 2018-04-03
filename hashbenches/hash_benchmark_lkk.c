#include "common.h"


//#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1))



static inline uint32_t fastmodD(uint32_t a, uint64_t M, uint32_t d) {
  uint64_t lowbits = M * a; // high 64 bits of this mult is the division
  // we use the low bits to retrieve the modulo
  return ((__uint128_t)lowbits * d) >> 64;
}

int main() {
  uint32_t seed = INITSEED;
  // apparently fails for D = 1, but ends up working
  uint64_t M = UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmodD(seed * MULTIPLIER + CONSTANTADD, M, D) ;
  }
  return seed;
}
