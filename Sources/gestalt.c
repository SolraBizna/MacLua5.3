#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <Gestalt.h>

static int f_gestalt(lua_State* L) {
  long response;
  OSErr error;
  size_t len;
  const char* selector = luaL_checklstring(L, 1, &len);
  if(len != 4)
    return luaL_error(L, "Gestalt selectors must be four characters long");
  error = Gestalt(*(const OSType*)selector, &response);
  if(error != noErr) {
    lua_pushnil(L);
    lua_pushinteger(L, error);
    return 2;
  }
  else {
    lua_pushinteger(L, response);
    return 1;
  }
}

int luaopen_gestalt(lua_State* L) {
  lua_pushcfunction(L, f_gestalt);
  return 1;
}
