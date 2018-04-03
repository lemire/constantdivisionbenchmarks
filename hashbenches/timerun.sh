#!/bin/bash

HOSTNAME=`hostname`
mkdir -p timeresults

LOGFILEGCC=timeresults/data-${HOSTNAME}-gcc.txt 
echo "************** Tests run `date` ********************" >>$LOGFILEGCC
./time_hash_benches_gcc.sh  >>$LOGFILEGCC 2>&1

LOGFILECLANG=timeresults/data-${HOSTNAME}-clang.txt 
echo "************** Tests run `date` ********************" >>$LOGFILECLANG
./time_hash_benches_clang.sh  >>$LOGFILECLANG 2>&1

