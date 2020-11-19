#include <SDL2/SDL.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300
#define FPS 30

class Scene {
    int counter_;
    void Init(SDL_Window *window, SDL_Renderer *renderer);
    void Draw(SDL_Window *window, SDL_Renderer *renderer) const;
    void Tick();
public:
    void Loop(SDL_Window *window, SDL_Renderer *renderer);
};
