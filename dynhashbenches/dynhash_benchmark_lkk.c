#include "common.h"



uint32_t fastmodD(uint32_t a, uint64_t M, uint32_t D) {
  uint64_t lowbits = M * a; // high 64 bits of this mult is the division
  // we use the low bits to retrieve the modulo
  return ((__uint128_t)lowbits * D) >> 64;
}

int main(int argc, char*argv[]) {
  uint32_t seed = INITSEED;
  uint32_t D =  strtol(argv[1], NULL, 0);
  uint64_t M = UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmodD(seed * MULTIPLIER + CONSTANTADD, M, D) ;
  }
  return seed;
}
