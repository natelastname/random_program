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


#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#define RANGE 256

#include "sdl_lib.hpp"
#include "dynamic_load.hpp"

int main() {

  printf("\nBitwise Bitmap Demo\n");
  printf("Author: Nathan Nichols\n");
  printf("License: GPL v3-or-later\n\n");

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(4*RANGE, 4*RANGE, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  int shiftamt = 0;
  long long offset_x, offset_y;
  offset_x = 0;
  offset_y = 0;

  printf("Initializing default function\n");
  sdl_lib::test_evaluate(renderer,0,0,0);

  int running = 1;
  SDL_Event event;
  bool changed = false;
  bool popmode = false;
  long long util = 0;
  long long util2 = 0;

  int proglength = 5;
  
  dynamic_function loader = dynamic_function();
  
  while(running){
    changed = false;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
	running = 0;
      }

      if(event.type == SDL_KEYDOWN){

	changed = true;
	// change index of bit that determines color
	if(event.key.keysym.sym == SDLK_LEFTBRACKET){
	  if(shiftamt > 0){
	    shiftamt--;
	  }
	}
	// change index of bit that determines color
	if(event.key.keysym.sym == SDLK_RIGHTBRACKET){
	  shiftamt += 1;
	}
	// reset
	if(event.key.keysym.sym == SDLK_r){
	  offset_x = 0;
	  offset_y = 0;
	  shiftamt = 0;
	  util = 0;
	  util2 = 0;
	}
	// wasd movment
	if(event.key.keysym.sym == SDLK_w){
	  offset_y -= (RANGE / 8);
	}
	if(event.key.keysym.sym == SDLK_a){
	  offset_x -= (RANGE / 8);
	}
	if(event.key.keysym.sym == SDLK_s){
	  offset_y += (RANGE / 8);
	}
	if(event.key.keysym.sym == SDLK_d){
	  offset_x += (RANGE / 8);
	}
	// Change length of program
	if(event.key.keysym.sym == SDLK_DOWN){
	  if(proglength > 1){
	    proglength--;
	  }
	  std::cout << "Program length:" << proglength << std::endl;
				
	}
	// Change length of program
	if(event.key.keysym.sym == SDLK_UP){
	  proglength++;			
	  std::cout << "Program length:" << proglength << std::endl;
	}
	// change value of util
	if(event.key.keysym.sym == SDLK_9){
	  if(util > 0){
	    util--;
	  }
	  std::cout << "Util: "<< util << std::endl;
	}
	// change value of util 
	if(event.key.keysym.sym == SDLK_0){
	  util++;
	  std::cout << "Util: "<< util << std::endl;
	}
	// change value of util2
	if(event.key.keysym.sym == SDLK_7){
	  if(util2 > 0){
	    util2--;
	  }
	  std::cout << "Util2: "<< util2 << std::endl;
	}
	// change value of util2
	if(event.key.keysym.sym == SDLK_8){
	  util2++;
	  std::cout << "Util2: "<< util2 << std::endl;
	}
	// toggle pop mode
	if(event.key.keysym.sym == SDLK_q){
	  popmode = !popmode;
	  if(popmode){
	    std::cout << "Popcount mode enabled" << std::endl;
	  }else{
	    std::cout << "Popcount mode disabled" << std::endl;
	  }               
	}
	// Call the python script to write to dynamic.c
	if(event.key.keysym.sym == SDLK_KP_PLUS){
	  std::string command = "python3 ./src/rangen_hack.py ";
	  command = command + std::to_string(proglength);
	  //command = command + " | tee dynamic.c";
	  system(command.c_str());
	  system("mv ./dynamic.c ./src");
	}
	// Save dynamic.c and a screencap in a new folder in ./python_progs
	if(event.key.keysym.sym == SDLK_KP_MINUS){
	  sdl_lib::cap_frame(renderer, window, "cap");
	  system("./save_python.sh");
	}

	
      } // end key down event	
    }

    if(changed){
      printf("\rx:%lli, y:%lli, shift:%i\n",offset_x, offset_y, shiftamt);
      // TODO: this function recompiles every time it is called.
      // This is not neccessary and greatly reduces speed.
      sdl_lib::dynamic_evaluate(renderer, offset_x, offset_y, shiftamt,
				&loader, util, util2);
      SDL_RenderPresent(renderer);				
    }
  }
  SDL_Quit();
  return 0;
}

