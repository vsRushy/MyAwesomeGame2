#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#pragma comment(lib, "../SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "../SDL_Mixer/libx86/SDL2_mixer.lib")
#define LENGTH 640
#define HEIGHT 480
#define SHIP_SPEED 1
#define SHOT_SPEED 1
#define SPACESHIP_X 64
#define SPACESHIP_Y 64
#define LASER_X 45
#define LASER_Y 50
#define TOTAL_SHOTS 1

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
	Mix_Music* music = NULL;
	Mix_Chunk* audio = NULL;
	int shipX = 0, shipY = 0;
	bool movShot, movLeft, movRight, movDown, movUp = false;
	int lastShot = 0;
	Projectile shots[TOTAL_SHOTS];
} Globals;

Globals g;

void Start() {

	SDL_Init(SDL_INIT_VIDEO);

	// Creation of window and renderer
	g.window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LENGTH, HEIGHT, 0);
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);

	// Load images
	IMG_Init(IMG_INIT_PNG);
	g.backGround = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/background.png"));
	g.ship = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/ship.png"));
	g.shot = SDL_CreateTextureFromSurface(g.renderer, IMG_Load("sprites/shot.png"));
	
	//Load music
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

	g.music = Mix_LoadMUS("audio/zizibum.ogg");
	g.audio = Mix_LoadWAV("audio/laser.wav");

	// Play music
	Mix_PlayMusic(g.music, -1);

	// Variable initialization
	g.shipX = 250;
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
	
	Mix_FreeMusic(g.music);
	Mix_FreeChunk(g.audio);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}

bool CheckInput() {

	// If an event is detected it will return true
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
				Mix_PlayChannel(-1, g.audio, 0);
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

	// Cannot exceed the screen limits
	if (g.shipX == 0) g.shipX += 1;
	if (g.shipX == LENGTH - SPACESHIP_X) g.shipX -= 1;
	if (g.shipY == 0) g.shipY += 1;
	if (g.shipY == HEIGHT - SPACESHIP_Y) g.shipY -= 1;

	if (g.movShot) {

		g.movShot = false;
		
		g.shots[g.lastShot].isAlive = true;
		g.shots[g.lastShot].x = g.shipX + SPACESHIP_X / 2;
		g.shots[g.lastShot].y = g.shipY;
		g.lastShot++;

		if (g.lastShot == TOTAL_SHOTS) g.lastShot = 0;
	}

	for (int i = 0; i < TOTAL_SHOTS; i++) {

		if (g.shots[i].isAlive) {

			if (g.shots[i].x < LENGTH) {

				g.shots[i].x += SHOT_SPEED;
			}
			else g.shots[i].isAlive = false;
		}
	}
}

void Draw() {

	// Textures are putted into this rect in order to show the texture
	SDL_Rect sprite;

	// Background
	sprite = {

		0,
		0,
		LENGTH,
		HEIGHT
	};

	SDL_RenderCopy(g.renderer, g.backGround, NULL, &sprite);

	// Laser
	for (int i = 0; i < TOTAL_SHOTS; i++) {

		if (g.shots[i].isAlive) {

			sprite = {

				g.shots[i].x,
				g.shots[i].y,
				64,
				64
			};

			SDL_RenderCopy(g.renderer, g.shot, NULL, &sprite);
		}
	}

	// Ship
	sprite = {

		g.shipX,
		g.shipY,
		SPACESHIP_X,
		SPACESHIP_Y
	};

	SDL_RenderCopy(g.renderer, g.ship, NULL, &sprite);

	SDL_RenderPresent(g.renderer); // Render present is needed in order to show new sprites / changes of the screen
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