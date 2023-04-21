#include "LuaScriptEngine.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace SignE::Core::Scripting {

    lua_State* LuaScriptEngine::luaState = nullptr;
    bool LuaScriptEngine::running = false;

    void LuaScriptEngine::Init() {
        luaState = luaL_newstate();
        luaState = luaL_newstate();
        luaL_openlibs(luaState);

        running = true;
    }

    void LuaScriptEngine::Shutdown() {
        lua_close(luaState);
    }

    void LuaScriptEngine::RunScript(const std::string& code) {
        luaL_dostring(luaState, code.c_str());
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
