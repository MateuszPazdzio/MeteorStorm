#include "Texture.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Texture::Texture(SDL_Renderer* renderer, SDL_FRect textRect, SDL_Color color, TTF_Font* font)
    : renderer(renderer), textRect(textRect), color(color), font(font) {
    // Base constructor logic (can be empty for abstract classes)
}
