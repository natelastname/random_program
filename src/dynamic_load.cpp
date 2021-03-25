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

#include "dynamic_load.hpp"
uint64_t (*load_dynamic()) (uint64_t X, uint64_t Y){
   // Compile and open dynamic.c
   system("./build_dynamic.sh");
   void * lib = dlopen("./dynamic.so", RTLD_LAZY);
   if(lib == NULL){
      printf("Couldn't find dynamic.so\n");
      return 0;
   }
   uint64_t (*fn) (uint64_t X, uint64_t Y) = 
      (uint64_t (*) (uint64_t X, uint64_t Y)) dlsym(lib, "evaluate_dynamic");

   if(fn == NULL){
      printf("Could not get evaluate_dynamic from dynamic.so.\n");
      return 0;         
   }
}

dynamic_function::dynamic_function(){
  dl_lib = NULL;
   
   
}

input_function dynamic_function::reload(){
   if(dl_lib != NULL){
     dlclose(dl_lib);
   }
   
   // Compile and open dynamic.c
   system("./build_dynamic.sh");
   void * lib = dlopen("./dynamic.so", RTLD_LAZY);
   if(lib == NULL){
      printf("Couldn't find dynamic.so\n");
      return 0;
   } 
   dl_lib = lib;

   input_function fn = (input_function) dlsym(lib, "evaluate_dynamic");

   if(fn == NULL){
      printf("Could not get evaluate_dynamic from dynamic.so.\n");
      return 0;         
   }
   
   current_function = fn;
   return current_function;
}

input_function dynamic_function::get_function(){
   return current_function;   
}

















