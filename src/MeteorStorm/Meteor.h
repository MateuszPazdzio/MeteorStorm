#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
class Enemy
{
private:
	
	float x;
	float y;
	float w;
	float h;
	int getRandomEnemyPos(int min, int max,int xOry);
	void runREnemyRendering(SDL_Renderer* renderer);
	SDL_FRect enemyBody;
	Player* player;

public:
	Enemy(Player* player);

	void updatePos(SDL_Renderer* renderer);
	float getHeight();
	float getX();
	float getY();
	float getWidth();

};

