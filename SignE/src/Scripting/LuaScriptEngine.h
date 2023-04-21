#ifndef LUASCRIPTENGINE_H
#define LUASCRIPTENGINE_H

#include <string>

extern "C" {
#include "lua.h"
}

namespace SignE::Core::Scripting {
    class LuaScriptEngine {
    public:
        static void Init();
        static void RunScript(const std::string& code);
        static void Shutdown();

        static bool IsPaused ();
        static void Pause (); 
        static void Resume ();
    private:
        static lua_State* luaState;
        static bool running;
    };
}

#endif // !
