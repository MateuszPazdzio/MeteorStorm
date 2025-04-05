#pragma once
#define SDL_MAIN_HANDLED  // Prevent SDL from redefining main()
#include <SDL3/SDL.h>
#include <string>

enum LEVEL {
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
};

void initGamePlay();
bool loadMedia();
void cleanup();

// Global Variables
extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;
extern SDL_Renderer* renderer;
extern float predator_meteor_ratio;//reflected in bool wantsACollisionWithPlayer in MEtoero construcotr/ represent ration of meteors that are 'hunting' for player
extern int player_speed;//reflected in bool wantsACollisionWithPlayer in MEtoero construcotr/ represent ration of meteors that are 'hunting' for player
extern bool running;
extern int meteors_count;
extern float meteorWidth;
extern float meteorHeight;
extern int meteorBaseInitialDistanceFromPlayer;
extern int X_LIMIT;
extern int Y_LIMIT;
extern int MOVE_STEP;
extern int meteorRandomMovmentBoundry;
extern bool levelChosen;