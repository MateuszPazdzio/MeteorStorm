#include <SDL3/SDL.h>
#include "Player.h"
#include "TextureController.h"
#include <algorithm>
#include <iostream>
#include <vector>

int speed;
SDL_FRect player;
SDL_Event event;
std::vector<Rocket*> rockets;
Dir playerDir = Dir::LEFT;

const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

Player::Player(int s, TextureController* textureController) : speed(s), textureController(textureController) {
    player = { 200.0f, 200.0f, 50.0f, 50.0f };
}

void Player::handleInput(bool& running) {

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.scancode == SDL_SCANCODE_UP ||
                event.key.scancode == SDL_SCANCODE_DOWN ||
                event.key.scancode == SDL_SCANCODE_LEFT ||
                event.key.scancode == SDL_SCANCODE_RIGHT) {
                updatePos(event);
            }
            if (event.key.scancode == SDL_SCANCODE_1 ||
                event.key.scancode == SDL_SCANCODE_2 ||
                event.key.scancode == SDL_SCANCODE_3 ||
                event.key.scancode == SDL_SCANCODE_4) {
                rotatePlayer(event);
            }

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

void Player::updatePos(SDL_Event e) {

    float yCopy = player.y;
    float xCopy = player.x;

    switch (e.key.scancode) {
        case SDL_SCANCODE_UP:
            if ((yCopy - speed) >= 0) {
                player.y -= speed;
            }
            break;

        case SDL_SCANCODE_DOWN:
            if ((yCopy + speed) <= (SCREEN_HEIGHT - player.h)) {
                player.y += speed;
            }
            break;

        case SDL_SCANCODE_LEFT:
            if ((xCopy - speed) >= 0) {
                player.x -= speed;
            }
            break;

        case SDL_SCANCODE_RIGHT:
            if ((xCopy + speed) <= (SCREEN_WIDTH - player.w)) {
                player.x += speed;
            }
            break;
    }
}

TextureController* Player::getTextController() {
    return textureController;
}

std::vector<Rocket*> Player::getRockets() {
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
        if ((rocketBody.x + rocketBody.w) > SCREEN_WIDTH || (rocketBody.x < 0) || (rocketBody.y - rocketBody.h) > SCREEN_HEIGHT || (rocketBody.y < 0)) {
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