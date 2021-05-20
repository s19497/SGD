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
    };

    SDL_Renderer *renderer;
    SDL_Rect rect = {};
    Controls controls = {};
    float acceleration;
    SDL_Texture *texture;
    double rotation = 0;
    double rotationSpeed = 0;
    double rotationAcceleration = .5;
    MyText *speedOMeter;

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
    void displaySpeed() const;
};


#endif //SDLDEMO_LITTLEPLAYER_H
