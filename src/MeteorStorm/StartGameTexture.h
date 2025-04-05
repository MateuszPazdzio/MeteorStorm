#pragma once
#include "Texture.h"
#include <map>
#include <iostream>

class StartGameTexture : public Texture
{
public:
	StartGameTexture(SDL_Renderer* renderer, std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font);

	void render() override;
	void createTexture() override;

private:
	SDL_Texture* textureFromSurface;
	std::map<std::string, std::string> textureTextDict = {
		{"easy", "1. EASY"},
		{"medium", "2. MEDIUM"},
		{"hard" , "3. HARD"}
	};
};

