//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef MYPROJECT_APPLICATION_H
#define MYPROJECT_APPLICATION_H


#include "Ref.h"

#include <string>
#include <vector>

namespace SignE::Core::Application {
    class ApplicationLayer;
    class Window;

    class Application {
    public:
        Application(std::string name) : name(name) { }

        void Run();
        void PushLayer(ApplicationLayer* layer);

        static float GetDeltaTime();
        static Ref<Window> GetWindow();
    private:
        std::vector<ApplicationLayer*> layers;
        bool running = false;
        std::string name;
        static Ref<Window> window;
        float lastFrameTime = 0.0f;
        static float deltaTime;
    };
}

#endif //MYPROJECT_APPLICATION_H
