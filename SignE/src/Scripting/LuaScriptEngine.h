#ifndef LUASCRIPTENGINE_H
#define LUASCRIPTENGINE_H

#include <string>
#include "ScriptEngine.h"

extern "C" {
#include "lua.h"
}

namespace SignE::Core::Scene {
    class Entity;
}

namespace SignE::Core::Scripting {
    class LuaScriptEngine : public ScriptEngine
{
    public:
    static void Shutdown();

        static bool IsPaused ();
        static void Pause (); 
        static void Resume ();
        static void CreateEntity(lua_State* L, const Scene::Entity& entity);
        static lua_State* luaState;
        static bool running;
};
}

#endif // !
