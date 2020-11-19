#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline Uint32 uint32(SDL_Color c)
{
    return c.a << 24 | c.b << 16 | c.g << 8 | c.r;
}

#ifdef __cplusplus
}
#endif
