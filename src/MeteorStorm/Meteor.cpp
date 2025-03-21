#include "Meteor.h"
#include <iostream>
#include <random>
#include <SDL3/SDL.h>
#include "Helpers.h"
#include "Player.h"
#include "MeteorStorm.h"

	float x;
	float y;
	float w;
	float h;

	SDL_FRect enemyBody;

	int Enemy::getRandomEnemyPos(int min, int max, int xOry) {
		float posVal = 0.0f;
		if (xOry == 0) {
			posVal = player->getPlayerPosX();
		}
		else {
			posVal = player->getPlayerPosY();
		}
		int val = -1;
		float diff = 0.0f;
		while (val == -1 && diff < 60) {
			val = Helpers::getRandomValue(min, max);
			diff = std::abs(posVal - val);
		}

		return val;
	}

	Enemy::Enemy(Player* player) : player(player)
	{
		x = getRandomEnemyPos(0,750,0);
		y = getRandomEnemyPos(0,550,1);
		w = 50.0;
		h = 50.0;
		// Draw player
		enemyBody = { x,y,50.0f,50.0f };
	};

	void Enemy::updatePos(SDL_Renderer* renderer) {
		switch (Helpers::getRandomValue(1,4))
		{
			case 1: 
				if (enemyBody.x > 740) {
					runREnemyRendering(renderer);
					return;
				}
				enemyBody.x += 10;
				x += 10;
				break;
			case 2:
				if (enemyBody.x < 0) {
					runREnemyRendering(renderer);
					return;
				}
				enemyBody.x -= 10;
				x -= 10;
				break;

			case 3:
				if (enemyBody.y > 540) {
					runREnemyRendering(renderer);
					return;
				}
				enemyBody.y += 10;
				y += 10;
				break;

			case 4:
				if (enemyBody.y < 0) {
					runREnemyRendering(renderer);
					return;
				}
				enemyBody.y -= 10;
				y -= 10;
				break;
			//case 2: enemyBody.x -= 10;break;
			//case 3: enemyBody.y += 10;break;
			//case 4: enemyBody.y -= 10;break;
			default: break;
		};
		runREnemyRendering(renderer);

	}

	void Enemy::runREnemyRendering(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
		SDL_RenderFillRect(renderer, &enemyBody);
	}

	float Enemy::getX() { return x; }
	float Enemy::getY()  { return y; }
	float Enemy::getWidth()  { return w; }
	float Enemy::getHeight()  { return h; }