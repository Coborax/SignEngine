//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef MYPROJECT_APPLICATION_H
#define MYPROJECT_APPLICATION_H


#include "Application/ApplicationLayer.h"
#include "Ref.h"
#include "Renderer/Renderer.h"
#include <vector>

namespace SignE::Core::Application {
    class ApplicationLayer;

    class Application {
    public:
        Application(std::string name) : name(name) { }

        void Run();
        void PushLayer(ApplicationLayer* layer);
        static float GetDeltaTime();
    private:
        std::vector<ApplicationLayer*> layers;
        bool running = false;
        std::string name;
    };
}

#endif //MYPROJECT_APPLICATION_H
