#include "CollisionController.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "Meteor.h"
#include "Player.h"
#include "MeteorController.h"
#include "TextureController.h"
#include "ScoreTexture.h"
#include "CollisionController.h"
#include "GameObject.h"
#include <set>

bool CollisionController::verifyMeteorCollisions(SDL_Renderer* renderer, TextureController* textureController, Player* player, MeteorController* meteorController) {

    bool collisionWithPlayer = false;

    std::vector<Meteor*>& meteors = meteorController->getMeteors(); // Referenz statt Kopie!

    for (size_t i = 0; i < meteors.size(); ++i) {
        Meteor* meteor = meteors[i];
        if (!meteor) continue;

        float meteorLeft = meteor->getX();
        float meteorRight = meteorLeft + meteor->getWidth();
        float meteorBottom = meteor->getY();
        float meteorTop = meteorBottom + meteor->getHeight();

        collisionWithPlayer = IsMeteorCollisionWithPlayerOccurred(meteor, player);
        if (collisionWithPlayer) {
            break;
        }

        auto& rockets = player->getRockets();
        for (auto it = rockets.begin(); it != rockets.end(); ) {
            Rocket* rocket = *it;

            float rocketLeft = rocket->getrocketBody().x;
            float rocketRight = rocketLeft + 25.0f;
            float rocketBottom = rocket->getrocketBody().y;
            float rocketTop = rocketBottom + 25.0f;

            if (rocketRight > meteorLeft && rocketLeft < meteorRight &&
                rocketTop > meteorBottom && rocketBottom < meteorTop) {

                std::cout << "Touched" << std::endl;
                it = rockets.erase(it); // Rakete entfernen
                player->getTextController()->updateCounterTexture();

                delete meteor;   // Meteor-Speicher freigeben
                meteors.erase(meteors.begin() + i); // Meteor aus Vektor entfernen
                --i; // Da wir ein Element entfernt haben, müssen wir den Index anpassen
                break;
            }
            else {
                ++it;
            }
        }
    }
    return collisionWithPlayer;
}

bool CollisionController::IsMeteorCollisionWithPlayerOccurred(Meteor* meteor, Player* player) {

    float meteorLeft = meteor->getX();
    float meteorRight = meteorLeft + meteor->getWidth();
    float meteorBottom = meteor->getY();
    float meteorTop = meteorBottom + meteor->getHeight();

    float playerLeft = player->getX();
    float playerRight = playerLeft + player->getWidth();
    float playerBottom = player->getY();
    float playerTop = playerBottom + player->getHeight();

    if (playerRight > meteorLeft && playerLeft < meteorRight &&
        playerTop > meteorBottom && playerBottom < meteorTop) {
        std::cout << "Touched a player" << std::endl;
        return true;
    }

    return false;
}
