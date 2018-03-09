#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#pragma comment(lib, "../SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "../SDL_Mixer/libx86/SDL2_mixer.lib")
#define LENGTH 1920
#define HEIGHT 1080
<<<<<<< HEAD
#define SHIP_SPEED 10
#define SHOT_SPEED 15
=======
#define SHIP_SPEED 1
#define SHOT_SPEED 1
>>>>>>> 92ed8a6931e964e2bd7dc8e4338e1580179d9b9a
#define SPACESHIP_X 64
#define SPACESHIP_Y 64
#define LASER_X 64
#define LASER_Y 64

typedef struct {

	int x, y;
	bool isAlive;
} Projectile;

typedef struct {

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* ship = nullptr;
	SDL_Texture* backGround = nullptr;
	SDL_Texture* shot = nullptr;
	Mix_Music* music = nullptr;
	Mix_Chunk* audio = nullptr;
	int shipX = 0, shipY = 0;
	bool movLeft, movRight, movDown, movUp = false;
	Projectile shots;
} Globals;

Globals g;

void Start() {

	SDL_Init(SDL_INIT_VIDEO);

	// Creation of window and renderer
	g.window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LENGTH, HEIGHT, 0);
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);

	// Fullscreen
	SDL_SetWindowFullscreen(g.window, SDL_WINDOW_FULLSCREEN);

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
	g.movDown = g.movUp = g.movLeft = g.movRight = false;
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

<<<<<<< HEAD
=======
	// If an event is detected it will return true
>>>>>>> 92ed8a6931e964e2bd7dc8e4338e1580179d9b9a
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
<<<<<<< HEAD
				ret = false; // Exit program if 'x' is pressed
=======
				ret = false;
>>>>>>> 92ed8a6931e964e2bd7dc8e4338e1580179d9b9a
				break;
			case SDLK_SPACE:
				if (!g.shots.isAlive) {    // The player can only shot when the shot is not alive
					Mix_PlayChannel(-1, g.audio, 0);
					g.shots.x = g.shipX;
					g.shots.y = g.shipY;
					
					g.shots.isAlive = true;
				}
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
<<<<<<< HEAD
	if (g.shipX < 0) g.shipX += SHIP_SPEED;
	if (g.shipX > LENGTH - SPACESHIP_X) g.shipX -= SHIP_SPEED;
	if (g.shipY < 0) g.shipY += SHIP_SPEED;
	if (g.shipY > HEIGHT - SPACESHIP_Y) g.shipY -= SHIP_SPEED;
=======
	if (g.shipX == 0) g.shipX += 1;
	if (g.shipX == LENGTH - SPACESHIP_X) g.shipX -= 1;
	if (g.shipY == 0) g.shipY += 1;
	if (g.shipY == HEIGHT - SPACESHIP_Y) g.shipY -= 1;
>>>>>>> 92ed8a6931e964e2bd7dc8e4338e1580179d9b9a

	if (!g.shots.isAlive) {

		g.shots.x = g.shipX;
		g.shots.y = g.shipY;
	}
	else {

		if (g.shots.x < LENGTH) {
			
			g.shots.x += SHOT_SPEED;
		}
		else{

		g.shots.x = g.shipX;
		g.shots.y = g.shipY;
		
		g.shots.isAlive = false;
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
	if (g.shots.isAlive) {
		
		sprite = {

			g.shots.x,
			g.shots.y,
			LASER_X,
			LASER_Y
		};

		SDL_RenderCopy(g.renderer, g.shot, NULL, &sprite);
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

// Main program
int main(int argc, char* argv[]) {

	Start();

	while (CheckInput()) {

		MoveStuff();
		Draw();
	}

	Finish();

	return 0;
}