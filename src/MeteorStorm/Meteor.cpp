#include "Meteor.h"
#include <iostream>
#include <random>
#include <SDL3/SDL.h>
#include "Helpers.h"
#include "Player.h"
#include "MeteorStorm.h"

	/*@meteorPosCoord might by x or y coordinate
	@playerPos might relate to y or x coordinate*/

	float Meteor::generateRandomMeteorPosition(int min, int max, float playerPos) {
		//we assume that meteor is a square

		int randomMeteorInitPos;
		float distanceBetweenPlayerAndMeteor;

		do {

			randomMeteorInitPos = Helpers::getRandomValue(min, max);
			distanceBetweenPlayerAndMeteor = std::abs(playerPos - randomMeteorInitPos);

		} while (distanceBetweenPlayerAndMeteor < meteorBaseInitialDistanceFromPlayer);

		return randomMeteorInitPos;
	}

	Meteor::Meteor(Player* player, bool wantsACollWithPlayer) : player(player), wantsACollisionWithPlayer(wantsACollWithPlayer)
	{
		meteorBody = { generateRandomMeteorPosition(0,750,player->getX()),generateRandomMeteorPosition(0,550,player->getY()),meteorWidth, meteorHeight};
		movements = {
			{Direction::EAST , {&meteorBody.x,  MOVE_STEP,  X_LIMIT}},
			{Direction::WEST , {&meteorBody.x, -MOVE_STEP,  0      }},
			{Direction::SOUTH , {&meteorBody.y,  MOVE_STEP,  Y_LIMIT }},
			{Direction::NORTH , {&meteorBody.y, -MOVE_STEP,  0       }},
		};
	};

	void Meteor::updateForSpecDir(Direction direction) {
		
			Movement& move = movements[direction];

			if ((move.delta > 0 && *move.coordinate > move.limit) ||
				(move.delta < 0 && *move.coordinate < move.limit)) {
				runMeteorRendering(renderer);
			}
			else {
				*move.coordinate += move.delta;
			}
	}

	void Meteor::updatePos(SDL_Renderer* renderer) {


		/*if meteor does not want to hunt for a player, it will be just randomly moving. It's still dangerous for player, but does not try to destroy him.*/
		if (!wantsACollisionWithPlayer) {
			//move player randomly in particular direction
			updateForSpecDir(Helpers::generateRandomDirection());
			runMeteorRendering(renderer);
			return;
		}


		/*Calculate meteor position based on player position. Meteor strives to make equlal its x and y cord with player's one. So the diffrence between meteor and player
		should be reduced to 0. x2- x1; y2- y1;*/

		int randomValue = Helpers::getRandomValue(0, meteorRandomMovmentBoundry);//higher the range, then the harder game is, since meteor will move more often in direction of player
		
		//so when luckly it hits range boundry meteor should move in random direction
		if (randomValue == meteorRandomMovmentBoundry) {
			updateForSpecDir(Helpers::generateRandomDirection());
		}
		else 
		{
			/*move meteor right when its less then 0 (1:LEFT)
			move meteor left when its greater or equal then 0 (3:RIGHT)*/
			updateForSpecDir(static_cast<Direction>((meteorBody.x - player->getX()) <= 0 ? 1 : 3));

			/*move meteor top when its greater or equal then 0 (0:NORTH)
			move meteor bottom when its less then 0 (3:RIGHT)*/
			updateForSpecDir(static_cast<Direction>((meteorBody.y - player->getY()) >= 0 ? 0 : 2));

		}
		

		runMeteorRendering(renderer);
	}

	void Meteor::runMeteorRendering(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
		SDL_RenderFillRect(renderer, &meteorBody);
	}

	float Meteor::getX() { return meteorBody.x; }
	float Meteor::getY()  { return meteorBody.y; }
	float Meteor::getWidth()  { return meteorBody.w; }
	float Meteor::getHeight()  { return meteorBody.h; }
	bool Meteor::getWantsACollisionWithPlayer()  { return wantsACollisionWithPlayer; }