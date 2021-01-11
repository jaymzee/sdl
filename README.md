to compile SDL2 programs under MSYS2 mingw64:

    gcc -Dmain=SDL_main myprg.c -lmingw32 -lSDL2main -lSDL2 -lSDL_ttf -lSDL_gfx
