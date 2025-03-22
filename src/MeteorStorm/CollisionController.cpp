#include "CollisionController.h"
#include <SDL3/SDL.h>
#include <iostream>
#include "Meteor.h"
#include "Player.h"
#include "MeteorController.h"
#include "TextureController.h"
#include "ScoreTexture.h"
#include "CollisionController.h"
#include "GameObject.h"

bool CollisionController::verifyMeteorCollisions(SDL_Renderer* renderer, TextureController* textureController, Player* player, MeteorController* meteorController) {

    bool collisionWithPlayer = false;

    Meteor** meteors = meteorController->getMeteors();
    for (int i = 0; i < 5; i++) {  // ✅ Iterate over the fixed-size array
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

        for (auto& rocket : player->getRockets()) {

            float rocketLeft = rocket->getrocketBody().x;
            float rocketRight = rocketLeft + 25.0f;
            float rocketBottom = rocket->getrocketBody().y;
            float rocketTop = rocketBottom + 25.0f;

            if (rocketRight > meteorLeft && rocketLeft < meteorRight &&
                rocketTop > meteorBottom && rocketBottom < meteorTop) {

                std::cout << "Touched" << std::endl;
                player->removeRocket(rocket);
                player->getTextController()->updateCounterTexture();

                delete meteor;
                meteors[i] = nullptr;  // ✅ Set original pointer in array to nullptr
                //delete rocket also
                break;
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




//bool CollisionController::verifyMeteorCollisions(SDL_Renderer* renderer, TextureController* textureController, Player* player, MeteorController* meteorController) {
//    bool collisionWithPlayer = false;
//
//    Meteor** meteors = meteorController->getMeteors();
//    for (int i = 0; i < 5; i++) {  // ✅ Durchlaufen des festen Arrays
//        Meteor* meteor = meteors[i];
//        if (!meteor) continue;
//
//        if (IsMeteorCollisionWithPlayerOccurred(meteor, player)) {
//            collisionWithPlayer = true;
//            break;
//        }
//
//        auto rockets = player->getRockets();
//        auto it = rockets.begin();
//        while (it != rockets.end()) {
//            Rocket* rocket = *it;
//            if (isCollision(rocket, meteor)) {
//                std::cout << "Touched" << std::endl;
//                it = rockets.erase(it); // Rakete entfernen
//                player->getTextController()->updateCounterTexture();
//
//                delete meteor;
//                meteors[i] = nullptr;  // ✅ Meteor im Array auf nullptr setzen
//                break;
//            }
//            else {
//                ++it;
//            }
//        }
//    }
//    return collisionWithPlayer;
//}
//
//bool CollisionController::IsMeteorCollisionWithPlayerOccurred(Meteor* meteor, Player* player) {
//    return isCollision(player, meteor);
//}
//
//bool CollisionController::isCollision(GameObject* obj1, GameObject* obj2) {
//    float left1 = obj1->getX();
//    float right1 = left1 + obj1->getWidth();
//    float bottom1 = obj1->getY();
//    float top1 = bottom1 + obj1->getHeight();
//
//    float left2 = obj2->getX();
//    float right2 = left2 + obj2->getWidth();
//    float bottom2 = obj2->getY();
//    float top2 = bottom2 + obj2->getHeight();
//
//    return (right1 > left2 && left1 < right2 && top1 > bottom2 && bottom1 < top2);
//}
