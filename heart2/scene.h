#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
#define RADIUS 450
#define FPS 10
#define POINTS 500
#define FACT_INIT 0.0
#define FACT_DIV 1.0
#define FACT_INCR (1.0 / FACT_DIV)
#define PI 3.14159265358979323846

class Scene {
    double factor_;
    TTF_Font *sans18_;
    void Init_(SDL_Window *window, SDL_Renderer *renderer);
    void Draw_(SDL_Window *window, SDL_Renderer *renderer) const;
public:
    void Loop(SDL_Window *window, SDL_Renderer *renderer);
};
