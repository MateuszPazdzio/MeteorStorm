#include "GameManager.h"
#include "GameDifficultyStrategy.h"

GameManager::GameManager(GameDifficultyStrategy* gDS) : gDS(gDS){}

void GameManager::executeGameStrategy() {
	gDS->executeBehavior();
}