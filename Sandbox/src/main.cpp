#include <iostream>
#include "../../SignE/src/SignE.h"
#include "Application/ImGuiLayer.h"

class SandboxLayer : public ApplicationLayer {
public:
    SandboxLayer() {
        Name = "Sandbox Application Layer";
    }

    void OnInit() override {
        ApplicationLayer::OnInit();

        scene = new Scene("Sanbox Scene");
        PushScene(scene);
        SetActiveScene(scene);
    }

    ~SandboxLayer() {
        delete scene;
    }
private:
    Scene* scene;
};

class SignEditorApplication : public Application {
public:
    SignEditorApplication() {
        layer = new SandboxLayer();
        imgui = new ImGuiLayer();
        PushLayer(layer);
        PushLayer(imgui);
    }

    ~SignEditorApplication() {
        delete layer;
        delete imgui;
    }
private:
    ApplicationLayer* layer;
    ApplicationLayer* imgui;
};

int main() {
    Application* app = new SignEditorApplication();
    app->Run();
    delete app;
}