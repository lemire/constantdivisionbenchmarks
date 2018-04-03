#include "common.h"
#include "libdivide.h"

int32_t fastmod(int32_t x, const struct libdivide_s32_t *denom, int32_t d) {
  return x - libdivide_s32_do(x, denom) * d;
}

int main(int argc, char*argv[]) {
  int32_t D =  strtol(argv[1], NULL, 0);
  struct libdivide_s32_t denom = libdivide_s32_gen(D);
  int32_t seed = INITSEED;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmod(seed * MULTIPLIER + CONSTANTADD, &denom, D);
  }
  return seed;
}
