#include <SDL2/SDL.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300
#define SCREEN_CX (SCREEN_WIDTH / 2)
#define SCREEN_CY (SCREEN_HEIGHT / 2)
#define FPS 4

class Scene {
    double theta;
    __m128 world[4];
    __m128 vlist[8];
    int edge[12][2];
    void Init(SDL_Window *window, SDL_Renderer *renderer);
    void Draw(SDL_Window *window, SDL_Renderer *renderer) const;
    void Tick();
public:
    Scene();
    void Loop(SDL_Window *window, SDL_Renderer *renderer);
};
