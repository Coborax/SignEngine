//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef SIGNEPROJECT_APPLICATIONLAYER_H
#define SIGNEPROJECT_APPLICATIONLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "Ref.h"

namespace SignE::Core::Scene
{
    class Scene;
}

namespace SignE::Core::Application {
    using SignE::Core::Scene::Scene;

    class ApplicationLayer {
    public:
        virtual void OnInit();
        virtual void OnUpdate(float dt);
        virtual void OnDraw();
        virtual void OnShutdown();

        void PushScene(const Ref<Scene> scene) { scenes.push_back(scene); }
        void SetActiveScene(const Ref<Scene>& scene);

        std::string Name = "Application Layer";
        Ref<Scene> ActiveScene;
    private:
        std::vector<Ref<Scene>> scenes;
    };
}

#endif //SIGNEPROJECT_APPLICATIONLAYER_H
