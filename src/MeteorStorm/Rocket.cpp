#include "Rocket.h"
#include <SDL3/SDL.h>

int lastId = 0;

Rocket::Rocket(float startX, float startY, Dir playerDir)
    : x(startX), y(startY), dir(playerDir), speed(30.0f) {
    rocketBody = { startX, startY, 25.0f,25.0f };
    lastId += 1;
    id = lastId;
}

void Rocket::updatePos(SDL_Renderer* renderer) {
    switch (dir) {
        case Dir::LEFT:  rocketBody.x -= speed; break;
        case Dir::RIGHT: rocketBody.x += speed; break;
        case Dir::UP:    rocketBody.y -= speed; break;
        case Dir::DOWN:  rocketBody.y += speed; break;
    }

    runRocketRendering(renderer);
}

void Rocket::runRocketRendering(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
    SDL_RenderFillRect(renderer, &rocketBody);
}

SDL_FRect Rocket::getrocketBody() { return rocketBody; }

int Rocket::getRocketId() { return id; }

bool Rocket::operator==(const Rocket& other) const {
    return this->id == other.id;  // More efficient
}