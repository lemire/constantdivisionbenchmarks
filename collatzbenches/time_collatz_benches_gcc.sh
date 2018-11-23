#!/bin/bash
TIMEFORMAT=%R
LIBDIV_OPTS="libdivide libdivide_branchless"  #x64 where we have libdivide
PERFCMD="time" # could be perf stat
CCSTRINGS=("gcc -O3" )
SIGNED=$1
CONSTANT=$2



case `hostname` in
       knightslanding.licef.ca)
     ;;
       zeal)
     ;;
       strife)
     ;;
       MacBook-Air.local)
     ;;
       skylake)
           CCSTRINGS=("gcc-6 -march=native -O3")
           ;;
       Softiron)
	   #assume GCC?
	   CCSTRINGS=("gcc-6 -march=armv8-a  -O3" )
	   LIBDIV_OPTS=    #none, for ARM
	   echo "Sorry, the embedded assembly is x64 for now, aborting"
	   exit -1
           ;;
       *)
     echo unknown hostname, please add it
   esac

#check SIGNED and CONSTANT for allowed values
case $SIGNED in
    signed)
	;;
    unsigned)
      ;;
    *)
	echo "error, argument $SIGNED should be 'signed' or 'unsigned'"
	exit -1
esac

case $CONSTANT in
    constant)
	;;
    invariant)
      ;;
    *)
	echo "error, argument $CONSTANT should be 'constant' or 'invariant'"
	exit -1
esac




for CCSTRING in "${CCSTRINGS[@]}" ; do
    echo "#" Machine `hostname`,  compiling with $CCSTRING
    CC_SEE_ASM="$CCSTRING -S"  #if multiple compilers, keep the last one

    echo '#*********************** ' $SIGNED ' ******************************'
#    echo "# divisor  lkk lkk_ofk lkk_ofk2  $LIBDIV_OPTS system slow"
#multiple repetitions to account for removed "ofk" alternatives
#also allows a rough and ready repeatability check
    echo "# divisor  lkk lkk  lkk  $LIBDIV_OPTS system slow"

    END=64 #4096

    for ((i=2;i<=END;i++)); do
	s=$i
	outputs=()
#	for opt in lkk lkk_ofk lkk_ofk2 $LIBDIV_OPTS system slow ; do
	for opt in lkk lkk lkk $LIBDIV_OPTS system slow ; do
	    touch a.out
	    rm a.out
	    $CCSTRING -I../library/include  collatz_benchmark_${opt}_${SIGNED}_${CONSTANT}.c -DD=$i
	    $CC_SEE_ASM -I../library/include collatz_benchmark_${opt}_${SIGNED}_${CONSTANT}.c -DD=$i
	    thisresult=$( { time ./a.out $i; } 2>&1 )
	    outputs+=($?)
	    s+=" "$thisresult
	done
	refout=${outputs[0]}
	for oute in "${outputs[@]}"
	do
	    if [ "$refout" != "$oute" ]
	    then
		echo "bug? ${outputs[@]} divisor=${i} "
		exit -1
	    fi
	done
	echo $s
    done

    BIGEND=2000000000
    for ((i=END+1;i<=BIGEND;i=i/10*19)); do
	s=$i
	outputs=()
#	for opt in lkk lkk_ofk lkk_ofk2  $LIBDIV_OPTS system slow; do
	for opt in lkk lkk lkk  $LIBDIV_OPTS system slow; do
	    touch a.out
	    rm a.out
	    $CCSTRING -I../library/include  collatz_benchmark_${opt}_${SIGNED}_${CONSTANT}.c -DD=$i
	    $CC_SEE_ASM -I../library/include collatz_benchmark_${opt}_${SIGNED}_${CONSTANT}.c -DD=$i
	    thisresult=$( { time ./a.out $i; } 2>&1 )
	    outputs+=($?)
	    s+=" "$thisresult
	done

	refout=${outputs[0]}
	for oute in "${outputs[@]}"
	do
	    if [ "$refout" != "$oute" ]
	    then
		echo "bug? ${outputs[@]} divisor=${i}"
		exit -1
	    fi
	done
	echo $s
    done

    echo
    echo
done
