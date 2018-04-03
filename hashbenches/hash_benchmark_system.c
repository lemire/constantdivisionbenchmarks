#include "common.h"

int main() {
  uint32_t seed = INITSEED;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = (seed * MULTIPLIER + CONSTANTADD) % D;
  }
  return seed;
}
