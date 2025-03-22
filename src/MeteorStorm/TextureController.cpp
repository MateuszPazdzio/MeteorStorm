#include "TextureController.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Helpers.h"
#include <iostream>
#include "Texture.h"
#include "ScoreTexture.h"
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
void TextureController::renderTexture() {
    for (auto it = textures.begin();it != textures.end();++it) {
        if (*it) (*it)->render();
    }
}