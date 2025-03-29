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
			posVal = player->getX();
		}
		else {
			posVal = player->getY();
		}
		int val = -1;
		float diff = 0.0f;
		while (val == -1 || diff < 100) {
			val = Helpers::getRandomValue(min, max);
			diff = std::abs(posVal - val);
		}

		return val;
	}

	Meteor::Meteor(Player* player, bool wantsACollWithPlayer) : player(player), wantsACollisionWithPlayer(wantsACollWithPlayer)
	{
		x = getRandomMeteorPos(0,750,0);
		y = getRandomMeteorPos(0,550,1);
		w = 50.0;
		h = 50.0;
		// Draw player
		meteorBody = { x,y,50.0f,50.0f };
	};
	void Meteor::updateForSpecDir(int result) {
		switch (result)
			//switch (Helpers::getRandomValue(1,4))
		{
		case 1:
			if (meteorBody.x > 740) {
				runRMeteorRendering(renderer);
				return;
			}
			meteorBody.x += 2;
			x += 2;
			break;
		case 2:
			if (meteorBody.x < 0) {
				runRMeteorRendering(renderer);
				return;
			}
			meteorBody.x -= 2;
			x -= 2;
			break;

		case 3:
			if (meteorBody.y > 540) {
				runRMeteorRendering(renderer);
				return;
			}
			meteorBody.y += 2;
			y += 2;
			break;

		case 4:
			if (meteorBody.y < 0) {
				runRMeteorRendering(renderer);
				return;
			}
			meteorBody.y -= 2;
			y -= 2;
			break;
			//case 2: enemyBody.x -= 10;break;
			//case 3: enemyBody.y += 10;break;
			//case 4: enemyBody.y -= 10;break;
		default: break;
		};
	}
	void Meteor::updatePos(SDL_Renderer* renderer) {


		/*if meteor does not want to hunt for a player, it will be just randomly moving. It's still dangerous for player, but does not try to destroy him.*/
		if (!wantsACollisionWithPlayer) {
			//move player randomly in particular direction
			updateForSpecDir(Helpers::getRandomValue(1, 4));
			runRMeteorRendering(renderer);
			return;
		}


		/*Calculate meteor position based on player position. Meteor strives to make equlal its x and y cord with player's one. So the diffrence between meteor and player
		should be mreduced to 0. x2- x1; y2- y1;*/

		//put some random number, that in case of its presence will move randomly a meteor. It is made for purpose to make game easier and to 
		// make meteros not ovelrlap so much
		int randomValue = Helpers::getRandomValue(0, 2);//higher the range, then the harder game is, since meteor will move more often in direction of player


		if (randomValue == 2) {
			updateForSpecDir(Helpers::getRandomValue(1, 4));
		}
		else {
			float diffXBetweenMeteorAndPlayer = x - player->getX();
			float diffYBetweenMeteorAndPlayer = y - player->getY();
			int result = 0;

			if (diffXBetweenMeteorAndPlayer < 0) {
				result = 1;
			}
			else if (diffXBetweenMeteorAndPlayer > 0) {
				result = 2;
			}

			updateForSpecDir(result);

			if (diffYBetweenMeteorAndPlayer < 0) {
				result = 3;
			}
			else if (diffYBetweenMeteorAndPlayer > 0) {
				result = 4;
			}

			updateForSpecDir(result);
		}
		

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
	bool Meteor::getWantsACollisionWithPlayer()  { return wantsACollisionWithPlayer; }