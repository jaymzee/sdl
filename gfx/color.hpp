#include <SDL2/SDL.h>

inline Uint32 Color(SDL_Color c)
{
    return c.a << 24 | c.b << 16 | c.g << 8 | c.r;
}

inline Uint32 Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)
{
    return a << 24 | b << 16 | g << 8 | r;
}
