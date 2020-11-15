#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "scene.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int renderer_flags = SDL_RENDERER_ACCELERATED;

    // process program arguments
    if (argc > 1) {
        if (strcmp(argv[1], "-s") == 0) {
            fprintf(stderr, "using software rendering\n");
            renderer_flags = SDL_RENDERER_SOFTWARE;
        }
    }

    // Initialize SDL and create a winodw, renderer, and font
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        printf("TTF Init: %s\n", TTF_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
        "initializing SDL",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Create Window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (!renderer) {
        fprintf(stderr, "Create Renderer: %s\n", SDL_GetError());
        return 1;
    }

    try {
        Scene scene(window, renderer);
        scene.Loop();
    } catch (const char *err) {
        fprintf(stderr, "scene loop: %s\n", err);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
