/**
 *   @file     fig27.1.c
 *   @date     2019-12-11
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    A bare-bones stand-alone Lua interpreter
 */

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    char buff[256];
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }

    lua_close(L);
    return 0;
}
