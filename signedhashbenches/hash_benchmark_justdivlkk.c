#include "common.h"



int32_t fastdivD(int32_t a, uint64_t M) {
  // generate two multiplications and can be manually fixed to use only 1 (cf
  // hacked libdivide_benchmark.c: TODO)
  int64_t highbits = ((__int128_t)a * (__int128_t)M) >> 64;
  return highbits + ((uint32_t)a >> 31);
}

static inline int32_t fastmodD(int32_t a, uint64_t M, int32_t d) {
  int32_t quotient = fastdivD(a, M);
  return a - quotient * d;
}

#if D <= 1
#warning "Expect problems because D<=1"
#endif

int main() {
  int32_t seed = INITSEED;
  // fails for D = 1 or any negative D.
  uint64_t M = UINT64_C(0xFFFFFFFFFFFFFFFF) / (D) + 1 + ((D &(D-1))==0 ? 1 : 0);
  int32_t d = D;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmodD(seed * MULTIPLIER + CONSTANTADD, M, d) ;
  }
  return seed;
}
