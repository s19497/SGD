/**
 * This is the simple hello world for SDL2.
 * 
 * You need C++14 to compile this.
 */


#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <iostream>
#include <thread>
#include <LittlePlayer.h>

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

    errcheck(init(window, renderer, WIDTH, HEIGHT));

    std::chrono::milliseconds dt(15);
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

    LittlePlayer player_1{
            renderer,
            {-20, -20, 20, 20},
            {255, 128, 128, 255},
            {SDL_SCANCODE_W, SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A},
            0.5
    };

    LittlePlayer player_2{
            renderer,
            {-20, -20, 20, 20},
            {100, 128, 200, 255},
            {SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT},
            1
    };

    const Uint8 *keyboardState;

    for (bool game_active = true; game_active;) {
        clearRenderer(renderer);
        SDL_Event event;

        while (SDL_PollEvent(&event)) { // check if there are some events
            if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_Q) {
                game_active = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_FPoint newPosition = {(float) event.button.x, (float) event.button.y};
                if (event.button.button == SDL_BUTTON_LEFT) {
                    player_1.position = newPosition;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    player_2.position = newPosition;
                }
            }
            keyboardState = SDL_GetKeyboardState(nullptr);
        }

        if (keyboardState[SDL_SCANCODE_SPACE]) {
            player_1.stop();
        }

        player_1.update(keyboardState);
        player_2.update(keyboardState);

        player_1.draw();
        player_2.draw();

        SDL_RenderPresent(renderer); // draw frame to screen

        std::this_thread::sleep_until(current_time = current_time + dt);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
