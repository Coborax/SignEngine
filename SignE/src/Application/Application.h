//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef MYPROJECT_APPLICATION_H
#define MYPROJECT_APPLICATION_H


#include <vector>
#include "ApplicationLayer.h"

class Application {
public:
    Application(std::string name) {
        this->name = name;
    }

    void Run();
    void PushLayer(ApplicationLayer* layer);
private:
    std::vector<ApplicationLayer*> layers;
    bool running = false;
    std::string name;
};


#endif //MYPROJECT_APPLICATION_H
