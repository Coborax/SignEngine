//
// Created by Mikkel Mouridsen on 18/12/2022.
//

#ifndef SIGNEPROJECT_SCENE_H
#define SIGNEPROJECT_SCENE_H

#include "entt/entt.hpp"
#include "../Log.h"

class Scene {
public:
    Scene();
    Scene(std::string name);
    void OnInit();
    void OnUpdate(float dt);
    void OnDraw();
    void OnShutdown();
private:
    entt::registry registry;
    std::string name;
};


#endif //SIGNEPROJECT_SCENE_H
