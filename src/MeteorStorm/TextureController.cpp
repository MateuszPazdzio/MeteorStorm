#include "TextureController.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers.h"
#include <iostream>
#include "Texture.h"
#include "ScoreTexture.h"
#include "GameOverTexture.h"
#include <vector>


TextureController::TextureController(SDL_Renderer* renderer) : renderer(renderer) {

};
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
    SDL_Event event;

    clear();
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    GameOverTexture* gameOverTextureUperLine = new GameOverTexture(renderer, "UpperLine", { 280, 200, 250, 40.0f }, {255, 0, 0, 255}, TTF_OpenFont("../assets/OpenSans.ttf", 25.0f));
    GameOverTexture* gameOverTextureLowerLine = new GameOverTexture(renderer, "LowerLine", {150, 300, 500, 40.0f }, { 255, 255, 255, 255 }, TTF_OpenFont("../assets/OpenSans.ttf", 25.0f));

    addTexture(gameOverTextureUperLine);
    addTexture(gameOverTextureLowerLine);

    bool tryAgain = false;

    while (!tryAgain) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                tryAgain = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    tryAgain = false;
                }
                if (event.key.scancode == SDL_SCANCODE_KP_ENTER) {
                    tryAgain = true;
                }
            }
        }

        // Render Game Over Screen
        SDL_RenderClear(renderer);
        renderTexture();
        SDL_RenderPresent(renderer);
    }
}