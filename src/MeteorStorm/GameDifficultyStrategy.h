#pragma once
class GameDifficultyStrategy
{
public:
	virtual void executeBehavior() = 0;
	virtual ~GameDifficultyStrategy() = default;
};

