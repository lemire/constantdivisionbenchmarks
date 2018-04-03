#include "common.h"

int main(int argc, char*argv[]) {
  uint32_t D =  strtol(argv[1], NULL, 0);
  uint32_t seed = INITSEED;
  for(size_t i = 0; i < REPEAT; i++) {
    seed = (seed * MULTIPLIER + CONSTANTADD) % D;
  }
  return seed;
}
