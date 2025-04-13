#pragma once
#include "GameDifficultyStrategy.h"

class MediumDifficulty : public GameDifficultyStrategy
{
public:
	void executeBehavior() override;
};

