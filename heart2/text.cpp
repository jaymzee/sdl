#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *r, char *s, int x, int y, TTF_Font *f, SDL_Color c)
{
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(f, s, c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    if (c.a < 255) {
        SDL_SetTextureAlphaMod(texture, c.a);
    }
    SDL_RenderCopy(r, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
