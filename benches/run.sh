#!/bin/bash

HOSTNAME=`hostname`
LOGFILE=results/data-${HOSTNAME}.txt 
mkdir -p results
echo "************** Tests run `date` ********************" >>$LOGFILE
./simplified_primes_benches.sh  >>$LOGFILE 2>&1

