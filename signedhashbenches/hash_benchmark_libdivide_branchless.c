#include "common.h"
#include "libdivide.h"

static inline int32_t fastmod(int32_t x, const struct libdivide_s32_branchfree_t *denom, int32_t d) {
  return x - libdivide_s32_branchfree_do(x, denom) * d;
}

int main() {
  struct libdivide_s32_branchfree_t denom = libdivide_s32_branchfree_gen(D);
  int32_t seed = INITSEED;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = fastmod(seed * MULTIPLIER + CONSTANTADD, &denom, D);
  }
  return seed;
}
