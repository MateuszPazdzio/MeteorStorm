#include "TextureController.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers.h"
#include <iostream>
#include "Texture.h"
#include "ScoreTexture.h"
#include "GameOverTexture.h"
#include "MeteorStorm.h"
#include <vector>


TextureController::TextureController(SDL_Renderer* renderer) : renderer(renderer) {};

void TextureController::addTexture(Texture* texture) {
    textures.push_back(texture);
}
void TextureController::updateCounterTexture() {

    if (!textures.empty() && textures[0]) {
        ScoreTexture* sT = dynamic_cast<ScoreTexture*>(textures[0]);
        sT->updateDestroyedMeteorCount();
    }
}

void TextureController::clear() {

    for (auto* texture : textures) {
        delete texture;
    }
    textures.clear();
}

void TextureController::renderTexture() {
    for (auto it = textures.begin();it != textures.end();++it) {
        if (*it) (*it)->render();
    }
}

void TextureController::showEndGameScreen(SDL_Renderer* renderer) {

    //remove all textures
    clear();

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    GameOverTexture* gameOverTextureUperLine = new GameOverTexture(renderer, "UpperLine", { 280, 200, 250, 40.0f }, {255, 0, 0, 255}, TTF_OpenFont("../assets/OpenSans.ttf", 25.0f));
    GameOverTexture* gameOverTextureLowerLine = new GameOverTexture(renderer, "LowerLine", {150, 300, 500, 40.0f }, { 255, 255, 255, 255 }, TTF_OpenFont("../assets/OpenSans.ttf", 25.0f));

    addTexture(gameOverTextureUperLine);
    addTexture(gameOverTextureLowerLine);

    bool showEndGameScr = true;

    //wait until user hits ESCAPE or LEFT ENTER
    while (showEndGameScr) {


        // Render Game Over Screen
        SDL_RenderClear(renderer);
        renderTexture();
        SDL_RenderPresent(renderer);

        showEndGameScr = handleEndGameInput();
    }
}

bool TextureController::handleEndGameInput() {

    SDL_Event event;
    bool showEndGameScr = true;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT || isEscapeOrEnterBtnPressedDown(event)) {
            showEndGameScr = false;
            running = (event.key.scancode == SDL_SCANCODE_SPACE);
        }
    }
    return showEndGameScr;
}
//actually if a key is unpressed
bool TextureController::isEscapeOrEnterBtnPressedDown(const SDL_Event& event) {
    return (event.type == SDL_EVENT_KEY_UP && (event.key.scancode == SDL_SCANCODE_ESCAPE || (event.key.scancode == SDL_SCANCODE_SPACE)));
}