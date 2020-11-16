#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)
#define RADIUS 450
#define FPS 4
#define POINTS 500
#define FACT_INIT 0.0
#define FACT_DIV 1.0
#define FACT_INCR (1.0 / FACT_DIV)
#define PI 3.14159265358979323846

class Scene {
    double factor_;
    int points_;
    int radius_;
    void Init(SDL_Window *window, SDL_Renderer *renderer);
    void Draw(SDL_Window *window, SDL_Renderer *renderer) const;
    void Tick();
public:
    void Loop(SDL_Window *window, SDL_Renderer *renderer);
};
