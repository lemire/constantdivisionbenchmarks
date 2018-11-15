#ifndef FASTMOD_H
#define FASTMOD_H

#include <stdint.h>
#include <stdbool.h>

// eventually delete these
//#define EXTRA_ALTERNATIVES 


/**
* Unsigned integers.
* Usage:
*  uint32_t d = ... ; // divisor, should be non-zero
*  uint64_t M = computeM_u32(d); // do once
*  fastmod_u32(a,M,d) is a % d for all 32-bit a.
*
**/

// M = ceil( (1<<64) / d ), d > 0
static inline uint64_t computeM_u32(uint32_t d) {
  return UINT64_C(0xFFFFFFFFFFFFFFFF) / d + 1;
}

// fastmod computes (a % d) given precomputed M
static inline uint32_t fastmod_u32(uint32_t a, uint64_t M, uint32_t d) {
  uint64_t lowbits = M * a;
  return ((__uint128_t)lowbits * d) >> 64;
}

// fastmod computes (a / d) given precomputed M for d>1
static inline uint32_t fastdiv_u32(uint32_t a, uint64_t M) {
  return ( (__uint128_t) M * a ) >> 64;
}
/**
* signed integers
* Usage:
*  int32_t d = ... ; // should be non-zero and between [-2147483647,2147483647]
*  int32_t positive_d = d < 0 ? -d : d; // absolute value
*  uint64_t M = computeM_s32(d); // do once
*  fastmod_s32(a,M,positive_d) is a % d for all 32-bit a.
**/

// M = floor( (1<<64) / d ) + 1
// you must have that d is different from 0 and -2147483648
// if d = -1 and a = -2147483648, the result is undefined
static inline uint64_t computeM_s32(int32_t d) {
  if (d < 0)
    d = -d;
  return UINT64_C(0xFFFFFFFFFFFFFFFF) / d + 1 + ((d & (d - 1)) == 0 ? 1 : 0);
}

// fastmod computes (a % d) given precomputed M,
// you should pass the absolute value of d
static inline int32_t fastmod_s32(int32_t a, uint64_t M, uint32_t positive_d) {
  uint64_t lowbits = M * a;
  int32_t highbits = ((__uint128_t)lowbits * positive_d) >> 64;
  return highbits - ((positive_d - 1) & (a >> 31));
}

// fastmod computes (a / d) given precomputed M, assumes that d must not
// be one of -1, 1, or -2147483648
static inline int32_t fastdiv_s32(int32_t a, uint64_t M, int32_t d) {
  uint64_t highbits = ((__uint128_t) M * a) >> 64;
  highbits += (a < 0 ? 1 : 0);
  if(d < 0) return -highbits;
  return highbits;
}

#ifdef EXTRA_ALTERNATIVES

//ofk, no idea if any better than   "return (v<0) ? -v : v"
static inline int32_t fast_abs(int32_t v) {
  int32_t zero_or_minus1 = v >> 31;
  return  (v ^ zero_or_minus1)-zero_or_minus1;
}

static inline bool is_positive_power_of_two(int32_t d) {
  return (d & (d-1)) == 0;
}

// some obvious de-ofk-ing needed once this is stable.


//ofk
#define IMUL64HIGH(rh, i1, i2)                                                 \
  do { int64_t unused_output;                                                  \
    asm("imulq %3" : "=d"(rh),"=a"(unused_output) : "a"(i1), "r"(i2) : "cc");} \
  while(0)

//ofk
#define MUL64HIGH(rh, i1, i2)                                                 \
  do { int64_t unused_output;                                                  \
    asm("mulq %3" : "=d"(rh),"=a"(unused_output) : "a"(i1), "r"(i2) : "cc");} \
  while(0)




//ofk
// use with computeM_s32
// this option is broken for 1,-1, 2, -2, and -2**31
static inline int32_t fastdiv_s32_ofk_special(int32_t a, uint64_t M, int32_t d) {
  
  int64_t quotient3;
  const int64_t corrector = d >> 31;
  const int64_t numer_corrector = a >> 31;

  IMUL64HIGH(quotient3, (int64_t) a, M);
  int32_t quotient2 = quotient3 - numer_corrector;
  
  // negate if necessary
  int32_t quotient = (quotient2 ^ corrector) - corrector;
  return quotient;  
}


// broken for +-1 also minor breakage d= -2**31 since d/d gives 0
static inline int32_t fastdiv_s32_ofk2(int32_t a, uint64_t M, int32_t d) {
  
  int64_t quotient3;
  const int64_t corrector = d >> 31;
  const int64_t numer_corrector = a >> 31;
  
  // based on the instructions used with unsigned 128bit multiplication
  MUL64HIGH(quotient3, (int64_t) a, M);
  quotient3 -= (M & numer_corrector);  // except should be cheaper and equivalent
  
  int32_t quotient2 = quotient3 - numer_corrector;
  
  // negate if necessary
  int32_t quotient = (quotient2 ^ corrector) - corrector;
  return quotient;  
}






static inline uint64_t computeM_s32_ofk(int32_t d) {
  const uint32_t abs_d = fast_abs(d);
  if (is_positive_power_of_two(abs_d)) {
    return __builtin_ctz(d);
  }
  else {
    const uint64_t M = 1 + (UINT64_C(0xffffffffffffffff) / abs_d); 
    return M;
  }
}

//ofk
// should work for all nonzero d
static inline int32_t fastdiv_s32_ofk(int32_t a, uint64_t M, int32_t d) {
  const int64_t corrector = d >> 31;
  int32_t quotient;

  if (is_positive_power_of_two(fast_abs(d))) {
      // code from libdivide
      // uses 3 shifts, 2 add/sub and and AND.  But much faster than the usual
      // sequence from Warren (same number of instructions).
      // M was co-opted to be a shift amount for d a power of 2
      const uint32_t uq = (uint32_t)(a + ((a >> 31) & ((1U << M) -1)));
      quotient = (int32_t) uq;
      quotient = quotient >> M;  
  }
  else {
    int64_t quotient3;
    const int64_t numer_corrector = a >> 31;
    
    IMUL64HIGH(quotient3, (int64_t) a, M);
    quotient = quotient3 - numer_corrector;
  }
  // negate if necessary
  quotient = (quotient ^ corrector) - corrector;
  return quotient;
}

#endif

#endif
