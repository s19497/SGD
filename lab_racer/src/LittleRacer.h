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
    SDL_Color color = {};
    Controls controls = {};
    float acceleration;
    SDL_Texture *texture;
    double rotation = 0;
    double rotationAcceleration = 3;
    MyText *speedOMeter;

    float absSpeed = 0;
    SDL_FPoint speed = {};
    SDL_FPoint position = {};

    LittleRacer(
            SDL_Renderer *_renderer, SDL_Rect _rect, SDL_Color _color, LittleRacer::Controls _controls,
            float _acceleration, SDL_Texture *_texture, MyText *_speedOMeter
    );

    ~LittleRacer();

    void update(const Uint8 *keyboardState);

    void draw();

    void stop();

    SDL_Point intPosition();
};


#endif //SDLDEMO_LITTLEPLAYER_H
