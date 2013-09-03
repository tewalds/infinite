
#include "xorshift.h"
#include "time.h"
#include "bitcount.h"
#include <cstdio>
#include <stdlib.h>

XORShift_uint64 rand64;

#define bitcount(n) __builtin_popcountll(n)
//#define bitcount(n) trailing_ones_bitcount(n)
//#define bitcount(n) parallel_bitcount(n)
//#define bitcount(n) precomputed_bitcount(n)
//#define bitcount(n) precomputed_bitcount2(n)

int count_trailing_zeros(uint64_t v){
  // output: c will count v's trailing zero bits,
  // so if v is 1101000 (base 2), then c will be 3
  if(v) {
    v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
    return bitcount(v);
  } else {
    return 64;
  }
}

int trial(){
  uint64_t r = rand64();
  return count_trailing_zeros(r);
}

int main(int argc, char **argv){

  uint64_t trials = 1000000;
  if(argc >= 2)
    trials = atol(argv[1]);

  uint64_t buckets[64] = {0};

  Time start;
  rand64.seed(start.in_usec());

  printf("Running %lu trials ...\n", trials);

  for(uint64_t i = 0; i < trials; i++)
    buckets[trial()]++;

  uint64_t s = 0;
  for(uint64_t i = 0; i < 64; i++){
    s += buckets[i] * (1ull<<i);
    if(buckets[i])
      printf("%lu\t%lu\n", i, buckets[i]);
  }

  printf("Average value: %f\n", (double)s/trials);
  printf("Finished in %.3f seconds\n", (Time() - start));

  return 0;
}
