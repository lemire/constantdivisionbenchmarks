#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* How many starting values between 2 and V_LIMIT satisfy our generalized 
 *  Collatz conjecture within STEPS_LIMIT steps?
 */

// compiler constant of D must be given

int main(int argc, char**argv) {
  if (argc < 2) {
    fprintf(stderr," **** need to give D on the command line. Abort.\n");
    return 1;
  }
  uint32_t d = atol(argv[1]);
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
	  v = v / D;
      }
    }
  }
  //  printf("count is %d\n",count/REPEAT);
  return count/REPEAT;

}
