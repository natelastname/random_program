#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util){
  uint64_t a = 0;
  // begin
  a = a ^ x;
  a = 0 - a;
  a = a & x;
  a = a & y;
  a = 0 - a;
  // end
  //a = __builtin_popcountll(a);
  return a;
}
