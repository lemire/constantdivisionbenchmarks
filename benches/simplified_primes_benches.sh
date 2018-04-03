#!/bin/bash
LIBDIV_OPTS="libdivide libdivide_branchless"  #x64 where we have libdivide
CC_OPTS="-march=native -O3"  #default had include -mbmi2
PERFCMD="perf stat -e cycles"   # alternatives are time and perf stat
REPS=1
case `hostname` in
       # knightslanding.licef.ca)
       # 	   CCSTRINGS=("gcc $CC_OPTS")  #gcc 5.4
       # 	   ;;
       strife)
	   CCSTRINGS=("gcc $CC_OPTS" "clang $CC_OPTS")  #gcc 5.4, clang 3.8
           ;;
       zeal)
	   CCSTRINGS=("gcc $CC_OPTS"  "clang-4.0 $CC_OPTS")
	   REPS=11   #ryzen timings seem noisier
	   ;;
       skylake)
	   CCSTRINGS=("gcc-6 $CC_OPTS"  "clang-4.0 $CC_OPTS")
	   ;;
       Softiron)
	   #assume GCC?
	   CCSTRINGS=("gcc-6 -march=armv8-a  -O3" "/opt/clang+llvm-4.0.0-aarch64-linux-gnu/bin/clang-4.0 -march=armv8-a -O3")
	   LIBDIV_OPTS=    #none, for ARM
	   ;;
       *)
	   echo unknown hostname, please add in simplified_primes_benches.sh
	   CCSTRINGS=("gcc $CC_OPTS" "clang $CC_OPTS")  
           ;;
   esac

for CCSTRING in "${CCSTRINGS[@]}" ; do

    echo Machine `hostname`,  compiling with $CCSTRING

    CC_SEE_ASM="$CCSTRING -S"  #if multiple compilers, keep the last one


    echo '*********************** UNSIGNED ******************************'
    #pulled out 16_gm 16_lkk
    for opt in gm lkk gm_general lkk_general   $LIBDIV_OPTS system ; do
	touch a.out
	rm a.out
	$CCSTRING   primes_benchmark_${opt}.c
	$CC_SEE_ASM primes_benchmark_${opt}.c
	echo ================ $opt ===================
	ctr=0
	while [[ ctr -lt REPS ]]; do
	    echo trial $ctr
 	    $PERFCMD ./a.out
	    ctr=$(( ctr+1 ))
	done
    done

    echo '*********************** SIGNED ******************************'
    for opt in gm lkk gm_general lkk_general $LIBDIV_OPTS system ; do
	touch a.out
	rm a.out
	$CCSTRING   primes_benchmark_${opt}_signed.c
	$CC_SEE_ASM primes_benchmark_${opt}_signed.c
	echo ================ $opt signed ===================
	ctr=0
	while [[ ctr -lt REPS ]]; do
 	    $PERFCMD ./a.out
	    ctr=$(( ctr+1 ))
	done
    done

done
