//
// Created by Mikkel Mouridsen on 17/12/2022.
//

#ifndef MYPROJECT_APPLICATION_H
#define MYPROJECT_APPLICATION_H


#include <vector>
#include "ApplicationLayer.h"

class Application {
public:
    void Run();
    void PushLayer(ApplicationLayer* layer) { layers.push_back(layer); }
private:
    std::vector<ApplicationLayer*> layers;
};


#endif //MYPROJECT_APPLICATION_H
