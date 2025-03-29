#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Texture.h"
#include <iostream>

class ScoreTexture : public Texture {
public: 
    // Constructor that calls the base class constructor
    ScoreTexture(SDL_Renderer* renderer,std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font);

    // Implementation of the pure virtual function
    void render() override;
    void createTexture() override;
    void updateDestroyedMeteorCount();

private:
    std::string text;
    SDL_Texture* textureFromSurface;
};