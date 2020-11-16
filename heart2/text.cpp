#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

// DrawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *renderer, Sint16 x, Sint16 y, char *str,
              TTF_Font *font, SDL_Color color)
{
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    if (color.a < 255) {
        SDL_SetTextureAlphaMod(texture, color.a);
    }
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
