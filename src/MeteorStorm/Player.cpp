#include <SDL3/SDL.h>
#include "Player.h"
#include "Helpers.h"
#include "TextureController.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include "Constants.h";

int speed;
SDL_FRect player;
SDL_Event event;
std::vector<Rocket*> rockets;
Dir playerDir = Dir::LEFT;

Player::Player(int s, TextureController* textureController) : speed(s), textureController(textureController) {
    player = { (float)Helpers::getRandomValue(0, 750), (float)Helpers::getRandomValue(0, 550), 50.0f, 50.0f };
}
void Player::handleInput(bool& running) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {
            pressedKeys.insert(event.key.scancode);  // Add pressed key
        }

        if (event.type == SDL_EVENT_KEY_UP) {
            pressedKeys.erase(event.key.scancode);  // Remove ONLY the released key
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {


            if (event.key.scancode == SDL_SCANCODE_1 ||
                event.key.scancode == SDL_SCANCODE_2 ||
                event.key.scancode == SDL_SCANCODE_3 ||
                event.key.scancode == SDL_SCANCODE_4) {
                rotatePlayer(event);
            }

        }

        if (event.type == SDL_EVENT_KEY_UP) {

            //pressedKeysEvents.erase(event.key.scancode);
            //pressedKeys.erase(event.key.scancode);

            if (event.key.scancode == SDL_SCANCODE_SPACE) {
                /// <summary>
                ///move to Rocket Controller since it is neccesery to rotate warfare
                /// </summary>
                //TO DO: apply for rocket build strategy size
                float rocketWidth = 25.0f;
                float rocketHeight = 25.0f;
                createRocket(player.x + 25, player.y + 25, rocketWidth, rocketHeight);

            }
        }
    }
}

void Player::updatePos() {
    float yCopy = player.y;
    float xCopy = player.x;

    if (pressedKeys.count(SDL_SCANCODE_UP) && (yCopy - speed) >= 0) {
        player.y -= speed;
    }
    if (pressedKeys.count(SDL_SCANCODE_DOWN) && (yCopy + speed) <= (Constants::SCREEN_HEIGHT - player.h)) {
        player.y += speed;
    }
    if (pressedKeys.count(SDL_SCANCODE_LEFT) && (xCopy - speed) >= 0) {
        player.x -= speed;
    }
    if (pressedKeys.count(SDL_SCANCODE_RIGHT) && (xCopy + speed) <= (Constants::SCREEN_WIDTH - player.w)) {
        player.x += speed;
    }
}

TextureController* Player::getTextController() {
    return textureController;
}

std::vector<Rocket*>& Player::getRockets() {
    return rockets;
}

float Player::getX() {
    return player.x;
}

float Player::getY() {
    return player.y;
}

float Player::getWidth() {
    return player.w;
}
float Player::getHeight() {
    return player.h;
}
SDL_FRect* Player::getPlayer() {
    return &player;
}

void Player::createRocket(float startX, float startY, float rocketWidth, float  rocketHeight) {
    rockets.push_back(new Rocket(startX, startY, playerDir, rocketWidth, rocketHeight));
}

void Player::updateRocketPos(SDL_Renderer* renderer) {
    for (Rocket* rocket : rockets) {
        rocket->updatePos(renderer);
        SDL_FRect rocketBody = rocket->getrocketBody();
        if ((rocketBody.x + rocketBody.w) > Constants::SCREEN_WIDTH || (rocketBody.x < 0) || (rocketBody.y - rocketBody.h) > Constants::SCREEN_HEIGHT || (rocketBody.y < 0)) {
            removeRocket(rocket);
        }
    }
}
//Rocket has been destroyes or moved out of screen
void Player::removeRocket(Rocket* rocket) {

    int rocketToDeleteId = rocket->getRocketId();

    std::cout << "Removing Rocket ID: " << rocket->getRocketId() << std::endl;
    auto it = std::find(rockets.begin(), rockets.end(), rocket);
    delete* it;
    rockets.erase(it);
}

void Player::rotatePlayer(SDL_Event e) {
    switch (e.key.scancode) {
        case SDL_SCANCODE_1:    playerDir = Dir::UP; break;
        case SDL_SCANCODE_2:    playerDir = Dir::RIGHT; break;
        case SDL_SCANCODE_3:  playerDir = Dir::DOWN; break;
        case SDL_SCANCODE_4:  playerDir = Dir::LEFT; break;
    }
}

std::set<SDL_Scancode> Player::getPressedKeys() {
    return pressedKeys;
}