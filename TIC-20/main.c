#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.h"
#include "screen.h"
#include "lua.h"

struct Screen *screen = NULL;

int main(int argc, char *argv[])
{
    const char *luafile = "main.lua";

    // process program arguments
    if (argc > 1) {
        luafile = argv[1];
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF Init: %s\n", TTF_GetError());
        return 1;
    }

    screen = CreateScreen(GREEN, SDL_RENDERER_ACCELERATED);
    if (!screen) {
        fprintf(stderr, "CreateScreen failed.");
        return 1;
    }

    dofile(luafile);

    // Cleanup and exit
    DestroyScreen(screen);
    SDL_Quit();

    return 0;
}
