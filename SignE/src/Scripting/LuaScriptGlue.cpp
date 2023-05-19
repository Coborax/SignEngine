#include "LuaScriptGlue.h"
#include <string>

#include "Log.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace SignE::Core::Scripting {
    using namespace SignE::Core::Scene::Components;
    using namespace SignE::Core::Scene;

    static int LuaLogInfo(lua_State* L) {
        std::string message = lua_tostring(L, 1);
        Log::LogInfo(message);

        return 0;
    }

    static int LuaLogError(lua_State* L) {
        std::string message = lua_tostring(L, 1);
        Log::LogError(message);

        return 0;
    }

    static int LuaGetEntityTag(lua_State* L) {
        Entity* entity = (Entity*)luaL_checkudata(L, 1, "Entity");
        lua_pushstring(L, entity->GetTag().c_str());

        return 1;
    }

    
    void LuaScriptGlue::RegisterComponents(lua_State* L) {
        
        luaL_Reg entityMethods[] = {
            { "getTag", LuaGetEntityTag },
            { NULL, NULL }
        };

        luaL_newmetatable(L, "Entity");
        luaL_setfuncs(L, entityMethods, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_pop(L, 1);
    }

    void LuaScriptGlue::RegisterFunctions(lua_State* L) {

        luaL_Reg functions[] = {
            { "LogInfo", LuaLogInfo },
            { "LogError", LuaLogError },
            { NULL, NULL }
        };

        luaL_newlib(L, functions);
        lua_setglobal(L, "SignE");
    }
}
