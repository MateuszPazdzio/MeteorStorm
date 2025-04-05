#include "Texture.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

Texture::Texture(SDL_Renderer* renderer,std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font)
    : renderer(renderer),text(text), textRect(textRect), color(color), font(font) {}
