#pragma once
#include <SDL3/SDL.h>
#include "TextureController.h"
#include "Rocket.h"
#include <iostream>
#include <vector>

class Player
{
private:
	SDL_FRect player;
	int speed;
	void updatePos(SDL_Event e);
	SDL_Event event;
	TextureController* textureController;
	std::vector<Rocket> rockets;

public:

	Player(int speed, TextureController* textureController);
	void handleInput(bool& running);
	float getPlayerPosX();
	float getPlayerPosY();
	float getPlayerWidth();
	float getPlayerHeight();
	SDL_FRect* getPlayer();
	std::vector<Rocket> getRockets();
	void createRocket(float startX, float startY);
	void updateRocketPos(SDL_Renderer* renderer);
	void rotatePlayer(SDL_Event e);
	TextureController* getTextController();
};



