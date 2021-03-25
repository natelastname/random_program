#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util){
  uint64_t a = 0;
  // begin
  a = a - x;
  a = a + x;
  a = a & x;
  a = a | y;
  a = ~a;
  a = a - 1;
  a = a | y;
  a = 0 - a;
  a = a * 2;
  a = a * 3;
  a = a * 2;
  a = a & x;
  a = a * 2;
  a = a * 3;
  a = (y * 2) ^ y;
  a = a & x;
  a = x - a;
  a = a | y;
  a = y - a;
  a = a + 1;
  // end
  if(util == 0){
    a = __builtin_popcountll(a);
  }
  return a;
}
