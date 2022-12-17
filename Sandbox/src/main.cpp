#include <iostream>
#include "../../SignE/src/SignE.h"

class TestLayer : public ApplicationLayer {
public:
    void Update(float dt) override {
        Log::LogInfo("Updating Test Layer!");
    }
};

int main() {
    Application* app = new Application();

    TestLayer* layer = new TestLayer();
    app->PushLayer(layer);

    app->Run();
    delete app;
    delete layer;
}