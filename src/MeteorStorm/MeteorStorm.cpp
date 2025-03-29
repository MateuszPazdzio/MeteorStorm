#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers.h"
#include "Meteor.h"
#include "Player.h"
#include "MeteorController.h"
#include "TextureController.h"
#include "ScoreTexture.h"
#include "CollisionController.h"
#include "MeteorStorm.h"

// Screen dimensions
const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

float speed = 150.0f;
SDL_Renderer* renderer = { nullptr };

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Movement", SCREEN_WIDTH, SCREEN_HEIGHT,0);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() == -1) {
        return -1;
    }
    Player* player;
    TextureController* textureController;
    ScoreTexture* sT;
    MeteorController* meteorController;
    CollisionController* collisionController;

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    textureController = new TextureController(renderer);
    //renderer, location ,white font, font
    sT = new ScoreTexture(renderer,"Score: 0", { 50, 50, 70.0f, 50.0f }, {255, 255, 255, 255}, TTF_OpenFont("../assets/OpenSans.ttf", 24));

    textureController->addTexture(sT);

    player = new Player(10, textureController);
    meteorController = new MeteorController(5, player);
    collisionController = new CollisionController();

    while (running) {
        player->handleInput(running);
        player->updatePos();
        // Clear screen once
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        meteorController->updatePos(renderer);
        player->updateRocketPos(renderer);
        textureController->renderTexture();
        bool meteorCollidedWithPlayer = collisionController->verifyMeteorCollisions(renderer, textureController, player, meteorController);

        if (meteorCollidedWithPlayer) {
            textureController->showEndGameScreen(renderer);
            player->getPressedKeys().clear();
            delete player;
            delete meteorController;
            delete collisionController;
            delete textureController;

            textureController = new TextureController(renderer);
            sT = new ScoreTexture(renderer,"Score: 0", { 50, 50, 70.0f, 50.0f }, {255, 255, 255, 255}, TTF_OpenFont("../assets/OpenSans.ttf", 24));
            textureController->addTexture(sT);
            player = new Player(10, textureController);
            meteorController = new MeteorController(5, player);
            collisionController = new CollisionController();

            continue;

        }
    /*    meteorController.checkIfAreaOfMeteorOverlapsWithRocket(player->getRockets());
        if (meteorController.checkIfAreaOfMeteorOverlapsWithPlayer()) {
            break;
        }*/
        // Draw player
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, player->getPlayer());

        // Present everything
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // Delay to limit FPS (60 FPS)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

