#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifdef __cplusplus
extern "C" {
#endif

// DrawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
// return -1 on errors, 0 on success
int DrawText(SDL_Renderer *renderer, Sint16 x, Sint16 y, char *str,
             TTF_Font *font, SDL_Color color);

#ifdef __cplusplus
}
#endif
