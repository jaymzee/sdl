// Heart2: times tables displayed graphically

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_framerate.h>
#include <stdio.h>
#include <math.h>
#include "scene.h"
#include "color.hpp"
#include "matrix4x4s.h"
#include "print_sse.h"

const SDL_Color Black   = {  0,   0,   0, 255};
const SDL_Color White   = {255, 255, 255, 255};
const SDL_Color Red     = {255,   0,   0, 255};
const SDL_Color Yellow  = {255, 255,   0, 255};
const SDL_Color Green   = {0,   255,   0, 255};

Scene::Scene() :
matrix{
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
},
vector{50.0, 0.0, 0.0, 1.0}
{}

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
    SDL_SetWindowTitle(window, "box");
    double theta = 0.1;
    matrix[0][0] = cos(theta);
    matrix[0][1] = -sin(theta);
    matrix[1][0] = sin(theta);
    matrix[1][1] = cos(theta);
}

// Draw draws one frame of the scene
void Scene::Draw(SDL_Window *window, SDL_Renderer *renderer) const
{
    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw scene
    __m128 v = vector;
    lineColor(renderer,
        SCREEN_CX, SCREEN_CY,
        SCREEN_CX + v[0], SCREEN_CY - v[1], uint32(Green));

    // draw text overlay
    char buf[256];
    sprint_4s(buf, vector);
    printf("%s\n", buf);
    stringColor(renderer, 10, 10, buf, uint32(Yellow));
}

void Scene::Tick()
{
    // update scene
    counter_++;
    vector = m4x4v_SSE4(matrix, vector);
}
