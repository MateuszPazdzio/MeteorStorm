#pragma once
#include "Meteor.h"
#include "Player.h"
#include <SDL3/SDL.h>
class MeteorController
{
private:
	size_t maxMeteorCount;
	Meteor* meteorAlive[5]{ nullptr };
	Player* player;
public:
	struct Cord {
		float x;
		float y;
	};
	MeteorController(size_t maxMeteorCount, Player* player);
	void updatePos(SDL_Renderer* renderer);
	void generateMeteors();
	void clearMeteors();
	void checkIfAreaOfMeteorOverlapsWithRocket(std::vector<Rocket> rockets);
	bool checkIfAreaOfMeteorOverlapsWithPlayer();
	Meteor** getMeteors();
};

