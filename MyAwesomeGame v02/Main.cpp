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
	int rectSpeed = 1;
	SDL_Rect rectangle;
	rectangle.x = 180;
	rectangle.y = 160;
	rectangle.w = 260;
	rectangle.h = 160;

	// Initialize shot
	int shotSpeed = 1;
	bool movShot = false;
	SDL_Rect shot;
	shot.x = rectangle.x + 220;
	shot.y = rectangle.y + 75;
	shot.w = 40;
	shot.h = 10;

	// Movement control
	bool movRight = false;
	bool movLeft = false;
	bool movUp = false;
	bool movDown = false;
	
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

				case SDLK_RIGHT: movRight = true;
					break;
				case SDLK_LEFT: movLeft = true;
					break;
				case SDLK_UP: movUp = true;
					break;
				case SDLK_DOWN: movDown = true;
					break;
				case SDLK_w: 
					shot.x = rectangle.x + 260;
					shot.y = rectangle.y + 75;
					movShot = true;
				default:
					break;
				}
			}
			else if (event.type == SDL_KEYUP) {

				switch (event.key.keysym.sym) {

				case SDLK_RIGHT: movRight = false;
					break;
				case SDLK_LEFT: movLeft = false;
					break;
				case SDLK_UP: movUp = false;
					break;
				case SDLK_DOWN: movDown = false;
					break;
				default:
					break;
				}
			}
		}

		// Move ship
		if (movRight) rectangle.x += rectSpeed;
		if (movLeft) rectangle.x -= rectSpeed;
		if (movUp) rectangle.y -= rectSpeed;
		if (movDown) rectangle.y += rectSpeed;
		if (movShot) {

			shot.x += shotSpeed;
		}
		else{
			
			shot.x = rectangle.x + 150;
			shot.y = rectangle.y + 75;
		}
		
			// Don't let rectangle get out of the screen
		if (rectangle.y < 0) rectangle.y = 0;
		if (rectangle.y > HEIGHT - 160) rectangle.y = HEIGHT -160;
		if (rectangle.x < 0) rectangle.x = 0;
		if (rectangle.x > LENGTH - 260) rectangle.x = LENGTH - 260;
		
		SDL_SetRenderDrawColor(renderer, 34, 150, 255, 255);
		SDL_RenderClear(renderer); // All the screen (background) will be blue

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &shot);
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle);
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
