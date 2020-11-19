#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

// DrawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
// return -1 on errors, 0 on success
int DrawText(SDL_Renderer *renderer, Sint16 x, Sint16 y, char *str,
             TTF_Font *font, SDL_Color color)
{
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect = {x, y, 0, 0};
    int err = -1;

    surface = TTF_RenderText_Blended(font, str, color);
    if (surface == NULL)
        goto surfaceD;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
        goto textureD;
    if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h))
        goto fail;
    if (color.a < 255) {
        if (SDL_SetTextureAlphaMod(texture, color.a))
            goto fail;
    }
    if (SDL_RenderCopy(renderer, texture, NULL, &rect))
        goto fail;

    err = 0;
fail:
    SDL_DestroyTexture(texture);
textureD:
    SDL_FreeSurface(surface);
surfaceD:
    return err;
}
