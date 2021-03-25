#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util, uint64_t util2){
  uint64_t a = 0;
  // begin
  a = a | x;
  a = (a ^ y) & y;
  a = __builtin_popcountll(a);
  a = a * x;
  a = a | x;
  a = (y * 2) ^ y;
  a = a & x;
  a = a * y;
  // end
  if(util > 0){
     a = a >> (util-1);
     a = __builtin_popcountll(a);
  }
  return a;
}
