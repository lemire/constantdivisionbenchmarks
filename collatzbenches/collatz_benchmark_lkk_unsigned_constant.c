#include <stdio.h>
#include "common.h"
#include "fastmod.h"

/* How many starting values between 2 and V_LIMIT satisfy our generalized 
 *  Collatz conjecture within STEPS_LIMIT steps?
 */
int main() {
  uint64_t M = computeM_u32(D);
  int count=0;
  
  for(int i = 0; i < REPEAT; i++) {
    for (uint32_t start_value = 2; start_value < V_LIMIT; ++start_value) {
      uint32_t v = start_value;
      for (int i=0; i < STEPS_LIMIT; ++i) {
	if (v == 1) {
	  ++count;
	  break;
	}
	if ( (v % 2) && (v < 0xfffffffe / (D+1))) // if (v % 2)
	  v = (D+1)*v +1;
	else
	  v = fastdiv_u32(v,M);
      }
    }
  }
  //  printf("count is %d\n",count/REPEAT);
  return count/REPEAT;

}
