// compile with: -lSDL2 -lSDL2_ttf -lm

#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int color = 0;
void DrawFrame(SDL_Renderer *renderer)
{
    color = 255 - color;
    SDL_SetRenderDrawColor(renderer, 0, color, 0, 255);
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_HEIGHT; x++) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

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
    window = SDL_CreateWindow(
        "Heart",
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

    for (int i = 0; i < 10; i++) {
        SDL_Event e;

        /*
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                // exit rendering loop
                break;
            }
        }
        */
        DrawFrame(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(2000.0);

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
