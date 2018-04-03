# constantdivisionbenchmarks
Benchmarks for constant-division problems (not a library! for research only!)

# Prerequistes

- A bash shell and a Linux-like system.
- It helps to have the GCC and clang compilers installed. The scripts that ends with gcc.sh require GCC whereas the scripts that ends with clang.sh require clang.
- Some specific tests require a Linux machine with a working ``perf`` command, but most tests run fine on other operating systems.

# Usage (requires just a working compiler)

```
cd dynhashbenches

./time_dynhash_benches_gcc.sh
./time_dynhash_benches_clang.sh

cd ..
```


```
cd hashbenches

./time_hash_benches_clang.sh
./time_hash_benches_gcc.sh

cd ..
```


```
cd signeddynhashbenches

./time_hash_benches_clang.sh
./time_hash_benches_gcc.sh

cd ..
```

```
cd signedhashbenches

./time_hash_benches_clang.sh
./time_hash_benches_gcc.sh

cd ..
```

```
cd collatzbenches

./time_collatz_benches_clang.sh  signed constant
./time_collatz_benches_clang.sh  signed invariant
./time_collatz_benches_clang.sh  unsigned constant
./time_collatz_benches_clang.sh  unsigned invariant

./time_collatz_benches_gcc.sh  signed constant
./time_collatz_benches_gcc.sh  signed invariant
./time_collatz_benches_gcc.sh  unsigned constant
./time_collatz_benches_gcc.sh  unsigned invariant

cd ..
```

# Usage (requires perf/Linux)

```
cd benches
./simplified_primes_benches.sh
cd ..
```
