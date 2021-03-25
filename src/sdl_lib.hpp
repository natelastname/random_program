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

#ifndef SDL_LIB_HPP
#define SDL_LIB_HPP

#include <string>
#include <inttypes.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>// execute compile command with system()

#include "dynamic_load.hpp"

#define RANGE 256

namespace sdl_lib{
	void draw_crosshair(SDL_Renderer * renderer);
	void dynamic_evaluate(SDL_Renderer * renderer, long long offset_x,
						long long offset_y,
				int shiftamt,
				dynamic_function * loader,
				long long util,
				long long util2);
	void test_evaluate(SDL_Renderer * renderer, long long offset_x,
						long long offset_y, int shiftamt);
	void cap_frame(SDL_Renderer * renderer, SDL_Window* window, 
					std::string name);

};

#endif // SDL_LIB_HPP
