#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Texture
{
public:
	//Texture();
    Texture(SDL_Renderer* renderer, std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font);
	virtual ~Texture() = default;
	virtual void render() = 0;
	virtual void createTexture() = 0;

protected:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_FRect textRect;
	SDL_Color color;
	std::string text;
};

