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

    void LuaScriptEngine::Init() {
        luaState = luaL_newstate();
        luaState = luaL_newstate();
        luaL_openlibs(luaState);

        LuaScriptGlue::RegisterComponents(luaState);
        LuaScriptGlue::RegisterFunctions(luaState);

        running = true;
    }

    void LuaScriptEngine::Shutdown() {
        lua_close(luaState);
    }

    void LuaScriptEngine::RunScript(const Entity& entity, const std::string& code) {
        int result = luaL_dostring(luaState, code.c_str());
        if (result != LUA_OK) {
            Log::LogError(lua_tostring(luaState, -1));
        }
    }

    void LuaScriptEngine::RunInitFunction(const Entity& entity, const std::string& code) {
        if (luaL_dostring(luaState, code.c_str()) != LUA_OK) {
            Log::LogError(lua_tostring(luaState, -1)); 
            return;
        }

        lua_getglobal(luaState, "onInit");
        if (lua_isfunction(luaState, -1)) {
            CreateEntity(luaState, entity);
            if (lua_pcall(luaState, 1, 0, 0) != LUA_OK) {
                Log::LogError(lua_tostring(luaState, -1));
            }
        }
        else {
            Log::LogInfo("init function not found");
        }
    }

    void LuaScriptEngine::RunUpdateFunction(const Entity& entity, const std::string& code) {
        if (luaL_dostring(luaState, code.c_str()) != LUA_OK) {
            Log::LogError(lua_tostring(luaState, -1)); 
            return;
        }

        lua_getglobal(luaState, "onUpdate");
        if (lua_isfunction(luaState, -1)) {
            CreateEntity(luaState, entity);

            lua_pushnumber(luaState, Application::Application::GetDeltaTime());

            if (lua_pcall(luaState, 2, 0, 0) != LUA_OK) {
                Log::LogError(lua_tostring(luaState, -1));
            }
        }
        else {
            Log::LogInfo("update function not found");
        }
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
