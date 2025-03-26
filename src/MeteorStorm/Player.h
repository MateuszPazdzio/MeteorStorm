#pragma once
#include <SDL3/SDL.h>
#include "TextureController.h"
#include "Rocket.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include <set>

class Player : public GameObject
{
private:
	SDL_FRect player;
	int speed;
	void updatePos(SDL_Event e);
	SDL_Event event;
	TextureController* textureController;
	std::vector<Rocket*> rockets;
	std::set<SDL_Scancode> pressedKeys;

public:

	Player(int speed, TextureController* textureController);
	void handleInput(bool& running);
	float getX() override;
	float getY() override;
	float getHeight() override;
	float getWidth() override;
	SDL_FRect* getPlayer();
	std::vector<Rocket*> getRockets();
	void createRocket(float startX, float startY, float width, float height);
	void updateRocketPos(SDL_Renderer* renderer);
	void rotatePlayer(SDL_Event e);
	TextureController* getTextController();
	void removeRocket(Rocket* rocket);
	void updatePos();
	std::set<SDL_Scancode> getPressedKeys();
};



