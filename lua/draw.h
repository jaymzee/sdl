#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Clear(SDL_Renderer *renderer);
void Delay(unsigned int msec);
void DrawLine(SDL_Renderer *renderer,
              double x1, double y1,
              double x2, double y2);
// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *renderer,
              int x, int y, const char *str,
              TTF_Font *font, SDL_Color color);
void Flip(void);
