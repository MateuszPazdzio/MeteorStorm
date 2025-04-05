#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Texture.h"
#include <iostream>

class ScoreTexture : public Texture {
public: 
    ScoreTexture(SDL_Renderer* renderer,std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font);

    void render() override;
    void createTexture() override;
    void updateDestroyedMeteorCount();

private:
    SDL_Texture* textureFromSurface;
    int destroyednMeteorCount;
};
