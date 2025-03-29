#ifndef SNAKE_H
#define SNAKE_H

#define SDL_MAIN_HANDLED  // Prevent SDL from redefining main()
#include <SDL3/SDL.h>
#include <string>

// Screen dimensions
constexpr int kScreenWidth{ 800 };
constexpr int kScreenHeight{ 600 };
const float PREDATOR_METEOR_RATIO = 0.5;//reflected in bool wantsACollisionWithPlayer in MEtoero construcotr/ represent ration of meteors that are 'hunting' for player


// Function declarations
bool init();
bool loadMedia();
void close();

// Global Variables
extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;
extern SDL_Renderer* renderer;
#endif // SNAKE_H
