// using the GM divisibilty, spot checking a few cases

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

// signed version has 2 thresholds and an addition
// could reduce to unsigned, but would require instr for abs,
// which is probably more expensive
bool divisible( const int32_t v, const struct intpair ip, const int32_t thresh1, const int32_t thresh2) {
  int32_t q0 = v*ip.dbar;
  // rotation trick does not work for -ve values

  //printf("q0 is %d\n",q0 );
  
  return  ((uint32_t)(q0-thresh1) <= (uint32_t)thresh2) && !(((1<<ip.e)-1) & q0);
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
  int32_t  divisors[] = {-1820, -455, 1820, +1, 455, 0x80000000, 0x80000001, -1};

  
  for (int i=0; i < 8; ++i) {
    int32_t div = divisors[i];
    printf("checking %d\n", div);

    int64_t longdiv = div;
    int64_t abs_d1 = (longdiv ^ (longdiv>>63)) - (longdiv>>63); 
    uint32_t abs_d = (div ^ (div>>31)) - (div>>31); 

      struct intpair M = gm_multiplicative_inverse(div);
      int prime_thresh_low  = -((0x80000000U / abs_d)<<M.e);
      printf("ptl=%d\n",prime_thresh_low);
      int prime_thresh2  = -prime_thresh_low + ((0x7fffffff / abs_d) << M.e);
      printf("thresholds are %d %d\n", prime_thresh_low, prime_thresh2);


    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      int dividend = (int) j;
      bool div1 = divisible(dividend, M, prime_thresh_low, prime_thresh2);
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

      int64_t longdiv = div;
      int64_t abs_d = (longdiv ^ (longdiv>>63)) - (longdiv>>63); 

      struct intpair M = gm_multiplicative_inverse(div);
      int prime_thresh_low  = -((0x80000000L / abs_d)<<M.e);
      //printf("ptl=%d\n",prime_thresh_low);
      int prime_thresh2  = -prime_thresh_low + ((0x7fffffff / abs_d) << M.e);
      //printf("thresholds are %d %d\n", prime_thresh_low, prime_thresh2);


      
      bool div1 = divisible(dividend, M, prime_thresh_low, prime_thresh2);
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
