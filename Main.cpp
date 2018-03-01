#include <iostream>
#include "SDL/include/SDL.h"
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#define LENGTH 640
#define HEIGHT 480

int main(int argc, char* argv[]) {

	// Game is running
	bool running = true;

	// Initialize and declare variables
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;

	// Initialize rect
	SDL_Rect rectangle;
	rectangle.x = 180;
	rectangle.y = 160;
	rectangle.w = 260;
	rectangle.h = 160;
	
	// Initialize video subsystem
	SDL_Init(SDL_INIT_VIDEO); 

	// Create window
	window = SDL_CreateWindow(
		"Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		LENGTH,
		HEIGHT,
		SDL_WINDOW_OPENGL);

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, 0); // Parameters: window, index, flags

	while (running) {
		while (SDL_PollEvent(&event) != 0) { 

			if (event.type == SDL_QUIT) running = false; // To close the window whenever the user wants
			else if (event.type == SDL_KEYDOWN) {

				switch (event.key.keysym.sym) {

				case SDLK_UP: rectangle.y -= 10;
					break;
				case SDLK_DOWN: rectangle.y += 10;
					break;
				case SDLK_RIGHT: rectangle.x += 10;
					break;
				case SDLK_LEFT: rectangle.x -= 10;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 34, 150, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}