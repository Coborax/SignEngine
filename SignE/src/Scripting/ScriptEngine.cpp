//
// Created by mikke on 13-08-2023.
//

#include "Application/Application.h"
#include "Scene/Entity.h"
#include "LuaScriptGlue.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua.h"
#include "Log.h"
#include "LuaScriptEngine.h"
#include "ScriptEngine.h"
void SignE::Core::Scripting::ScriptEngine::Init() {
    LuaScriptEngine::luaState = luaL_newstate();
    LuaScriptEngine::luaState = luaL_newstate();
    luaL_openlibs(LuaScriptEngine::luaState);

    LuaScriptGlue::RegisterComponents(LuaScriptEngine::luaState);
    LuaScriptGlue::RegisterFunctions(LuaScriptEngine::luaState);

    LuaScriptEngine::running = true;
}
void SignE::Core::Scripting::ScriptEngine::RunScript(const Entity& entity, const std::string& code) {
    int result = luaL_dostring(LuaScriptEngine::luaState, code.c_str());
    if (result != LUA_OK) {
        Log::LogError(lua_tostring(LuaScriptEngine::luaState, -1));
    }
}
void SignE::Core::Scripting::ScriptEngine::RunInitFunction(const Entity& entity, const std::string& code) {
    if (luaL_dostring(LuaScriptEngine::luaState, code.c_str()) != LUA_OK) {
        Log::LogError(lua_tostring(LuaScriptEngine::luaState, -1));
        return;
    }

    lua_getglobal(LuaScriptEngine::luaState, "onInit");
    if (lua_isfunction(LuaScriptEngine::luaState, -1)) {
        LuaScriptEngine::CreateEntity(LuaScriptEngine::luaState, entity);
        if (lua_pcall(LuaScriptEngine::luaState, 1, 0, 0) != LUA_OK) {
            Log::LogError(lua_tostring(LuaScriptEngine::luaState, -1));
        }
    }
    else {
        Log::LogInfo("init function not found");
    }
}
void SignE::Core::Scripting::ScriptEngine::RunUpdateFunction(const Entity& entity, const std::string& code) {
    if (luaL_dostring(LuaScriptEngine::luaState, code.c_str()) != LUA_OK) {
        Log::LogError(lua_tostring(LuaScriptEngine::luaState, -1));
        return;
    }

    lua_getglobal(LuaScriptEngine::luaState, "onUpdate");
    if (lua_isfunction(LuaScriptEngine::luaState, -1)) {
        LuaScriptEngine::CreateEntity(LuaScriptEngine::luaState, entity);

        lua_pushnumber(LuaScriptEngine::luaState, Application::Application::GetDeltaTime());

        if (lua_pcall(LuaScriptEngine::luaState, 2, 0, 0) != LUA_OK) {
            Log::LogError(lua_tostring(LuaScriptEngine::luaState, -1));
        }
    }
    else {
        Log::LogInfo("update function not found");
    }
}