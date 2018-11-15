#include "common.h"



static inline uint32_t fastmodD(int32_t a, uint64_t M, uint32_t d) {
    uint64_t lowbits = M * a; // high 64 bits of this mult is the division
    // we use the low bits to retrieve the modulo
    int32_t highbits = ((__uint128_t) lowbits * (uint64_t) d) >> 64;
    return highbits - ((d - 1) & (a >> 31));
}

int main(int argc, char*argv[]) {
  uint32_t seed = INITSEED;
  uint32_t D =  strtol(argv[1], NULL, 0);
  if(D<=1) printf("Expect problems because D<=1");
  uint64_t M = UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1 + ((D &(D-1))==0 ? 1 : 0);
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmodD(seed * MULTIPLIER + CONSTANTADD, M, D) ;
  }
  return seed;
}
