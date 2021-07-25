#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"
#include "lua.h"

TTF_Font *default_font = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[])
{
    const char *luafile = "main.lua";

    // process program arguments
    int renderer_flags = SDL_RENDERER_ACCELERATED;
    if (argc > 1) {
        luafile = argv[1];
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        printf("TTF Init: %s\n", TTF_GetError());
        return 1;
    }

    // create a winodw, renderer, and font
    SDL_Window *window = SDL_CreateWindow(
        "lua",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Create Window:%s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (!renderer) {
        fprintf(stderr, "Create Renderer:%s\n", SDL_GetError());
        return 1;
    }
    default_font = TTF_OpenFont("DejaVuSans.ttf", 18);
    if (default_font == NULL) {
        fprintf(stderr, "Open Font: %s\n", TTF_GetError());
        return 1;
    }
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    dofile(luafile);

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
