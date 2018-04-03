#include "common.h"

uint32_t slowmod(uint32_t x, uint32_t d) {
  return x % d;
}

int main() {
  uint32_t seed = INITSEED;
  const volatile uint32_t volatile_d = D;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = slowmod(seed * MULTIPLIER + CONSTANTADD, volatile_d);
  }
  return seed;
}
