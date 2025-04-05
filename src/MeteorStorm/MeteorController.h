#pragma once
#include "Meteor.h"
#include "Player.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>

class MeteorController
{
private:
	size_t maxMeteorCount;
	Player* player;
	std::vector<Meteor*> meteorsAlive;
	float meteorWidth, meteorHeight;

public:
	MeteorController(size_t maxMeteorCount, Player* player, float meteorWidth, float meteorHeight);
	void updatePos(SDL_Renderer* renderer);
	void clearMeteors();
	void checkIfAreaOfMeteorOverlapsWithRocket(std::vector<Rocket*>& rockets);
	bool checkIfAreaOfMeteorOverlapsWithPlayer();
	std::vector<Meteor*>& getMeteors();
	void createMeteor();
};

