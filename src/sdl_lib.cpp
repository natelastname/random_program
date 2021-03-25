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

#include "sdl_lib.hpp"

namespace sdl_lib{
  
  /*
   *	Draws the red marker
   */
  void draw_crosshair(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    int a = RANGE*2;
    
    SDL_RenderDrawPoint(renderer,a,a);
    SDL_RenderDrawPoint(renderer,a+1,a);
    SDL_RenderDrawPoint(renderer,a-1,a);
    SDL_RenderDrawPoint(renderer,a,a+1);
    SDL_RenderDrawPoint(renderer,a,a-1);
    SDL_RenderDrawPoint(renderer,a+2,a);
    SDL_RenderDrawPoint(renderer,a-2,a);
    SDL_RenderDrawPoint(renderer,a,a+2);
    SDL_RenderDrawPoint(renderer,a,a-2);
  }

  // This is the function the initial screen uses 
  uint64_t reference_eval(uint64_t x, uint64_t y){
    uint64_t a = y;
    a = __builtin_popcountll(a ^ y);
    a = a * y;
    a = a * x;
    a = a * 2;
    a = __builtin_popcountll(~a);
    a = a + y;
    a = a & x;
    a = a - y;
    a = __builtin_popcountll(a);
    return a;		
  }

  // Don't remember why it uses this but it's harmless
  void test_evaluate(SDL_Renderer * renderer, long long offset_x,
		     long long offset_y, int shiftamt){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for(long long x = -RANGE; x < RANGE+1; x++){
      for(long long y = -RANGE; y < RANGE+1; y++){
	if((reference_eval(x+offset_x,y+offset_y) >> shiftamt) & 0x01){			
	  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}else{
	  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	long long a = (RANGE+x)*2;
	long long b = (RANGE+y)*2;
	SDL_RenderDrawPoint(renderer, a, b);
	SDL_RenderDrawPoint(renderer, a+1, b);
	SDL_RenderDrawPoint(renderer, a, b+1);
	SDL_RenderDrawPoint(renderer, a+1, b+1);
      }
    }
    draw_crosshair(renderer);
    SDL_RenderPresent(renderer);
  }


  // Notice how x and y are signed. (this is a deliberate choice)
  void dynamic_evaluate(SDL_Renderer * renderer, long long offset_x,
			long long offset_y, int shiftamt,
			dynamic_function * loader,
			long long util,
			long long util2){

    input_function fn = loader->reload();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    for(long long x = -RANGE; x < RANGE+1; x++){
      for(long long y = -RANGE; y < RANGE+1; y++){
	if((fn(x+offset_x,y+offset_y,util, util2) >> shiftamt) & 0x01){		
	  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}else{
	  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	long long a = (RANGE+x)*2;
	long long b = (RANGE+y)*2;
	SDL_RenderDrawPoint(renderer, a, b);
	SDL_RenderDrawPoint(renderer, a+1, b);
	SDL_RenderDrawPoint(renderer, a, b+1);
	SDL_RenderDrawPoint(renderer, a+1, b+1);

      }
    }
    draw_crosshair(renderer);
    return;

  }

  /**
   * saves current window to file as a bitmap 
   */
  void cap_frame(SDL_Renderer * renderer, SDL_Window* window, std::string name) {
    std::cout << "capping frame" << std::endl;
    const uint32_t format = SDL_PIXELFORMAT_ARGB8888;
    const int width = (2*RANGE+1);
    const int height = (2*RANGE+1);
	 
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
    std::string fname = "./screencaps/"+name+".bmp";
    std::cout << fname << std::endl;
    SDL_SaveBMP(surface, fname.c_str());
    SDL_FreeSurface(surface);
  } 

};
