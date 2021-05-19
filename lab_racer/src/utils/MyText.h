//
// Created by Jan Pieczul on 19/05/2021.
//

#ifndef LAB_RACER_MYTEXT_H
#define LAB_RACER_MYTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class MyText {
    SDL_Texture *textTexture{};

public:
    SDL_Renderer *renderer;
    TTF_Font *sans;
    SDL_Color color{};
    SDL_Rect rect = {100, 100, 100, 100};

    void setText(const char *newText);

    void draw();

    MyText(SDL_Renderer *pRenderer, TTF_Font *pFont, SDL_Color _color, SDL_Rect _rect);
};


#endif //LAB_RACER_MYTEXT_H
