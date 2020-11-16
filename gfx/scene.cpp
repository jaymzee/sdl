// Heart2: times tables displayed graphically

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_framerate.h>
#include <stdio.h>
#include "scene.h"
#include "color.h"

const SDL_Color White   = {255, 255, 255, 255};
const SDL_Color Red     = {255,   0,   0, 255};
const SDL_Color Yellow  = {255, 255,   0, 255};
const SDL_Color Green   = {0,   255,   0, 255};
const SDL_Color Cyan    = {0,   255, 255, 255};

// Loop is the event loop for the scene
void Scene::Loop(SDL_Window *window, SDL_Renderer *renderer)
{
    FPSmanager fpsmgr;
    SDL_initFramerate(&fpsmgr);
    SDL_setFramerate(&fpsmgr, FPS);
    Init(window, renderer);            // Init scene
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
        Draw(window, renderer);         // Draw scene frame
        SDL_RenderPresent(renderer);
        SDL_framerateDelay(&fpsmgr);
        Tick();                         // Update scene
    }
}

// Init initializes the scene
void Scene::Init(SDL_Window *window, SDL_Renderer *renderer)
{
    factor_ = FACT_INIT;
    points_ = POINTS;
    radius_ = RADIUS;
    SDL_SetWindowTitle(window, "Heart 2 (gfx)");
}

// Draw draws one frame of the scene
void Scene::Draw(SDL_Window *window, SDL_Renderer *renderer) const
{
    double n1, n2, theta, phi;
    double x1, y1, x2, y2;
    char buf[128];

    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // draw scene
    for (int n = 0; n < points_; n++) {
        n1 = n;
        n2 = factor_ * n1;
        theta = 2 * PI * n1 / points_;
        phi = 2 * PI * n2 / points_;
        x1 = radius_ * cos(theta);
        y1 = radius_ * sin(theta);
        x2 = radius_ * cos(phi);
        y2 = radius_ * sin(phi);
        lineColor(renderer,
            (SCREEN_CENTER_X - x1), (SCREEN_CENTER_Y - y1),
            (SCREEN_CENTER_X - x2), (SCREEN_CENTER_Y - y2),
            Color(Green)
        );
    }

    // draw text overlay
    sprintf(buf, "factor: %6.3f", factor_);
    stringColor(renderer, 10, 10, buf, Color(Yellow));
}

void Scene::Tick()
{
    factor_ += FACT_INCR;
}
