#pragma once
#include "Enemy.h"
#include "Player.h"
#include <SDL3/SDL.h>
class EnemyController
{
private:
	size_t maxEnemyCount;
	Enemy* enemyAlive[5]{ nullptr };
	Player* player;
public:
	struct Cord {
		float x;
		float y;
	};
	EnemyController(size_t maxEnemyCount, Player* player);
	void updatePos(SDL_Renderer* renderer);
	void generateEnemies();
	void clearEnemies();
	void checkIfAreaOverlapWithPlayer(std::vector<Rocket> rockets);
};

