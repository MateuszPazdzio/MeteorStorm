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

Meteor** MeteorController::getMeteors() {
    return meteorAlive;
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
//dodac texture game over i sprzatniecie ca³ej zawartosci ekranu w momencie jej wyswieltenia, jezeli naciskasz Enter to gra leci na nowo
/*To DO: wygenerowac teksture petli ktora zmiata wszystkie rzeczy i reaguje tylko ne enter lub ESC - dodac do TextureController EndGameTexture, rozwazyc
czy texture powienien miec pole z nazwa ekranu na ktorej ma sie wyswieltac. wtedy moglyby byc renderowane tylko te teksture z vectora ktore sa widoczne na danym
ekranie.*/

bool MeteorController::checkIfAreaOfMeteorOverlapsWithPlayer() {

    float playerLeft = player->getX();
    float playerRight = playerLeft + player->getWidth();
    float playerBottom = player->getY();
    float playerTop = playerBottom + player->getHeight();

    bool playerHit = false;

    for (auto*& meteor : meteorAlive) {
        if (!meteor) continue;

        float meteorLeft = meteor->getX();
        float meteorRight = meteorLeft + meteor->getWidth();
        float meteorBottom = meteor->getY();
        float meteorTop = meteorBottom + meteor->getHeight();

        if (playerRight > meteorLeft && playerLeft < meteorRight &&
            playerTop > meteorBottom && playerBottom < meteorTop) {
            std::cout << "Touched a player" << std::endl;
            playerHit = true;
            break;
        }
    }

    return playerHit;
}
void MeteorController::checkIfAreaOfMeteorOverlapsWithRocket(std::vector<Rocket> rockets) {

    for (auto& rocket : rockets) {

        float rocketLeft = rocket.getrocketBody().x;
        float rocketRight = rocketLeft + 25.0f;
        float rocketBottom = rocket.getrocketBody().y;
        float rocketTop = rocketBottom + 25.0f;

        for (auto*& meteor : meteorAlive) {
            if (!meteor) continue;

            float meteorLeft = meteor->getX();
            float meteorRight = meteorLeft + meteor->getWidth();
            float meteorBottom = meteor->getY();
            float meteorTop = meteorBottom + meteor->getHeight();

            if (rocketRight > meteorLeft && rocketLeft < meteorRight &&
                rocketTop > meteorBottom && rocketBottom < meteorTop) {
                std::cout << "Touched" << std::endl;
                player->getTextController()->updateCounterTexture();
                delete meteor;
                meteor = nullptr;
            }
        }
    }


}


