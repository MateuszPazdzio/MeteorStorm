#include "StartGameTexture.h"
#include "Helpers.h"

StartGameTexture::StartGameTexture(SDL_Renderer* renderer, std::string text, SDL_FRect textRect, SDL_Color color, TTF_Font* font)
    : Texture(renderer, text, textRect, color, font) {

    this->text = text;
    this->textRect = textRect;
    this->color = color;
    this->font = font;
    createTexture();
}

void StartGameTexture::createTexture() {

    int charsCount = 0;
    Helpers::countCharsInString(textureTextDict[text].c_str(), charsCount);
    SDL_Surface* surface = TTF_RenderText_Solid(font, textureTextDict[text].c_str(), charsCount, color);
    textureFromSurface = SDL_CreateTextureFromSurface(renderer, surface);
}

void StartGameTexture::render() {
    SDL_RenderTexture(renderer, textureFromSurface, nullptr, &textRect);
}