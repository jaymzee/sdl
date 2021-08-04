#include <stdio.h>
#include "SDL.h"

int main(int argc, char *args[])
{
    int  i;
    const SDL_VideoInfo *videoInfo;

    SDL_Surface* screen = NULL;
    //Start SDL
    SDL_Init( SDL_INIT_VIDEO );

    printf("video initialized, querying screen size ...\n");
    videoInfo = SDL_GetVideoInfo();

    if (videoInfo) {
        printf("got it\n");
        int systemX = videoInfo->current_w ;
        int systemY = videoInfo->current_h ;
        int systemZ = videoInfo->vfmt->BitsPerPixel ;
        printf("%d %d %d\n", systemX, systemY, systemZ);
    }

    //Set up screen
    screen = SDL_SetVideoMode(1280, 1024, 32, SDL_ANYFORMAT );
    if (!screen)
    {
     	printf("SDL_SetVideoMode failed\n");
     	return 0;
    }
    
    SDL_Rect r = {0,0,320,240};
    SDL_FillRect(screen,&r, SDL_MapRGB(screen->format, 200,200,0) );

    //Update Screen
    //SDL_Flip( screen );
    //Pause
    SDL_Delay( 4000 );

    //Quit SDL
    SDL_Quit();

    return 0;
}
