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


  // begin
  uint64_t a = 0;
  a = (x&y) + (~x) + util2;
  a ^= (x&y) + (~x);
  //a = ~(x^y)+util2;
  if(util > 0){
    a = a >> (util-1);
    a = __builtin_popcountll(a);
  }
  return a;

  /*
  uint64_t a = 0;
  a = (x&y) + (~x) + util2;
  a ^= (x&y) + (~x);
  //a = ~(x^y)+util2;
  if(util > 0){
    a = a >> (util-1);
    a = __builtin_popcountll(a);
  }
  return a;
  
  */

  
  /*
  if(util2 == 0){
    uint64_t a = 0;
    a = x&y;
    a = a + (~x) + util2;
    // end
    if(util > 0){
      a = a >> (util-1);
      a = __builtin_popcountll(a);
    }
    return a;
  }else{
    int a = 0; 
    int A = x;
    int B = y;
    a = A&B;
    a = a - A;
    // end
    if(util > 0){
      a = a >> (util-1);
      a = __builtin_popcountll(a);
    }
    return a;
  }
  */
  
}
