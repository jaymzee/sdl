// Heart
// times tables displayed graphically
// compile with: -lSDL2 -lSDL2_ttf -lm

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "colors.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
#define RADIUS 450
#define FPS 1000
#define POINTS 500
#define PI 3.14159265358979323846

// fonts are global because it makes it easier to add multiple new fonts
// without breaking the interface. They exist for the entire *lifetime
// of the program and do not change, so they are fine as global variables.

// a Sans Serif 18 point font.
TTF_Font* Sans18 = NULL;

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *renderer,
              char *str, int x, int y,
              TTF_Font *font, SDL_Color color)
{
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// draw draws one frame of a multiplication table for the factor
// given on a circle of connected points.
void DrawFrame(SDL_Renderer *renderer, double factor)
{
    double n1, n2, theta, phi;
    double x1, y1, x2, y2;
    char buf[128];

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int n = 0; n < POINTS; n++) {
        n1 = n;
        n2 = factor * n1;
        theta = 2 * PI * n1 / POINTS;
        phi = 2 * PI * n2 / POINTS;
        x1 = RADIUS * cos(theta);
        y1 = RADIUS * sin(theta);
        x2 = RADIUS * cos(phi);
        y2 = RADIUS * sin(phi);
        SDL_RenderDrawLine(renderer,
            (SCREEN_CENTER_X - x1), (SCREEN_CENTER_Y - y1),
            (SCREEN_CENTER_X - x2), (SCREEN_CENTER_Y - y2)
        );
    }
    sprintf(buf, "factor: %6.3f", factor);
    DrawText(renderer, buf, 10, 10, Sans18, Yellow);
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int renderer_flags = SDL_RENDERER_ACCELERATED;
    double factor = 1.0;

    // process program arguments
    if (argc > 1) {
        if (strcmp(argv[1], "-s") == 0) {
            fprintf(stderr, "Using software rendering\n");
            renderer_flags = SDL_RENDERER_SOFTWARE;
        }
    }

    // Initialize SDL and create a winodw, renderer, and font
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        printf("TTF_Init: %s\n", TTF_GetError());
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
    Sans18 = TTF_OpenFont("DejaVuSans.ttf", 18);
    if (Sans18 == NULL) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return 1;
    }

    // rendering loop
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                // exit rendering loop
                break;
            }
        }
        DrawFrame(renderer, factor);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000.0 / FPS);
        factor += 0.001;
    }

    // Cleanup and exit
    // DestroyFont(Sans18) ??
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
