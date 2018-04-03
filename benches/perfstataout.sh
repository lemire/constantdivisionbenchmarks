#!/bin/bash
perf stat -e cycles ./a.out 2>&1
