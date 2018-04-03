// using the GM divisibilty, spot checking a few cases
// This is the possibly faster version that takes absolute values


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// bitwise rotation, hopefully recognized by compiler
// 1 <= n <= 31.
// See Regehr blog on how n=0 is officially undefined behaviour
// https://blog.regehr.org/archives/1063
// but, if the compiler generates the right instruction, we can
// get away without without artificially hurting the GM implementation.
uint32_t rotr32 (uint32_t x, uint32_t n)
{
  return (x>>n) | (x<<(32-n));
}

struct intpair {uint32_t e; int32_t dbar;};

bool divisible( const int32_t v, const struct intpair ip, const uint32_t thresh) {
  uint32_t abs_v = (v ^ (v>>31)) - (v>>31);
  uint32_t q0 = abs_v*ip.dbar;
  return rotr32(q0, ip.e) <= thresh;
}



// Newton's method per Warren p 246 & 247
struct intpair gm_multiplicative_inverse(int32_t d) {
  struct intpair retval;
  int32_t abs_d = (d ^ (d>>31)) - (d>>31); // -2**31 might be issue
  retval.e = __builtin_ctz(abs_d);
  int32_t d_odd = abs_d >> retval.e;
  //printf("abs_d is %d and e is %d and d_odd is %d\n",abs_d, retval.e, d_odd);
  int32_t x0 = d_odd + 2*((d_odd+1) & 4);
  int32_t x1 = x0 * (2 - d_odd *x0);
  int32_t x2 = x1 * (2 - d_odd *x1);
  retval.dbar = x2 * (2 - d_odd *x2);
  return retval;
}

int  main() {
  int32_t  divisors[] = {0x80000000, +1, -1820, -455, 1820, 455,  0x80000001, -1};

  
  for (int i=0; i < 8; ++i) {
    int32_t div = divisors[i];
    printf("checking %d\n", div);

    uint32_t abs_d = (div ^ (div>>31)) - (div>>31); 

      struct intpair M = gm_multiplicative_inverse(div);
      int32_t prime_thresh = 0xffffffffU / abs_d;

    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      int32_t dividend = (int32_t) j;
      bool div1 = divisible(dividend, M, prime_thresh);
      bool div2;
      if (div == -1 && dividend == 0x80000000) 
        div2 = true; 
      else
        div2 = (dividend % div ==0);
      //if (div2) printf("should divide\n");

      if (div1 != div2) {
        printf("whoops for dividend %d and divisor %d\n", dividend, div);
        return 0;}
      }
  }
   
 // all divisors for a small collection of dividends
  
  for (int i=0; i < 8; ++i) {
    int32_t dividend = divisors[i];
    printf("checking dividend %d\n", dividend);
    
    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      if (j==0) continue;
      int32_t div = (int32_t) j;

    int32_t abs_d = (div ^ (div>>31)) - (div>>31); 

      struct intpair M = gm_multiplicative_inverse(div);
      int32_t prime_thresh = 0xffffffffU / abs_d;
      
      bool div1 = divisible(dividend, M, prime_thresh);
      bool div2;
      if (div == -1 && dividend == 0x80000000) 
        div2 = true; 
      else
        div2 = (dividend % div ==0);
      if (div1 != div2) {
        printf("whoops for dividend %d and divisor %d\n", dividend, div);
        return 0;}
    }
  }
  
}
