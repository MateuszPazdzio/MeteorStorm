#include "MeteorController.h"
#include "Meteor.h"
#include "Rocket.h"
#include "Helpers.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>
#include "MeteorStorm.h"
#include <vector>

MeteorController::MeteorController(size_t maxMeteorCount, Player* player, float meteorWidth, float meteorHeight)
    : maxMeteorCount(maxMeteorCount), player(player), meteorWidth(meteorWidth), meteorHeight(meteorHeight){
    meteorsAlive.assign(maxMeteorCount, nullptr); 
}

void MeteorController::updatePos(SDL_Renderer* renderer) {

    int meteorCount = 0;
    for (auto* meteor : meteorsAlive) {
        if (meteor) {
            meteorCount++;
            meteor->updatePos(renderer);
        }
    }

    for (size_t i = 0; i < maxMeteorCount - meteorCount; i++)
    {
        createMeteor();
    }
}

void MeteorController::createMeteor() {

    int predatorTreshold = std::ceil(predator_meteor_ratio * maxMeteorCount);
    bool meteorWantsToACollisionWithPlayer = Helpers::getRandomValue(1, maxMeteorCount) < predatorTreshold;
    meteorsAlive.push_back(new Meteor(player, meteorWantsToACollisionWithPlayer));

}

void MeteorController::clearMeteors() {

    for (auto* meteor : meteorsAlive) {
        delete meteor;
    }
    meteorsAlive.clear();
}

bool MeteorController::checkIfAreaOfMeteorOverlapsWithPlayer() {

    float playerLeft = player->getX();
    float playerRight = playerLeft + player->getWidth();
    float playerBottom = player->getY();
    float playerTop = playerBottom + player->getHeight();

    for (auto* meteor : meteorsAlive) {
        if (!meteor) continue;

        float meteorLeft = meteor->getX();
        float meteorRight = meteorLeft + meteor->getWidth();
        float meteorBottom = meteor->getY();
        float meteorTop = meteorBottom + meteor->getHeight();

        if (playerRight > meteorLeft && playerLeft < meteorRight &&
            playerTop > meteorBottom && playerBottom < meteorTop) {
            std::cout << "Touched a player" << std::endl;
            return true;
        }
    }
    return false;
}

void MeteorController::checkIfAreaOfMeteorOverlapsWithRocket(std::vector<Rocket*>& rockets) {

    auto rocketIt = rockets.begin();

    while (rocketIt != rockets.end()) {
        Rocket* rocket = *rocketIt;
        float rocketLeft = rocket->getrocketBody().x;
        float rocketRight = rocketLeft + 25.0f;
        float rocketBottom = rocket->getrocketBody().y;
        float rocketTop = rocketBottom + 25.0f;

        auto meteorIt = meteorsAlive.begin();

        while (meteorIt != meteorsAlive.end()) {

            Meteor* meteor = *meteorIt;

            if (!meteor) {
                ++meteorIt;
                continue;
            }

            float meteorLeft = meteor->getX();
            float meteorRight = meteorLeft + meteor->getWidth();
            float meteorBottom = meteor->getY();
            float meteorTop = meteorBottom + meteor->getHeight();

            if (rocketRight > meteorLeft && rocketLeft < meteorRight &&
                rocketTop > meteorBottom && rocketBottom < meteorTop) {

                std::cout << "Touched" << std::endl;
                player->getTextController()->updateCounterTexture();

                delete meteor;

                meteorIt = meteorsAlive.erase(meteorIt);
                rocketIt = rockets.erase(rocketIt); 

                break;
            }
            else {
                ++meteorIt;
            }
        }

        if (rocketIt != rockets.end()) {
            ++rocketIt;
        }
    }
}

std::vector<Meteor*>& MeteorController::getMeteors() {
    return meteorsAlive;
}
