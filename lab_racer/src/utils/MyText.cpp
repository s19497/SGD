//
// Created by Jan Pieczul on 19/05/2021.
//


#include <SDL.h>
#include "MyText.h"

void MyText::setText(const char *newText) {
    textTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(sans, newText, color));
}

void MyText::draw() {
    SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
}

MyText::MyText(SDL_Renderer *pRenderer, TTF_Font *pFont, SDL_Color _color, SDL_Rect _rect) {
    renderer = pRenderer;
    sans = pFont;
    color = _color;
    rect = _rect;
}
