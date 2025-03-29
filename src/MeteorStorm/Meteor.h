#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "GameObject.h"

class Meteor : public GameObject
{
private:
	
	float x;
	float y;
	float w;
	float h;
	int getRandomMeteorPos(int min, int max,int xOry);
	void runRMeteorRendering(SDL_Renderer* renderer);
	SDL_FRect meteorBody;
	Player* player;
	bool wantsACollisionWithPlayer;

public:
	Meteor(Player* player, bool wantsACollisionWithPlayer);

	void updatePos(SDL_Renderer* renderer);
	float getHeight();
	float getX();
	float getY();
	float getWidth();
	void updateForSpecDir(int result);
	bool getWantsACollisionWithPlayer();
};

