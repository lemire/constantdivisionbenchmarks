#include "common.h"


uint32_t fastmodD(uint32_t a, uint64_t M, uint32_t D) {
  uint64_t quotient = ( (__uint128_t) M * a ) >> 64;// this is the division
  return a - quotient * D;
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
