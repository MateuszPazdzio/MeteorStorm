#include "MeteorController.h"
#include "Meteor.h"
#include "Rocket.h"
#include <SDL3/SDL.h>
#include <iostream>
size_t maxMeteorCount;
Meteor* meteorAlive[5]{ nullptr };
Player* player;

MeteorController::MeteorController(size_t maxMeteorCount, Player* player)
    : maxMeteorCount(maxMeteorCount), player(player) {

};
void MeteorController::updatePos(SDL_Renderer* renderer) {
    //based on level check enemy count, that are alive
    int meteorCount = 0;

    for (auto* meteor : meteorAlive) {
        if (meteor) meteorCount++;
    }

    //update meteor pos
    for (auto* meteor : meteorAlive) {
        if (meteor) meteor->updatePos(renderer);
    }


    if (meteorCount < maxMeteorCount) {
        int meteorToAdd = maxMeteorCount - meteorCount;
        for (size_t i = 0; i < maxMeteorCount && meteorToAdd > 0; i++)
        {
            if (meteorAlive[i] == nullptr) {
                meteorAlive[i] = new Meteor(player);
                meteorToAdd--;
            }
        }
    }
}
void MeteorController::generateMeteors() {

}

void clearMeteors() {
    for (size_t i = 0; i < maxMeteorCount; i++) {
        if (meteorAlive[i] != nullptr) {
            delete meteorAlive[i];  // Free memory
            meteorAlive[i] = nullptr;
        }
    }
}

void MeteorController::checkIfAreaOverlapWithPlayer(std::vector<Rocket> rockets) {

    for (auto& rocket : rockets) {

        float playerLeft = rocket.getrocketBody().x;
        float playerRight = playerLeft + 25.0f;
        float playerBottom = rocket.getrocketBody().y;
        float playerTop = playerBottom + 25.0f;

        for (auto*& meteor : meteorAlive) {
            if (!meteor) continue;

            float meteorLeft = meteor->getX();
            float meteorRight = meteorLeft + meteor->getWidth();
            float meteorBottom = meteor->getY();
            float meteorTop = meteorBottom + meteor->getHeight();

            if (playerRight > meteorLeft && playerLeft < meteorRight &&
                playerTop > meteorBottom && playerBottom < meteorTop) {
                std::cout << "Touched" << std::endl;
                player->getTextController()->updateCounterTexture();
                delete meteor;
                meteor = nullptr;
            }
        }
    }


}


