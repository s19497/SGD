//
// Created by Jan Pieczul on 13/05/2021.
//

#include "LittleRacer.h"
#include "utils/my_math.h"

void LittleRacer::stop() {
    speed.x = 0;
    speed.y = 0;
}

void LittleRacer::displaySpeed() const {
    static char speedDisplay[20];
    sprintf(speedDisplay, "%d km/h", (int) (10 * jp_ns::pythagoras(speed.x, speed.y)));
    speedOMeter->setText(speedDisplay);
}

void LittleRacer::draw() {
    displaySpeed();
    SDL_RenderCopyEx(
            renderer, texture, nullptr, &rect, rotation, nullptr,
            SDL_RendererFlip::SDL_FLIP_NONE
    );
}

float airBrake(float speed) {
    static float deceleration = 0.001f;
    speed *= 1 - speed * speed * deceleration;
    return speed;
}

void LittleRacer::update(const Uint8 *keyboardState) {
    if (keyboardState[controls.up]) {
        speed.x += acceleration * (float) sin(jp_ns::degToRad(rotation));
        speed.y += acceleration * (float) cos(jp_ns::degToRad(rotation));
    }
    if (keyboardState[controls.down]) {
        speed.x -= acceleration * (float) sin(jp_ns::degToRad(rotation));
        speed.y -= acceleration * (float) cos(jp_ns::degToRad(rotation));
    }
    if (keyboardState[controls.left]) {
        rotationSpeed -= rotationAcceleration;
    }
    if (keyboardState[controls.right]) {
        rotationSpeed += rotationAcceleration;
    }

    rotation += rotationSpeed;
    rotation *= 0.9;

    position.x += airBrake(speed.x);
    position.y -= airBrake(speed.y);
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
