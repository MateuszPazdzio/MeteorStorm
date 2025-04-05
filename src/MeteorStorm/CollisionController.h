#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "MeteorController.h"
#include "TextureController.h"
#include "CollisionController.h"
#include "GameObject.h"

class CollisionController
{
private:
	bool IsMeteorCollisionWithPlayerOccurred(Meteor* meteor, Player* player);
public:
	bool verifyMeteorCollisions(SDL_Renderer* renderer, TextureController* textureController, Player* player, MeteorController* meteorController);
};

