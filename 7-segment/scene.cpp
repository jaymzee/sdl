// Heart2: times tables displayed graphically

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_framerate.h>
#include <stdio.h>
#include "scene.h"
#include "color.h"
#include "encode7.h"
#include "7segment.h"

const SDL_Color Black   = {  0,   0,   0, 255};
const SDL_Color White   = {255, 255, 255, 255};
const SDL_Color Red     = {255,   0,   0, 255};
const SDL_Color Yellow  = {255, 255,   0, 255};
const SDL_Color Green   = {0,   255,   0, 255};

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
    counter_ = 0;
    SDL_SetWindowTitle(window, "7-segment display");
}

// Draw draws one frame of the scene
void Scene::Draw(SDL_Window *window, SDL_Renderer *renderer) const
{
    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw scene
    for (int h = 0; h < 4; h++) {
        char code = Encode7segment((counter_ >> h * 4) & 0xF, h == 0);
        Draw7segment(renderer, 250 - h*50, 100, code, Green);
    }

    // draw text overlay
}

void Scene::Tick()
{
    // update scene
    counter_++;
}
