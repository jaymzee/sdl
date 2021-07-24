#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "draw.h"
#include "lua.h"

//const SDL_Color Red = {255, 0, 0, 255};
//const SDL_Color Green = {0, 255, 0, 255};
//const SDL_Color Blue = {0, 0, 255, 255};
const SDL_Color Yellow = {255, 255, 0, 255};
//const SDL_Color Cyan = {0, 255, 255, 255};
//const SDL_Color Magenta = {255, 0, 255, 255};
//const SDL_Color White = {255, 255, 255, 255};
//const SDL_Color LightGray = {170, 170, 170, 255};
//const SDL_Color DarkGray = {85, 85, 85, 255};

extern SDL_Renderer *renderer;
extern TTF_Font *default_font;

static int text(lua_State *L)
{
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    const char *s = luaL_checkstring(L, 3);

    DrawText(renderer, x, y, s, default_font, Yellow);

    return 0;   // number of results
}

static int line(lua_State *L)
{
    //check and fetch the arguments
    double x1 = luaL_checknumber(L, 1);
    double y1 = luaL_checknumber(L, 2);
    double x2 = luaL_checknumber(L, 3);
    double y2 = luaL_checknumber(L, 4);

    DrawLine(renderer, x1, y1, x2, y2);

    return 0;   // number of results
}

static int flip(lua_State *L)
{
    Flip();

    return 0;   // number of results
}

static int delay(lua_State *L)
{
    double msec = luaL_checknumber(L, 1);
    Delay(msec);

    return 0;   // number of results
}

void dofile(const char *filename)
{
    // Create new Lua state and load the lua libraries
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    //Expose the swap function to the lua environment
    lua_pushcfunction(L, text);
    lua_setglobal(L, "text");
    lua_pushcfunction(L, line);
    lua_setglobal(L, "line");
    lua_pushcfunction(L, flip);
    lua_setglobal(L, "flip");
    lua_pushcfunction(L, delay);
    lua_setglobal(L, "delay");

    // Tell Lua to execute a lua file
    luaL_dofile(L, filename);
}
