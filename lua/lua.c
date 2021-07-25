#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>
#include "text.h"
#include "lua.h"

extern SDL_Renderer *renderer;
extern TTF_Font *default_font;

static int clear(lua_State *L)
{
    unsigned int c = luaL_checknumber(L, 1);

    SDL_SetRenderDrawColor(renderer, c >> 24, (c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);
    SDL_RenderClear(renderer);

    return 0;    // number of results
}

static int pencolor(lua_State *L)
{
    unsigned int c = luaL_checknumber(L, 1);

    SDL_SetRenderDrawColor(renderer, c >> 24, (c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff);

    return 0;   // number of results
}

static int text(lua_State *L)
{
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    const char *s = luaL_checkstring(L, 3);
    unsigned int c = luaL_checknumber(L, 4);

    SDL_Color color = {c >> 24 & 0xff, c >> 16 & 0xff, c >> 8 & 0xff, c & 0xff};

    DrawText(renderer, x, y, s, default_font, color);

    return 0;   // number of results
}

static int line(lua_State *L)
{
    //check and fetch the arguments
    double x1 = luaL_checknumber(L, 1);
    double y1 = luaL_checknumber(L, 2);
    double x2 = luaL_checknumber(L, 3);
    double y2 = luaL_checknumber(L, 4);

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    return 0;   // number of results
}

static int flip(lua_State *L)
{
    SDL_RenderPresent(renderer);

    return 0;   // number of results
}

static int delay(lua_State *L)
{
    unsigned int msec = luaL_checknumber(L, 1);
    SDL_Delay(msec);

    return 0;   // number of results
}

void dofile(const char *filename)
{
    // Create new Lua state and load the lua libraries
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    //Expose the swap function to the lua environment
    lua_pushcfunction(L, clear);
    lua_setglobal(L, "clear");
    lua_pushcfunction(L, pencolor);
    lua_setglobal(L, "pencolor");
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
