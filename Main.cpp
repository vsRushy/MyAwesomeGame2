#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#pragma comment(lib, "../SDL_Image/libx86/SDL2_image.lib")
#define LENGTH 640
#define HEIGHT 480
#define SHIP_SPEED 1
#define SHOT_SPEED 1

typedef struct {

	int x, y;
	bool isAlive;
} Projectile;

typedef struct {

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* ship = NULL;
	SDL_Texture* backGround = NULL;
	SDL_Texture* shot = NULL;
	int backGroundWidth = 0;
	int shipX = 0, shipY = 0;
	bool movShot, movLeft, movRight, movDown, movUp;
	Projectile shots;
} Globals;

Globals g;

void Start() {

	SDL_Init(SDL_INIT_EVERYTHING);

	// Creation of window and renderer
	g.window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LENGTH, HEIGHT, 0);
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);

	// Load images
	IMG_Init(IMG_INIT_PNG);
	g.backGround = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/background.png"));
	g.ship = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/ship.png"));
	g.shot = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/shot.png"));
	SDL_QueryTexture(g.backGround, nullptr, nullptr, &g.backGroundWidth, nullptr);

	// Variable initialization
	g.shipX = 100;
	g.shipY = HEIGHT / 2;
	g.movShot = g.movDown = g.movUp = g.movLeft = g.movRight = false;
}

void Finish() {

	SDL_DestroyTexture(g.backGround);
	SDL_DestroyTexture(g.ship);
	SDL_DestroyTexture(g.shot);

	IMG_Quit();

	SDL_DestroyWindow(g.window);
	SDL_DestroyRenderer(g.renderer);
	
	SDL_Quit();
}

bool CheckInput() {

	bool ret = true;
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_KEYUP) {

			switch (event.key.keysym.sym) {

			case SDLK_LEFT:
				g.movLeft = false;
				break;
			case SDLK_RIGHT:
				g.movRight = false;
				break;
			case SDLK_DOWN:
				g.movDown = false;
				break;
			case SDLK_UP:
				g.movUp = false;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_KEYDOWN) {

			switch (event.key.keysym.sym) {

			case SDLK_LEFT:
				g.movLeft = true;
				break;
			case SDLK_RIGHT:
				g.movRight = true;
				break;
			case SDLK_DOWN:
				g.movDown = true;
				break;
			case SDLK_UP:
				g.movUp = true;
				break;
			case SDLK_x:
				ret = false;
				break;
			case SDLK_SPACE:
				g.shots.x = g.shipX + 32;
				g.shots.y = g.shipY;
				g.movShot = true;
				break;
			default:
				break;
			}
		}
		else if (event.type == SDL_QUIT) {

			ret = false;
		}
	}

	return ret;
}

void MoveStuff() {

	// Update ship position
	if (g.movLeft) g.shipX -= SHIP_SPEED;
	if (g.movRight) g.shipX += SHIP_SPEED;
	if (g.movDown) g.shipY += SHIP_SPEED;
	if (g.movUp) g.shipY -= SHIP_SPEED;

	if (g.movShot) {

		//g.movShot = false;
		g.shots.isAlive = true;
		

		if (g.shots.x < LENGTH) {
			
			g.shots.x += SHOT_SPEED;
		}
		else {

			g.shots.isAlive = false;
		}
	}
	else {

		g.shots.x = g.shipX + 32;
		g.shots.y = g.shipY;
	}
}

void Draw() {

	SDL_Rect target;

	// Background
	target = {

		0,
		0,
		g.backGroundWidth,
		HEIGHT
	};

	SDL_RenderCopy(g.renderer, g.backGround, nullptr, &target);

	// Laser
	if (g.shots.isAlive) {
		target = {

			g.shots.x,
			g.shots.y,
			64,
			64
		};

		SDL_RenderCopy(g.renderer, g.shot, nullptr, &target);
	}

	// Ship
	target = {

		g.shipX,
		g.shipY,
		64,
		64
	};

	SDL_RenderCopy(g.renderer, g.ship, nullptr, &target);

	SDL_RenderPresent(g.renderer);
}

int main(int argc, char* argv[]) {

	Start();

	while (CheckInput()) {

		MoveStuff();
		Draw();
	}

	Finish();

	return 0;
}