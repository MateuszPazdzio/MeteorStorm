#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "GameObject.h"
#include <map>
enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};
class Meteor : public GameObject
{

struct Movement {
	float* coordinate;
	int delta;
	int limit;
};

private:
	int generateRandomMeteorPosition(int min, int max,int xOry);
	float generateRandomMeteorPosition(int min, int max, float meteorPosCoord);
	void runMeteorRendering(SDL_Renderer* renderer);
	SDL_FRect meteorBody;
	Player* player;
	bool wantsACollisionWithPlayer;
	std::map<Direction, Movement> movements;

public:
	Meteor(Player* player, bool wantsACollisionWithPlayer);

	void updatePos(SDL_Renderer* renderer);
	float getHeight();
	float getX();
	float getY();
	float getWidth();
	void updateForSpecDir(Direction direction);
	bool getWantsACollisionWithPlayer();
};

