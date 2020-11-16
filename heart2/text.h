#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// DrawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *r, int x, int y, char *s, TTF_Font *f, SDL_Color c);
