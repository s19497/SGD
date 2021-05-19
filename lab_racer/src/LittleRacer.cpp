//
// Created by Jan Pieczul on 13/05/2021.
//

#include "LittleRacer.h"
#include "utils/my_math.h"

void LittleRacer::stop() {
    absSpeed = 0;
}

void LittleRacer::draw() {
    char speedDisplay[20];
    sprintf(speedDisplay, "%.2f", absSpeed);
    speedOMeter->setText(speedDisplay);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopyEx(
            renderer,texture,nullptr,&rect,rotation,nullptr,
            SDL_RendererFlip::SDL_FLIP_NONE
    );
}

void LittleRacer::update(const Uint8 *keyboardState) {
    if (keyboardState[controls.up]) {
        absSpeed += acceleration;
    }
    if (keyboardState[controls.down]) {
        absSpeed -= acceleration;
    }
    if (keyboardState[controls.left]) {
        rotation -= rotationAcceleration;
    }
    if (keyboardState[controls.right]) {
        rotation += rotationAcceleration;
    }

    speed.x = absSpeed * sin(jp_ns::degToRad(rotation));
    speed.y = absSpeed * cos(jp_ns::degToRad(rotation));

    position.x += speed.x;
    position.y -= speed.y;
    rect.x = (int) position.x;
    rect.y = (int) position.y;
}

LittleRacer::LittleRacer(
        SDL_Renderer *_renderer,
        SDL_Rect _rect,
        SDL_Color _color,
        LittleRacer::Controls _controls,
        float _acceleration,
        SDL_Texture *_texture,
        MyText *_speedOMeter
) {
    renderer = _renderer;
    rect = _rect;
    color = _color;
    controls = _controls;
    acceleration = _acceleration;
    texture = _texture;
    speedOMeter = _speedOMeter;
}

LittleRacer::~LittleRacer() {
    SDL_DestroyTexture(texture);
}

SDL_Point LittleRacer::intPosition() {
    return {(int) position.x, (int) position.y};
}
