#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "ScoreTexture.h"
#include <iostream>
#include "Helpers.h"

int destroyednMeteorCount = 0;

ScoreTexture::ScoreTexture(SDL_Renderer* renderer, SDL_FRect textRect, SDL_Color color, TTF_Font* font)
    : Texture(renderer, textRect, color, font) {
    color = color; // White color
    font = font;
    textRect = textRect;
    createTexture();
}
void ScoreTexture::createTexture() {
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Score: 0", 12, color);
    textureFromSurface = SDL_CreateTextureFromSurface(renderer, surface);
}
void ScoreTexture::render() {
    SDL_RenderTexture(renderer, textureFromSurface, nullptr, &textRect);
}

void ScoreTexture::updateDestroyedMeteorCount() {

    if (textureFromSurface) {
        SDL_DestroyTexture(textureFromSurface);
        textureFromSurface = nullptr;
    }
    destroyednMeteorCount += 1;

    std::string newTextVal = "Score: "+ Helpers::GetString(destroyednMeteorCount);
    SDL_Surface* surface = TTF_RenderText_Solid(font, newTextVal.c_str(), 16, color);
    if (!surface) {
        std::cerr << "Failed to render text surface!";
        return;
    }

    textureFromSurface = SDL_CreateTextureFromSurface(renderer, surface);
    if (!textureFromSurface) {
        std::cerr << "Failed to create text texture! SDL Error: " << SDL_GetError() << std::endl;
    }
    textRect = { 50, 50, (float)surface->w, (float)surface->h };
    SDL_RenderTexture(renderer, textureFromSurface, nullptr, &textRect);

    SDL_DestroySurface(surface);
}