//
// Created by Jan Pieczul on 13/05/2021.
//

#ifndef SDLDEMO_LITTLEPLAYER_H
#define SDLDEMO_LITTLEPLAYER_H

#include "SDL.h"

struct LittlePlayer {
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

    SDL_FPoint speed = {};
    SDL_FPoint position = {};

    LittlePlayer(
            SDL_Renderer *_renderer,
            SDL_Rect _rect,
            SDL_Color _color,
            Controls _controls,
            float _acceleration
    );

    void update(const Uint8 *keyboardState);

    void draw();

    void stop();
};


#endif //SDLDEMO_LITTLEPLAYER_H
