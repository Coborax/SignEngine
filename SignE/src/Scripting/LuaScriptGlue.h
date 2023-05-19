#ifndef LUAS_SCRIPTGLUE_H
#define LUAS_SCRIPTGLUE_H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace SignE::Core::Scene
{
    class Entity;
}

namespace SignE::Core::Scripting
{
    using namespace SignE::Core::Scene;

    class LuaScriptGlue
    {
    public:
        static void RegisterComponents(lua_State* L);
        static void RegisterFunctions(lua_State* L);
    };
}

#endif // !#ifndef LUAS_SCRIPTGLUE_H
