#include <stdio.h>
#include "common.h"
#include "fastmod.h"

/* How many starting values between 2 and V_LIMIT satisfy our generalized 
 *  Collatz conjecture within STEPS_LIMIT steps?
 */
int main() {
  uint64_t M = computeM_s32(D); // consider ofk vers
  int count=0;
  
  for(int i = 0; i < REPEAT; i++) {
    for (int32_t start_value = 2; start_value < V_LIMIT; ++start_value) {
      int32_t v = start_value;
      for (int i=0; i < STEPS_LIMIT; ++i) {
	if (v == 1) {
	  ++count;
	  break;
	}
	if ((v % 2) && (v < 0x7ffffffe / (D+1)))
	  v = (D+1)*v +1;
	else
	  v = fastdiv_s32(v,M,D); // consider ofk version
      }
    }
  }
  //  printf("count is %d\n",count/REPEAT);
  return count/REPEAT;

}
