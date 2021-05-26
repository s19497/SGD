//
// Created by Jan Pieczul on 13/05/2021.
//

#ifndef SDLDEMO_LITTLEPLAYER_H
#define SDLDEMO_LITTLEPLAYER_H

#include "SDL.h"
#include <iostream>
#include <utils/MyText.h>

struct LittleRacer {
    struct Controls {
        SDL_Scancode up;
        SDL_Scancode right;
        SDL_Scancode down;
        SDL_Scancode left;
        SDL_Scancode handbrake;
    };

    SDL_Renderer *renderer;
    SDL_Rect rect = {};
    Controls controls = {};
    float acceleration;
    SDL_Texture *texture;
    double rotation = 0;
    double rotationSpeed = 0;
    double rotationAcceleration = .2;
    MyText *speedOMeter;
    bool showVectors;

    float normalFriction = 0.9;
    float handbrakeFriction = 0.01;
    float driftFriction = 0.01;
    float driftThreshold = 0.35;
    bool isDrifting = false;
    bool handbrake = false;

    float frontSpeed = 0;
    int driftPoints = 0;

    SDL_FPoint speed{};
    SDL_FPoint position{};

    LittleRacer(
            SDL_Renderer *_renderer,
            SDL_Rect _rect,
            LittleRacer::Controls _controls,
            float _acceleration,
            SDL_Texture *_texture,
            MyText *_speedOMeter
    );

    ~LittleRacer();

    void update(const Uint8 *keyboardState);

    void draw();

    void stop();

private:
    void displaySpeed();

    void applyFriction(const Uint8 *keyboardState);

    void applyRotation();
};


#endif //SDLDEMO_LITTLEPLAYER_H
