#include "EnemyController.h"
#include "Enemy.h"
#include "Rocket.h"
#include <SDL3/SDL.h>
#include <iostream>
size_t maxEnemyCount;
Enemy* enemyAlive[5]{ nullptr };
Player* player;

EnemyController::EnemyController(size_t maxEnemyCount, Player* player) 
    : maxEnemyCount(maxEnemyCount), player(player) {

};
void EnemyController::updatePos(SDL_Renderer* renderer) {
    //based on level check enemy count, that are alive
    int enemyCount = 0;

    for (auto* enemy : enemyAlive) {
        if (enemy) enemyCount++;
    }

    //update enemy pos
    for (auto* enemy : enemyAlive) {
        if (enemy) enemy->updatePos(renderer);
    }


    if (enemyCount < maxEnemyCount) {
        int enemyToAdd = maxEnemyCount - enemyCount;
        for (size_t i = 0; i < maxEnemyCount && enemyToAdd > 0; i++)
        {
            if (enemyAlive[i] == nullptr) {
                enemyAlive[i] = new Enemy(player);
                enemyToAdd--;
            }
        }
    }
}
void EnemyController::generateEnemies() {

}

void clearEnemies() {
    for (size_t i = 0; i < maxEnemyCount; i++) {
        if (enemyAlive[i] != nullptr) {
            delete enemyAlive[i];  // Free memory
            enemyAlive[i] = nullptr;
        }
    }
}

void EnemyController::checkIfAreaOverlapWithPlayer(std::vector<Rocket> rockets) {

    for (auto& rocket : rockets) {

        float playerLeft = rocket.getrocketBody().x;
        float playerRight = playerLeft + 25.0f;
        float playerBottom = rocket.getrocketBody().y;
        float playerTop = playerBottom + 25.0f;

        for (auto*& enemy : enemyAlive) {
            if (!enemy) continue;

            float enemyLeft = enemy->getX();
            float enemyRight = enemyLeft + enemy->getWidth();
            float enemyBottom = enemy->getY();
            float enemyTop = enemyBottom + enemy->getHeight();

            if (playerRight > enemyLeft && playerLeft < enemyRight &&
                playerTop > enemyBottom && playerBottom < enemyTop) {
                std::cout << "Touched" << std::endl;
                player->getTextController()->updateCounterTexture();
                delete enemy;
                enemy = nullptr;
            }
        }
    }


}


