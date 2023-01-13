#include <iostream>
#include "../../SignE/src/SignE.h"
#include "Application/ImGuiLayer.h"
#include "EditorLayer.h"


class SignEditorApplication : public Application {
public:
    SignEditorApplication() : Application("SignEditor") {
        PushLayer(&editorLayer);
    }

private:
    EditorLayer editorLayer = EditorLayer();
};

int main() {
    Application* app = new SignEditorApplication();
    app->Run();
    delete app;
}