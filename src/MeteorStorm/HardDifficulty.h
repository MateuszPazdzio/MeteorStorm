#pragma once
#include "GameDifficultyStrategy.h"

class HardDifficulty : public GameDifficultyStrategy
{
public:
	void executeBehavior() override;
};

