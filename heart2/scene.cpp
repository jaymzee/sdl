// Heart
// times tables displayed graphically

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"
#include "colors.h"
#include "text.h"

// Init initializes the scene
Scene::Scene(SDL_Window *window, SDL_Renderer *renderer)
: window{window}, renderer{renderer}
{
    factor = FACT_INIT;
    sans18 = TTF_OpenFont("DejaVuSans.ttf", 18);
    if (sans18 == NULL) {
        throw TTF_GetError();
    }
    SDL_SetWindowTitle(window, "Heart2");
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

// Draw draws one frame of the scene
void Scene::Draw()
{
    double n1, n2, theta, phi;
    double x1, y1, x2, y2;
    char buf[128];

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
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

    // there is a bug where a single pixel is appearing on the bottom right
    // of the text drawn. The two lines below work around it by making the
    // last drawn color the background and alpha 0.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawPoint(renderer, 0, 0);

    // draw text overlay
    sprintf(buf, "factor: %6.3f", factor);
    DrawText(renderer, 10, 10, buf, sans18, Yellow);
}

// Loop is the event loop for the scene
void Scene::Loop() {
    for (bool running = true; running; ) {
        // respond to events
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                printf("Quit\n");
                running = false;
                break;
            }
        }

        // draw a single frame of the scene
        Draw();
        SDL_RenderPresent(renderer);
        SDL_Delay(1000.0 / FPS);

        // update scene
        factor += FACT_INCR;
    }
}
