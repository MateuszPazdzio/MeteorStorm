#pragma once
#include "GameDifficultyStrategy.h"

class EasyDifficulty : public GameDifficultyStrategy
{

public:
	// Inherited via GameDifficultyStrategy
	void executeBehavior() override;
};

