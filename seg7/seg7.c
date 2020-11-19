#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "seg7.h"
#include "color.h"

static const SDL_Color White    = {255, 255, 255, 255};
static const SDL_Color DarkGray = { 48,  48,  48, 255};

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

static const Sint16 * const vx[7] = {Ax, Bx, Cx, Dx, Ex, Fx, Gx};
static const Sint16 * const vy[7] = {Ay, By, Cy, Dy, Ey, Fy, Gy};

int Draw7segment(SDL_Renderer *rend, Uint16 x, Uint16 y, Uint8 b, SDL_Color c)
{
    SDL_Rect vpsave, vp = {x, y, 50, 75};
    SDL_RenderGetViewport(rend, &vpsave);
    SDL_RenderSetViewport(rend, &vp);
    Uint32 ledOn = Color(c), ledOff = Color(DarkGray);
    int err = -1;

//    if (rectangleColor(rend, 0, 0, 50, 75, Color(White)) < 0)
//       goto fail;

    for (int i = 0; i < 8; i++) {
        Uint32 led = ledOff;
        if ((b >> i) & 1) {
            led = ledOn;
        }
        if (i < 7) {
            if (filledPolygonColor(rend, vx[i], vy[i], 6, led) < 0)
                goto fail;
        } else {
            if (filledCircleColor(rend, 41, 60, 3, led) < 0)
                goto fail;
        }
    }

    err = 0;
fail:
    SDL_RenderSetViewport(rend, &vpsave);
    return err;
}
