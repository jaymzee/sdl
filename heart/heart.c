// SDL2 Heart
// times tables displayed graphically
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2

#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define SCREEN_CENTERX (SCREEN_WIDTH / 2)
#define SCREEN_CENTERY (SCREEN_HEIGHT / 2)
#define RADIUS 450
#define FPS 500
#define POINTS 500

void draw(SDL_Renderer *renderer, double factor)
{
    double n1, n2, theta, phi;
    double x1, y1, x2, y2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int n = 0; n < POINTS; n++) {
        n1 = n;
        n2 = factor * n1;
        theta = 2 * M_PI * n1 / POINTS;
        phi = 2 * M_PI * n2 / POINTS;
        x1 = RADIUS * cos(theta);
        y1 = RADIUS * sin(theta);
        x2 = RADIUS * cos(phi);
        y2 = RADIUS * sin(phi);
        SDL_RenderDrawLine(
            renderer,
            (SCREEN_CENTERX - x1), (SCREEN_CENTERY - y1),
            (SCREEN_CENTERX - x2), (SCREEN_CENTERY - y2)
        );
    }
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int renderer_flags = SDL_RENDERER_ACCELERATED;
    double factor = 1.0;

    if (argc > 1) {
        if (strcmp(argv[1], "-s") == 0) {
            fprintf(stderr, "Using software rendering");
            renderer_flags = SDL_RENDERER_SOFTWARE;
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
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

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        draw(renderer, factor);
        SDL_RenderPresent(renderer);
        //SDL_Delay(1000.0 / FPS);
        factor += 0.001;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
