//
// Created by mikke on 13-08-2023.
//

#ifndef SIGNEPROJECT_SCRIPTENGINE_H
#define SIGNEPROJECT_SCRIPTENGINE_H

#include "lua.h"
#include "Scene/Entity.h"
#include <string>
namespace SignE
{
namespace Core
{
    namespace Scripting
    {

        class ScriptEngine
        {
        public:
            static void Init();
            static void RunScript(const Scene::Entity& entity, const std::string& code);
            static void RunInitFunction(const Scene::Entity& entity, const std::string& code);
            static void RunUpdateFunction(const Scene::Entity& entity, const std::string& code);
        };

    } // namespace Scripting
} // namespace Core
} // namespace SignE

#endif // SIGNEPROJECT_SCRIPTENGINE_H
