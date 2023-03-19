//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef SIGNEPROJECT_APPLICATIONLAYER_H
#define SIGNEPROJECT_APPLICATIONLAYER_H


#include "Scene/Scene.h"


namespace SignE::Core::Application {
    using SignE::Core::Scene::Scene;

    class ApplicationLayer {
    public:
        virtual void OnInit();
        virtual void OnUpdate(float dt);
        virtual void OnDraw();
        virtual void OnShutdown();

        void PushScene(Scene* scene) { scenes.push_back(scene); }
        void SetActiveScene(Scene* scene);

        std::string Name = "Application Layer";
        Scene* ActiveScene;
    private:
        std::vector<Scene*> scenes;
    };
}

#endif //SIGNEPROJECT_APPLICATIONLAYER_H
