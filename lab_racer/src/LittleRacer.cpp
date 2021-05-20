//
// Created by Jan Pieczul on 13/05/2021.
//

#include "LittleRacer.h"
#include "utils/my_math.h"

void LittleRacer::stop() {
    absSpeed = 0;
}

void LittleRacer::displaySpeed() const {
    char speedDisplay[20];
    sprintf(speedDisplay, "%d km/h", (int) (absSpeed * 10));
    speedOMeter->setText(speedDisplay);
}

void LittleRacer::draw() {
    displaySpeed();
    SDL_RenderCopyEx(
            renderer, texture, nullptr, &rect, rotation, nullptr,
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
        rotationSpeed -= rotationAcceleration;
    }
    if (keyboardState[controls.right]) {
        rotationSpeed += rotationAcceleration;
    }

    rotation += rotationSpeed;
    rotation *= 0.9;

    static float deceleration = 0.0001f;
    absSpeed *= 1 - absSpeed * absSpeed * deceleration;

    float speedX = absSpeed * (float) sin(jp_ns::degToRad(rotation));
    float speedY = absSpeed * (float) cos(jp_ns::degToRad(rotation));

    position.x += speedX;
    position.y -= speedY;
    rect.x = (int) position.x;
    rect.y = (int) position.y;
}

LittleRacer::LittleRacer(
        SDL_Renderer *_renderer,
        SDL_Rect _rect,
        LittleRacer::Controls _controls,
        float _acceleration,
        SDL_Texture *_texture, MyText *_speedOMeter
) {
    renderer = _renderer;
    rect = _rect;
    controls = _controls;
    acceleration = _acceleration;
    texture = _texture;
    speedOMeter = _speedOMeter;
}

LittleRacer::~LittleRacer() {
    SDL_DestroyTexture(texture);
}
