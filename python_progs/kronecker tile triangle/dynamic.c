#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util){
  uint64_t a = 0;
  // begin
  a = a - y;
  a = a - x;
  a = a & x;
  a = a | y;
  a = y - a;
  a = a + 1;
  // end
  a = __builtin_popcountll(a);
  return a;
}
