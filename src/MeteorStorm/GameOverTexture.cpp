#include "GameOverTexture.h"
#include <map>
#include "Helpers.h"

GameOverTexture::GameOverTexture(SDL_Renderer* renderer,std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font)
    : Texture(renderer, text, textRect, color, font) {
    this->text = text;
    this->color = color;
    this->font = font;
    this->textRect = textRect;
    createTexture();
}
void GameOverTexture::createTexture() {
    int charsCount = 0;
    Helpers::countCharsInString(textureTextDict[text].c_str(), charsCount);
    SDL_Surface* surface = TTF_RenderText_Solid(font, textureTextDict[text].c_str(), charsCount, color);
    textureFromSurface = SDL_CreateTextureFromSurface(renderer, surface);
}
void GameOverTexture::render() {
    SDL_RenderTexture(renderer, textureFromSurface, nullptr, &textRect);
}