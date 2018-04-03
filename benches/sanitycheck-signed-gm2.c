// using the GM divisibilty, spot checking a few cases
// specialized signed, not taking absolute value of v

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



bool gm_divisible( const int32_t v, const  int32_t dbar, const int32_t thresh1, const int32_t thresh2) {
  return (uint32_t) (v*dbar-thresh1) <= (uint32_t) thresh2;
}


// Newton's method per Warren p 246 & 247
int32_t gm_multiplicative_inverse(int32_t d) {
  int32_t retval;
  int32_t abs_d_odd = (d ^ (d>>31)) - (d>>31); // -2**31 might be issue
  int32_t x0 = abs_d_odd + 2*((abs_d_odd+1) & 4);
  int32_t x1 = x0 * (2 - abs_d_odd *x0);
  int32_t x2 = x1 * (2 - abs_d_odd *x1);
  retval = x2 * (2 -abs_d_odd *x2);
  return retval;
}




int  main() {
  int32_t  divisors[] = {-1821, -455, 1821, +1, 455, 0x80000003, 0x80000001, -1};

  
  for (int i=0; i < 8; ++i) {
    int32_t div = divisors[i];
    printf("checking %d\n", div);

    int64_t longdiv = div;
    int64_t abs_d1 = (longdiv ^ (longdiv>>63)) - (longdiv>>63); 
    uint32_t abs_d = (div ^ (div>>31)) - (div>>31); 

      int32_t M = gm_multiplicative_inverse(div);
      int prime_thresh_low  = -((0x80000000U / abs_d));
      printf("ptl=%d\n",prime_thresh_low);
      int prime_thresh2  = -prime_thresh_low + ((0x7fffffff / abs_d));

      printf("thresholds are %d %d\n", prime_thresh_low, prime_thresh2);


    for (long j= -(1L<<31); j < (1L<<31) ; ++j) {
      int dividend = (int) j;
      bool div1 = gm_divisible(dividend, M, prime_thresh_low, prime_thresh2);
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
 // all odd divisors for a small collection of dividends
  
  for (int i=0; i < 8; ++i) {
    int32_t dividend = divisors[i];
    printf("checking dividend %d\n", dividend);
    
    for (long j= -(1L<<31)+1; j < (1L<<31) ; j+=2 ) {
      if (j==0) continue;
      int32_t div = (int32_t) j;

      int64_t longdiv = div;
      int64_t abs_d = (longdiv ^ (longdiv>>63)) - (longdiv>>63); 

      int32_t  M = gm_multiplicative_inverse(div);
      int prime_thresh_low  = -((0x80000000L / abs_d));
      //printf("ptl=%d\n",prime_thresh_low);
      int prime_thresh2  = -prime_thresh_low + ((0x7fffffff / abs_d));
      //prime_thresh_low = 0x80000000U / (uint32_t) div;
      //prime_thresh2 = prime_thresh_low + 0x7fffffff / div;
      //printf("thresholds are %d %d\n", prime_thresh_low, prime_thresh2);


      
      bool div1 = gm_divisible(dividend, M, prime_thresh_low, prime_thresh2);
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
