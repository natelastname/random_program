#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util, uint64_t util2){
  uint64_t a = 0;
  // begin
  a = __builtin_popcountll(a);
  a = a & x;
  a = a | x;
  a = a | x;
  a = a * x;
  a = a + y;
  a = a & y;
  a = __builtin_popcountll(a);
  // end
  if(util > 0){
     a = a >> (util-1);
     a = __builtin_popcountll(a);
  }
  return a;
}

