#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util){
  uint64_t a = 0;
  // begin
  a = a ^ y;
  a = ~a;
  a = 0 - a;
  a = a * 2;
  a = a & y;
  a = ~a;
  a = a * 2;
  a = x - a;
  a = a + y;
  a = ~a;
  // end
  if(util == 0){
    a = __builtin_popcountll(a);
  }
  return a;
}
