#include <iostream>
#include "../../SignE/src/SignE.h"

class TestLayer : public ApplicationLayer {
public:
    void Update(float dt) override {
    }
    void Draw() override {
        Renderer2D::DrawRect(10, 10);
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