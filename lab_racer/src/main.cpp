/**
 * This is the simple hello world for SDL2.
 * 
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <thread>

#include "LittleRacer.h"
#include "utils/MyText.h"

#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                            \
      std::cout << SDL_GetError() << std::endl;         \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

int init(SDL_Window *&window, SDL_Renderer *&renderer, int width, int height) {
    errcheck(SDL_Init(SDL_INIT_VIDEO))
    TTF_Init();
//    errcheck(IMG_Init(IMG_INIT_PNG));

    window = SDL_CreateWindow(
            "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
    );
    errcheck(window == nullptr)

    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED
    ); // SDL_RENDERER_PRESENTVSYNC
    errcheck(renderer == nullptr)

    SDL_SetWindowResizable(window, static_cast<SDL_bool>(true));

    return 0;
}

void clearRenderer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

int main(int, char **) {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    errcheck(init(window, renderer, WIDTH, HEIGHT))
    MyText txt{
            renderer,
            TTF_OpenFont("data/open-sans/OpenSans-Regular.ttf", 80),
            {255, 255, 255, 255},
            {100, 100, 100, 100}
    };

    MyText pointsText{
        renderer,
        TTF_OpenFont("data/open-sans/OpenSans-Regular.ttf", 80),
        {255, 255, 255, 255},
        {100, 200, 100, 100}
    };

    LittleRacer player_1(
            renderer,
            {-20, -20, 40, 80},
            {
                    SDL_SCANCODE_W,
                    SDL_SCANCODE_D,
                    SDL_SCANCODE_S,
                    SDL_SCANCODE_A,
                    SDL_SCANCODE_SPACE
            },
            0.07,
            IMG_LoadTexture(&*renderer, "data/little_racer.png"),
            &txt
    );

    const Uint8 *keyboardState;

    std::chrono::milliseconds dt(15);
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

    for (bool game_active = true; game_active;) {
        clearRenderer(renderer);
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_Q) {
                game_active = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_FPoint newPosition = {(float) event.button.x, (float) event.button.y};
                if (event.button.button == SDL_BUTTON_LEFT) {
                    player_1.position = newPosition;
                }
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_V) {
                    player_1.showVectors = !player_1.showVectors;
                }
            }
            keyboardState = SDL_GetKeyboardState(nullptr);
        }

        if (keyboardState[SDL_SCANCODE_T]) {
            player_1.stop();
        }

        player_1.update(keyboardState);
        player_1.draw();

        txt.draw();
        pointsText.setText(std::to_string(player_1.driftPoints).data());
        pointsText.draw();
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_until(current_time = current_time + dt);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
