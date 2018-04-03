#!/bin/bash

LIBDIV_OPTS="libdivide libdivide_branchless"  #x64 where we have libdivide
CC_OPTS="-march=native -O3"  #default had include -mbmi2
case `hostname` in
       # knightslanding.licef.ca)
       # 	   CCSTRINGS=("gcc $CC_OPTS")  #gcc 5.4
       # 	   ;;
       strife)
	   CCSTRINGS=("gcc $CC_OPTS")  #gcc 5.4
           ;;
       zeal)
	   CCSTRINGS=("gcc $CC_OPTS"  "clang-4.0 $CC_OPTS")
	   ;;
       skylake)
	   CCSTRINGS=("gcc-6 $CC_OPTS"  "clang-4.0 $$_OPTS")
	   ;;
       Softiron)
	   #assume GCC?
	   CCSTRINGS=("gcc-6 -march=armv8-a  -O3" "/opt/clang+llvm-4.0.0-aarch64-linux-gnu/bin/clang-4.0 -march=armv8-a -O3")
	   LIBDIV_OPTS=    #none, for ARM
	   ;;
       *)
	   echo unknown hostname, please add in simplified_primes_benches.sh
	   exit
   esac

CCSTRING="${CCSTRINGS[0]}"

for opt in lkk_general gm_general lkk gm; do

echo '*********************** UNSIGNED ******************************'
    
	touch a.out
	rm a.out
	$CCSTRING   primes_benchmark_${opt}.c
	echo ================ $opt ===================
	for testrun in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do
	   ./perfstataout.sh | grep cycles   2>&1
	done

    echo '*********************** SIGNED ******************************'
	touch a.out
	rm a.out
	$CCSTRING   primes_benchmark_${opt}_signed.c
	echo ================ $opt signed ===================
	for testrun in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do
	./perfstataout.sh | grep cycles  2>&1
    done
done
