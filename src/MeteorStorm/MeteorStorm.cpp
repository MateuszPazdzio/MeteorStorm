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
#include "Constants.h"
#include "GameManager.h"
#include "GameDifficultyStrategy.h"
#include "EasyDifficulty.h"
#include "MediumDifficulty.h"
#include "HardDifficulty.h"
#include <map>

//struct GameConfig {
//    float predator_meteor_ratio;
//    int player_speed;
//    bool running;
//    int meteors_count;
//    float meteorWidth;
//    float meteorHeight;
//    int meteorBaseInitialDistanceFromPlayer;
//    int X_LIMIT;
//    int Y_LIMIT;
//    int MOVE_STEP;
//    int meteorRandomMovmentBoundry;
//};


//default values:
float predator_meteor_ratio = 0.5f;
int player_speed = 10;
bool running = true;
int meteors_count = 5;
float meteorWidth = 50.0f;
float meteorHeight = 50.0f;
int meteorBaseInitialDistanceFromPlayer = 100;
int X_LIMIT = 740;
int Y_LIMIT = 540;
int MOVE_STEP = 2;
int meteorRandomMovmentBoundry = 2; //defines when what is a boundry in range from which random number is get, that defines move of meteor towards player

Level level = Level::NONE;
std::map<Level, GameDifficultyStrategy*> diffLevels = {
    { Level::EASY, new EasyDifficulty() },
    { Level::MEDIUM, new MediumDifficulty() },
    { Level::HARD, new HardDifficulty() }
};

Player* player;
TextureController* textureController;
ScoreTexture* sT;
MeteorController* meteorController;
CollisionController* collisionController;

SDL_Renderer* renderer = { nullptr };

void setGameProperties() {

    GameManager gM = GameManager(diffLevels[level]);
    gM.executeGameStrategy();
}

void initGamePlay() {

    delete textureController;
    delete player;
    delete meteorController;
    delete collisionController;

    if(level != Level::NONE) setGameProperties();

    textureController = new TextureController(renderer);
    sT = new ScoreTexture(renderer, "Score: 0", { 50, 50, 70.0f, 50.0f }, { 255, 255, 255, 255 }, TTF_OpenFont("../assets/OpenSans.ttf", 24));
    textureController->addTexture(sT);
    player = new Player(10, textureController);
    meteorController = new MeteorController(meteors_count, player, meteorHeight, meteorWidth);
    collisionController = new CollisionController();

}

void cleanup() {

    delete player;
    delete meteorController;
    delete collisionController;
    delete textureController;
    delete sT;

    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Movement", Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT,0);
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

    initGamePlay();

    while (running) {

        if (level == Level::NONE) {

            textureController->showStartGameScreen(renderer);
            initGamePlay();
        }

        //if user click X button, then game will end already on startgame screen
        if (!running) break;
        player->handleInput(running);
        player->updatePos();

        // Clear screen once
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        meteorController->updatePos(renderer);
        player->updateRocketPos(renderer);
        textureController->renderTexture();

        if (collisionController->verifyMeteorCollisions(renderer, textureController, player, meteorController)) {
            textureController->showEndGameScreen(renderer);
            player->getPressedKeys().clear();
            initGamePlay();
            continue;
        }

        // Draw player
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, player->getPlayer());

        // Present everything
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // Delay to limit FPS (60 FPS)
    }

    cleanup();
    SDL_DestroyWindow(window);
    return 0;
}



