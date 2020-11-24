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
theta{0.0},
world{
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0, 1.0}
},
vlist{
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 0, 1},
    {0, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 0, 1, 1},
    {1, 1, 1, 1},
    {0, 1, 1, 1}
},
edge{
    {0, 1}, // 0
    {1, 2}, // 1
    {2, 3}, // 2
    {3, 0}, // 3
    {4, 5}, // 4
    {5, 6}, // 5
    {6, 7}, // 6
    {7, 4}, // 7
    {0, 4}, // 8
    {1, 5}, // 9
    {2, 6}, // 10
    {3, 7}  // 11
} {}

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
    SDL_SetWindowTitle(window, "box");
    double theta = 0.1;
    world[0][0] = cos(theta);
    world[0][1] = -sin(theta);
    world[1][0] = sin(theta);
    world[1][1] = cos(theta);
}

// Draw draws one frame of the scene
void Scene::Draw(SDL_Window *window, SDL_Renderer *renderer) const
{
    // clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw scene

    for (int i = 0; i < 12; i++) {
        __m128 v1 = m4x4v_SSE4(world, vlist[edge[i][0]]);
        v1 /= v1[3];
        __m128 v2 = m4x4v_SSE4(world, vlist[edge[i][1]]);
        v2 /= v2[3];
        lineColor(renderer,
            SCREEN_CX + v1[0], SCREEN_CY - v1[1],
            SCREEN_CX + v2[0], SCREEN_CY - v2[1], uint32(Green));
    }

    // draw text overlay
}

void Scene::Tick()
{
    // update scene
    theta+=0.1;
    world[0][0] = 100 * cos(theta);
    world[0][1] = 100 * -sin(theta);
    world[1][0] = 100 * sin(theta);
    world[1][1] = 100 * cos(theta);
}
