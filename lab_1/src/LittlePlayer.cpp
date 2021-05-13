//
// Created by Jan Pieczul on 13/05/2021.
//

#include "LittlePlayer.h"

void LittlePlayer::stop() {
    speed = {0, 0};
}

void LittlePlayer::draw() {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void LittlePlayer::update(const Uint8 *keyboardState) {
    if (keyboardState[controls.up]) {
        speed.y -= acceleration;
    }
    if (keyboardState[controls.down]) {
        speed.y += acceleration;
    }
    if (keyboardState[controls.left]) {
        speed.x -= acceleration;
    }
    if (keyboardState[controls.right]) {
        speed.x += acceleration;
    }

    position.x += speed.x;
    position.y += speed.y;
    rect.x = (int) position.x;
    rect.y = (int) position.y;
}

LittlePlayer::LittlePlayer(
        SDL_Renderer *_renderer,
        SDL_Rect _rect,
        SDL_Color _color,
        LittlePlayer::Controls _controls,
        float _acceleration
) {
    renderer = _renderer;
    rect = _rect;
    color = _color;
    controls = _controls;
    acceleration = _acceleration;
}
