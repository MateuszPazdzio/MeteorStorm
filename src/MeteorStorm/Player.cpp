#include <SDL3/SDL.h>
#include "Player.h"
#include "TextureController.h"
#include <algorithm>
#include <iostream>
#include <vector>

int speed;
SDL_FRect player;
SDL_Event event;
std::vector<Rocket> rockets;
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
            if (event.key.scancode == SDL_SCANCODE_UP || event.key.scancode == SDL_SCANCODE_DOWN || event.key.scancode == SDL_SCANCODE_LEFT || event.key.scancode == SDL_SCANCODE_RIGHT) {
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
                createRocket(player.x + 25, player.y + 25);
            }
        }
    }
}

void Player::updatePos(SDL_Event e) {

    switch (e.key.scancode) {
    case SDL_SCANCODE_UP:    player.y -= speed; player.y; break;
    case SDL_SCANCODE_DOWN:  player.y += speed; player.y; break;
    case SDL_SCANCODE_LEFT:  player.x -= speed; player.x; break;
    case SDL_SCANCODE_RIGHT: player.x += speed; player.x; break;
    }

    //textureController->updateCounterTexture();
}

TextureController* Player::getTextController() {
    return textureController;
}

std::vector<Rocket> Player::getRockets() {
    return rockets;
}
float Player::getPlayerPosX() {
    return player.x;
}

float Player::getPlayerPosY() {
    return player.y;
}

float Player::getPlayerWidth() {
    return player.w;
}
float Player::getPlayerHeight() {
    return player.h;
}
SDL_FRect* Player::getPlayer() {
    return &player;
}

void Player::createRocket(float startX, float startY) {
    rockets.push_back(Rocket(startX, startY, playerDir));
}

void Player::updateRocketPos(SDL_Renderer* renderer) {
    for (auto& rocket : rockets) {
        rocket.updatePos(renderer);
        SDL_FRect rocketBody = rocket.getrocketBody();
        if ((rocketBody.x + rocketBody.w) > SCREEN_WIDTH || (rocketBody.x < 0) || (rocketBody.y - rocketBody.h) > SCREEN_HEIGHT || (rocketBody.y < 0)) {
             int rocketToDeleteId = rocket.getRocketId();

            std::cout << "Removing Rocket ID: " << rocket.getRocketId() << std::endl;

            auto it = std::find(rockets.begin(), rockets.end(), rocket);
            int rocketIdx = 0;
            if (it!=rockets.end()) {
                rocketIdx = std::distance(rockets.begin(), it);
            }
            rockets.erase(rockets.begin() + rocketIdx);
        }
    }



}
void Player::rotatePlayer(SDL_Event e) {
    switch (e.key.scancode) {
        case SDL_SCANCODE_1:    playerDir = Dir::UP; break;
        case SDL_SCANCODE_2:    playerDir = Dir::RIGHT; break;
        case SDL_SCANCODE_3:  playerDir = Dir::DOWN; break;
        case SDL_SCANCODE_4:  playerDir = Dir::LEFT; break;
    }
}