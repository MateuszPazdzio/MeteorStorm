#pragma once
#include "GameDifficultyStrategy.h"

class GameManager
{
private:
	GameDifficultyStrategy* gDS;
public:
	GameManager(GameDifficultyStrategy* gDS);
	void executeGameStrategy();
};

