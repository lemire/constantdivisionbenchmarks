#!/bin/bash
TIMEFORMAT=%R
LIBDIV_OPTS="libdivide libdivide_branchless"  #x64 where we have libdivide
PERFCMD="time" # could be perf stat
CCSTRINGS=("gcc -march=native -mbmi2 -O3" )
case `hostname` in
       knightslanding.licef.ca)
     #Owen seems to prefer gcc 5.4  "gcc -march=native -mbmi2 -O3"
     ;;
       zeal)
           ;;
       strife)
     #CCSTRINGS=("gcc -march=native -mbmi2 -O3")  #gcc 5.4
           ;;
        MacBook-Air.local)
            ;;
       skylake)
     CCSTRINGS=("gcc-6 -march=native -mbmi2 -O3")
            ;;
       Softiron)
     #assume GCC?
     CCSTRINGS=("gcc-6 -march=armv8-a  -O3")
     LIBDIV_OPTS=    #none, for ARM
            ;;
       *)
     echo unknown hostname, please add it
   esac

for CCSTRING in "${CCSTRINGS[@]}" ; do
    echo "#" Machine `hostname`,  compiling with $CCSTRING
    CC_SEE_ASM="$CCSTRING -S"  #if multiple compilers, keep the last one
    echo '#*********************** UNSIGNED ******************************'
    echo "# divisor  lkk justdivlkk $LIBDIV_OPTS system "

    END=4096
    for opt in lkk justdivlkk $LIBDIV_OPTS system  ; do
       $CCSTRING  -o dynhash_benchmark_${opt}  dynhash_benchmark_${opt}.c
       $CC_SEE_ASM  dynhash_benchmark_${opt}.c
    done
    for ((i=2;i<=END;i++)); do
      s=$i
      outputs=()
      for opt in lkk justdivlkk $LIBDIV_OPTS system  ; do
         thisresult=$( { time ./dynhash_benchmark_${opt} $i; } 2>&1 )
          outputs+=($?)
          s+=" "$thisresult
      done
      refout=${outputs[0]}
      for oute in "${outputs[@]}"
      do
          if [ "$refout" != "$oute" ]
          then
            echo "bug? ${outputs[@]}"
            exit -1
          fi
      done
      echo $s
    done
    echo
    echo
done
