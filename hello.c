// SDL2 Hello, World!
// This should display a white screen for 5 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2

#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void draw(SDL_Renderer *renderer, int frame)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(renderer, frame, 0, 200 + frame, 200);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                    0, &window, &renderer) != 0) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetWindowTitle(window, "Hello World!");

    for (int i = 0; i < 300; i++) {
        draw(renderer, i);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
