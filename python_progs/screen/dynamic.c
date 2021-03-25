#include "dynamic.h"

uint64_t evaluate_dynamic(uint64_t x, uint64_t y, uint64_t util){
  uint64_t a = 0;
  // begin
  a = a | x;
  a = a | y;
  a = a - 1;
  a = ~a;  // only leaves lowest bit set
           // this lowest bit will be in either x,y or both.
           // it is one if it is in both
  a = a & y;
  a = a & x;
  // end
  if(util == 0){
    a = __builtin_popcountll(a);
  }
  return a;
}
