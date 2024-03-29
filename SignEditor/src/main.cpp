#include <iostream>
#include "../../SignE/src/SignE.h"
#include "EditorLayer.h"

namespace SignE::Editor::Application {
    using SignE::Core::Application::Application;

    class SignEditorApplication : public Application {
    public:
        SignEditorApplication() : Application("SignEditor") {
            Core::VFS::Instance().Mount("C:/Repos/GlobalAssets/scenes", "scenes");
            Core::VFS::Instance().Mount("C:/Repos/GlobalAssets/models", "models");
            Core::VFS::Instance().Mount("C:/Repos/GlobalAssets/textures", "textures");
            PushLayer(&editorLayer);
        }

    private:
        EditorLayer editorLayer;
    };

}

int main() {
    std::unique_ptr<SignE::Core::Application::Application> app = std::make_unique<SignE::Editor::Application::SignEditorApplication>();
    app->Run();
}
