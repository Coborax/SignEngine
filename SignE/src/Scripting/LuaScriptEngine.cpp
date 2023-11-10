#include "LuaScriptEngine.h"
#include "Log.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "LuaScriptGlue.h"
#include "Scene/Entity.h"
#include "Application/Application.h"

namespace SignE::Core::Scripting {

    lua_State* LuaScriptEngine::luaState = nullptr;
    bool LuaScriptEngine::running = false;

    void LuaScriptEngine::Shutdown() {
        lua_close(luaState);
    }

    void LuaScriptEngine::CreateEntity(lua_State* L, const Entity& entity) {
        Entity* entityPtr = (Entity*)lua_newuserdata(L, sizeof(Entity));
        *entityPtr = entity;

        luaL_getmetatable(L, "Entity");
        lua_setmetatable(L, -2);
    }

    bool LuaScriptEngine::IsPaused() {
        return !running;
    }

    void LuaScriptEngine::Pause() {
        running = false;
    }

    void LuaScriptEngine::Resume() {
        running = true;
    }

}
