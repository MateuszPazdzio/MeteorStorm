#pragma once
#include <SDL3/SDL.h>
#include "GameObject.h"

enum class Dir { UP , RIGHT, DOWN ,LEFT };  // Richtung als Enum
class Rocket : public GameObject
{
private:
	int id;
	float speed;
	Dir dir;
	float x;
	float y;
	SDL_FRect rocketBody;
	float width;
	float height;

public:
	Rocket(float startX, float startY, Dir playerDir, float width, float height);

	void updatePos(SDL_Renderer* renderer);
	void runRocketRendering(SDL_Renderer* renderer);
	SDL_FRect getrocketBody();
	int getRocketId();
	bool operator==(const Rocket& other) const;
	float getX() override;
	float getY() override;
	float getHeight() override;
	float getWidth() override;
	//float onCover() override;


};

