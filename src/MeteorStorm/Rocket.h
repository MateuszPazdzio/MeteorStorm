#pragma once
#include <SDL3/SDL.h>

enum class Dir { UP , RIGHT, DOWN ,LEFT };  // Richtung als Enum
class Rocket
{
private:
	int id;
	float speed;
	Dir dir;
	float x;
	float y;
	SDL_FRect rocketBody;

public:
	Rocket(float startX, float startY, Dir playerDir);

	void updatePos(SDL_Renderer* renderer);
	void runRocketRendering(SDL_Renderer* renderer);
	SDL_FRect getrocketBody();
	int getRocketId();
	bool operator==(const Rocket& other) const;
};

