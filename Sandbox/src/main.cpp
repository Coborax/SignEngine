#include <iostream>
#include "../../SignE/src/SignE.h"

class SandboxLayer : public ApplicationLayer {
public:
    SandboxLayer() {
        Name = "Sandbox Application Layer";
    }

    void OnInit() override {
        ApplicationLayer::OnInit();
        SetActiveScene(&scene);
    }
private:
    Scene scene;
};

class SandboxApplication : public Application {
public:
    SandboxApplication() : Application("SignE Sandbox") {
        PushLayer(&layer);
    }

private:
    SandboxLayer layer;
};
int main() {
    std::unique_ptr<SignE::Core::Application::Application> app = std::make_unique<SignE::Editor::Application::SignEditorApplication>();
    app->Run();
}
