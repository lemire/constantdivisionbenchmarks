#include "common.h"

int32_t slowmod(int32_t x, int32_t d) {
  return x % d;
}

int main() {
  int32_t seed = INITSEED;
  const volatile int32_t volatile_d = D;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = slowmod(seed * MULTIPLIER + CONSTANTADD, volatile_d);
  }
  return seed;
}
