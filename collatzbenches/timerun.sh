#!/bin/bash

HOSTNAME=`hostname`
mkdir -p timeresults

for SIGNED in unsigned signed; do
    for CONSTANT in constant invariant; do
	echo $SIGNED $CONSTANT
	LOGFILEGCC=timeresults/data-${HOSTNAME}-${SIGNED}-${CONSTANT}-gcc.txt 
	echo "#************** Tests run `date` ********************" >>$LOGFILEGCC
	./time_collatz_benches_gcc.sh $SIGNED $CONSTANT >>$LOGFILEGCC 2>&1
	
	LOGFILECLANG=timeresults/data-${HOSTNAME}-${SIGNED}-${CONSTANT}-clang.txt 
	echo "#************** Tests run `date` ********************" >>$LOGFILECLANG
	./time_collatz_benches_clang.sh $SIGNED $CONSTANT  >>$LOGFILECLANG 2>&1
	
    done
done

