/*
Copyright (C) 2018 Nathan Nichols

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL NATHAN
NICHOLS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef DYNAMIC_LOAD_HPP
#define DYNAMIC_LOAD_HPP

#include <iostream>
#include <stdlib.h>// execute compile command with system()
#include <dlfcn.h> // loading .so file
#include <inttypes.h>

typedef uint64_t (*input_function) (uint64_t X, uint64_t Y,
				      uint64_t util, uint64_t util2);

class dynamic_function {
   private:
      input_function current_function;
      void * dl_lib;
   public:
      dynamic_function();
      input_function reload();
      input_function get_function();
};

#endif // DYNAMIC_LOAD_HPP


