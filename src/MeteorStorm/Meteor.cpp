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

	SDL_FRect meteorBody;

	int Meteor::getRandomMeteorPos(int min, int max, int xOry) {
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

	Meteor::Meteor(Player* player) : player(player)
	{
		x = getRandomMeteorPos(0,750,0);
		y = getRandomMeteorPos(0,550,1);
		w = 50.0;
		h = 50.0;
		// Draw player
		meteorBody = { x,y,50.0f,50.0f };
	};

	void Meteor::updatePos(SDL_Renderer* renderer) {
		switch (Helpers::getRandomValue(1,4))
		{
			case 1: 
				if (meteorBody.x > 740) {
					runRMeteorRendering(renderer);
					return;
				}
				meteorBody.x += 10;
				x += 10;
				break;
			case 2:
				if (meteorBody.x < 0) {
					runRMeteorRendering(renderer);
					return;
				}
				meteorBody.x -= 10;
				x -= 10;
				break;

			case 3:
				if (meteorBody.y > 540) {
					runRMeteorRendering(renderer);
					return;
				}
				meteorBody.y += 10;
				y += 10;
				break;

			case 4:
				if (meteorBody.y < 0) {
					runRMeteorRendering(renderer);
					return;
				}
				meteorBody.y -= 10;
				y -= 10;
				break;
			//case 2: enemyBody.x -= 10;break;
			//case 3: enemyBody.y += 10;break;
			//case 4: enemyBody.y -= 10;break;
			default: break;
		};
		runRMeteorRendering(renderer);

	}

	void Meteor::runRMeteorRendering(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
		SDL_RenderFillRect(renderer, &meteorBody);
	}

	float Meteor::getX() { return x; }
	float Meteor::getY()  { return y; }
	float Meteor::getWidth()  { return w; }
	float Meteor::getHeight()  { return h; }