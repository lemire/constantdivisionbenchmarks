#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "libdivide.h"

/* How many starting values between 2 and V_LIMIT satisfy our generalized 
 *  Collatz conjecture within STEPS_LIMIT steps?
 */

// compiler constant of D must be given

int main(int argc, char**argv) {
  if (argc < 2) {
    fprintf(stderr," **** need to give D on the command line. Abort.\n");
    return 1;
  }
  int32_t d = atol(argv[1]);
  struct libdivide_s32_t M =  libdivide_s32_gen(d);

  int count=0;
  
  for(int i = 0; i < REPEAT; i++) {
    for (int32_t start_value = 2; start_value < V_LIMIT; ++start_value) {
      int32_t v = start_value;
      for (int i=0; i < STEPS_LIMIT; ++i) {
	if (v == 1) {
	  ++count;
	  break;
	}
	if ((v % 2) && (v < 0x7ffffffe / (D+1))) //	if (v % 2)
	  v = (D+1)*v +1;
	else
	  v = libdivide_s32_do(v, &M);
      }
    }
  }
  //  printf("count is %d\n",count/REPEAT);
  return count/REPEAT;

}
