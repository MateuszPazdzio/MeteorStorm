#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Texture.h"
#include <vector>
#include "MeteorStorm.h"

class TextureController
{
private:
	SDL_Renderer* renderer;
	std::vector<Texture*> textures;

public:
	TextureController(SDL_Renderer* renderer);
	void renderTexture();
	void addTexture(Texture* texture);
	void updateCounterTexture();
	void showEndGameScreen(SDL_Renderer* renderer);
	void clear();
	bool handleEndGameInput();
	bool isEscapeOrEnterBtnPressedDown(const SDL_Event& event);
	void handleStartGameInput(bool& showStartGameScr);
	bool isLevelOptionButtonPressed(const SDL_Event& event);
	void showStartGameScreen(SDL_Renderer* renderer);
};

