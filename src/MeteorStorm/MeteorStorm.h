#ifndef SNAKE_H
#define SNAKE_H

#define SDL_MAIN_HANDLED  // Prevent SDL from redefining main()
#include <SDL3/SDL.h>
#include <string>

// Screen dimensions
constexpr int kScreenWidth{ 800 };
constexpr int kScreenHeight{ 600 };

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
