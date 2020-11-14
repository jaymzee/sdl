#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *r, char *s, int x, int y, TTF_Font *f, SDL_Color c);
