#ifndef LUASCRIPTENGINE_H
#define LUASCRIPTENGINE_H

#include <string>

extern "C" {
#include "lua.h"
}

namespace SignE::Core::Scene {
    class Entity;
}

namespace SignE::Core::Scripting {
    class LuaScriptEngine {
    public:
        static void Init();
        static void RunScript(const Scene::Entity& entity, const std::string& code);
        static void RunInitFunction(const Scene::Entity& entity, const std::string& code);
        static void RunUpdateFunction(const Scene::Entity& entity, const std::string& code);
        static void Shutdown();

        static bool IsPaused ();
        static void Pause (); 
        static void Resume ();
    private:
        static lua_State* luaState;
        static bool running;

        static void CreateEntity(lua_State* L, const Scene::Entity& entity);
    };
}

#endif // !
