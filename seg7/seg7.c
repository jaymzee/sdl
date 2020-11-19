#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "seg7.h"
#include "color.hpp"

static const SDL_Rect Border = {0, 0, 50, 75};

static const SDL_Color BorderColor = { 16,  16,  16, 255};
static const SDL_Color FillColor   = { 16,  16,  16, 255};
static const SDL_Color LedOffColor = { 48,  48,  48, 255};

// led polygons
static const Sint16 Ax[6] = {18, 37, 40, 36, 19, 16};
static const Sint16 Ay[6] = { 9,  9, 12, 14, 14, 12};

static const Sint16 Bx[6] = {41, 39, 37, 34, 36, 39};
static const Sint16 By[6] = {13, 33, 35, 32, 15, 12};

static const Sint16 Cx[6] = {38, 36, 34, 31, 33, 36};
static const Sint16 Cy[6] = {38, 57, 59, 56, 40, 37};

static const Sint16 Dx[6] = {14, 30, 33, 30, 12, 10};
static const Sint16 Dy[6] = {57, 57, 60, 62, 62, 60};

static const Sint16 Ex[6] = { 8, 10, 12, 14, 12,  9};
static const Sint16 Ey[6] = {58, 39, 37, 40, 56, 59};

static const Sint16 Fx[6] = {11, 13, 15, 18, 15, 12};
static const Sint16 Fy[6] = {34, 14, 12, 15, 32, 35};

static const Sint16 Gx[6] = {17, 33, 37, 33, 15, 12};
static const Sint16 Gy[6] = {33, 33, 36, 39, 39, 36};

static const SDL_Point Pv = {41, 60};   // location of decimal point
static const int Pr       = 3;          // radius of decimal point

// compose each led into an array for x and y
static const Sint16 * const Vx[7] = {Ax, Bx, Cx, Dx, Ex, Fx, Gx};
static const Sint16 * const Vy[7] = {Ay, By, Cy, Dy, Ey, Fy, Gy};

// Draw the seven-segment led onto the renderer surface
int Draw7segment(SDL_Renderer *rend, Uint16 x, Uint16 y, Uint8 b, SDL_Color c)
{
    // return -1 on errors, 0 on success
    int err = -1;
    // precompute these colors
    Uint32 on = uint32(c);
    Uint32 off = uint32(LedOffColor);

    // calculate new viewport
    SDL_Rect vp = Border;
    vp.x = x;
    vp.y = y;

    // fill shape with background color (erase it)
    SDL_Color fill = FillColor;
    if (SDL_SetRenderDrawColor(rend, fill.r, fill.g, fill.b, fill.a))
        return err;
    if (SDL_RenderFillRect(rend, &vp))
        return err;

    // save the current viewport and set the new one
    SDL_Rect vpsave;
    SDL_RenderGetViewport(rend, &vpsave);
    if (SDL_RenderSetViewport(rend, &vp))
        goto fail;

    // draw border
    if (rectangleColor(rend, 0, 0, vp.w, vp.h, uint32(BorderColor)))
       goto fail;

    for (int i = 0; i < 8; i++) {
        Uint32 led = off;
        if ((b >> i) & 1) {
            led = on;
        }
        if (i < 7) {
            if (filledPolygonColor(rend, Vx[i], Vy[i], 6, led))
                goto fail;
        } else {
            if (filledCircleColor(rend, Pv.x, Pv.y, Pr, led))
                goto fail;
        }
    }

    err = 0;
fail:
    SDL_RenderSetViewport(rend, &vpsave);
    return err;
}
