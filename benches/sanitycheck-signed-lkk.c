// using the Lemire divisibility check.  General version for all
// divisors and dividends

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* version matching paper. Reduction to the unsigned case */


uint64_t lkk_mvalue(const int32_t d) {
  uint32_t abs_d = (d ^ (d>>31)) - (d>>31);
  return 1 + (UINT64_C(0xffffffffffffffff) / abs_d);
}

// d==1 gives M=0 and wrong results. Have to check for it.
// if we expect this silly situation to be very rare, might
// go for the branchy version (|| in return stmt)
bool lkk_divisible(const int32_t v, const uint64_t mval) {
  const uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  //  return !mval || (abs_v*mval < mval);  // Owen's painful approach
  return abs_v*mval <= mval-1;  // Daniel's hack, rely on 0 mval wrapping
}

int  main() {
  int32_t  divisors[] = {-1, +1, 455,-455, 0xfedcba98, 0x76543210, 0x80000000, 0x80000001};

  for (int i=0; i < 8; ++i) {
    int32_t div = divisors[i];
    printf("checking divisor %d\n", div);
      uint64_t M = lkk_mvalue(div);

      // all dividends for a small collection of divisors

    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      int dividend = (int) j;
      
      bool div1 = lkk_divisible(dividend, M);
      bool div2;
      if (div == -1 && dividend == 0x80000000) 
        div2 = true; 
      else
        div2 = (dividend % div ==0);
      if (div1 != div2)
        printf("whoops for dividend %d and divisor %d\n", dividend, div);
      }
  }
  
  // all divisors for a small collection of dividends
  
  for (int i=0; i < 8; ++i) {
    int32_t dividend = divisors[i];
    printf("checking dividend %d\n", dividend);
    
    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      if (j==0) continue;
      int32_t div = (int32_t) j;
      uint64_t M = lkk_mvalue(div);
      
      bool div1 = lkk_divisible(dividend, M);
      bool div2;
      if (div == -1 && dividend == 0x80000000) 
        div2 = true; 
      else
        div2 = (dividend % div ==0);
      if (div1 != div2)
        printf("whoops for dividend %d and divisor %d\n", dividend, div);
    }
  }
}
