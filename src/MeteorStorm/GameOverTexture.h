#pragma once
#include "Texture.h"
#include <map>

class GameOverTexture : public Texture
{
public:
    // Constructor that calls the base class constructor
    GameOverTexture(SDL_Renderer* renderer, std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font);

    // Implementation of the pure virtual function
    void render() override;
    void createTexture() override;

private:
    SDL_Texture* textureFromSurface;
    std::map<std::string, std::string> textureTextDict = {
        {"UpperLine","GAME OVER"},
        {"LowerLine","Press space, to try again"}
    };
};

