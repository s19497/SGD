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
//    sprintf(speedDisplay, "%d km/h", (int) (10 * jp_ns::pythagoras(speed.x, speed.y)));
    sprintf(speedDisplay, "%d km/h", (int) (frontSpeed()));
    speedOMeter->setText(speedDisplay);
}

void LittleRacer::draw() {
    displaySpeed();
    SDL_RenderCopyEx(
            renderer, texture, nullptr, &rect, rotation, nullptr,
            SDL_RendererFlip::SDL_FLIP_NONE
    );

    if (!showVectors) {
        return;
    }

    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_RenderDrawLine(renderer, centerX, centerY, centerX + speed.x * 50, centerY);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
    SDL_RenderDrawLine(renderer, centerX, centerY, centerX, centerY - speed.y * 50);
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
    rotationSpeed *= 0.9;
    if (rotation < 0) {
        rotation += 360;
    } else if (rotation > 360) {
        rotation -= 360;
    }

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

float LittleRacer::frontSpeed() const {
    float tg = speed.x != 0 ? atan(speed.y / speed.x) : 0;
    float d = jp_ns::pythagoras(speed.x, speed.y);

    float F = d * cos(jp_ns::degToRad(90 - rotation) - tg);
    float Fy = F * sin(jp_ns::degToRad(90 - rotation));
    float Fx = F * cos(jp_ns::degToRad(90 - rotation));

    float S = d * sin(jp_ns::degToRad(90 - rotation) - tg);
    float Sy = S * sin(jp_ns::degToRad(rotation));
    float Sx = S * cos(jp_ns::degToRad(rotation));

    float fd = 100;

    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;

    SDL_SetRenderDrawColor(renderer, 0, 100, 255, 100);
    SDL_RenderDrawLine(renderer, centerX, centerY, centerX + Fx * fd, centerY - Fy * fd);

    SDL_SetRenderDrawColor(renderer, 100, 0, 255, 100);
    SDL_RenderDrawLine(renderer, centerX, centerY, centerX + Sx * fd, centerY + Sy * fd);

    return F;
}

