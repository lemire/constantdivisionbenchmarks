#!/bin/bash
TIMEFORMAT=%R
LIBDIV_OPTS="libdivide libdivide_branchless"  #x64 where we have libdivide
PERFCMD="time" # could be perf stat
CCSTRINGS=("gcc -march=native -O3" )
case `hostname` in
       knightslanding.licef.ca)
     #Owen seems to prefer gcc 5.4  "gcc -march=native -mbmi2 -O3"
     ;;
       zeal)
           ;;
       strife)
         # CCSTRINGS=("gcc -march=native -mbmi2 -O3")  #gcc 5.4
           ;;
        MacBook-Air.local)
            ;;
       skylake)
           CCSTRINGS=("gcc-6 -march=native -O3") # Owen seems to prefer gcc? "gcc-6 -march=native -mbmi2 -O3"
            ;;
       Softiron)
     #assume GCC?
     CCSTRINGS=("gcc-6 -march=armv8-a  -O3" )
     LIBDIV_OPTS=    #none, for ARM
            ;;
       *)
     echo unknown hostname, please add it
   esac

for CCSTRING in "${CCSTRINGS[@]}" ; do
    echo "#" Machine `hostname`,  compiling with $CCSTRING
    CC_SEE_ASM="$CCSTRING -S"  #if multiple compilers, keep the last one
    echo '#*********************** UNSIGNED ******************************'
    echo "# divisor  lkk justdivlkk $LIBDIV_OPTS system slow"

    END=64 #4096

    for ((i=2;i<=END;i++)); do
      s=$i
      outputs=()
      for opt in lkk justdivlkk $LIBDIV_OPTS system slow ; do
          touch a.out
          rm a.out
          $CCSTRING   hash_benchmark_${opt}.c -DD=$i
          $CC_SEE_ASM hash_benchmark_${opt}.c -DD=$i
          thisresult=$( { time ./a.out; } 2>&1 )
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

    BIGEND=2000000000
    for ((i=END+1;i<=BIGEND;i=i/10*19)); do
      s=$i
      outputs=()
      for opt in lkk justdivlkk $LIBDIV_OPTS system slow ; do
          touch a.out
          rm a.out
          $CCSTRING   hash_benchmark_${opt}.c -DD=$i
          $CC_SEE_ASM hash_benchmark_${opt}.c -DD=$i
          thisresult=$( { time ./a.out; } 2>&1 )
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
