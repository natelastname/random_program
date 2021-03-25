#include "dynamic.h"

uint64_t cl_mul(uint64_t a, uint64_t b){
    uint64_t r = 0;
    while (b != 0){
        if ((a & 1) != 0){
            r ^= b;
	}
        a >>= 1;
        b <<= 1;
    }
    return r;
}


uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util, uint64_t util2){
  uint64_t a = 0;
  // begin
  a = a < x? a : x;
  a = a + 1;
  a = a & y;
  a = a & y;
  a = a - x;
  a = a + 1;
  a = a - 1;
  a = ~a;
  a = a & x;
  a = a - x;
  a = a | x;
  a = a * 2;
  a = a * y;
  a = a ^ y;
  // end
  if(util > 0){
     a = a >> (util-1);
     a = __builtin_popcountll(a);
  }

  return a;
}
