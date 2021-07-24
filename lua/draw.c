#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer *renderer;
extern TTF_Font *default_font;

// drawText renders a string to screen coordinates x and y in the
// font and color given.  It is a convenience method that
//   - creates surface
//   - a texture from that surface
//   - renders the texture
void DrawText(SDL_Renderer *renderer,
              int x, int y, const char *str,
              TTF_Font *font, SDL_Color color)
{
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, str, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Clear(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}


void DrawLine(SDL_Renderer *renderer,
              double x1, double y1,
              double x2, double y2)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 64);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Delay(unsigned int msec)
{
    SDL_Delay(msec);
}

void Flip(void)
{
    SDL_RenderPresent(renderer);
}
