#include <stdio.h>
#include "SDL.h"

int main()
{
    const SDL_VideoInfo *videoInfo = NULL;
    SDL_Surface* screen = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    printf("SDL video initialized, getting video info ...\n");
    videoInfo = SDL_GetVideoInfo();
    if (videoInfo) {
        int w = videoInfo->current_w ;
        int h = videoInfo->current_h ;
        int bits = videoInfo->vfmt->BitsPerPixel ;
        printf("setting video mode to: %d %d %d\n", w, h, bits);
        screen = SDL_SetVideoMode(w, h, bits, SDL_ANYFORMAT);
    }
    if (!screen) {
        printf("SDL_SetVideoMode failed\n");
        return 0;
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_Rect r = {0, 0, 320, 240};
    SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 200, 200, 0));

    SDL_Flip(screen);
    SDL_Delay(2000);

    SDL_Quit();

    return 0;
}
