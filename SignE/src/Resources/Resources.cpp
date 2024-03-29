#include "Resources.h"
#include "FileSystem/VirtualFileSystem.h"
#include "Log.h"
#include "Resources/Model.h"
#include "Resources/Texture.h"

namespace SignE::Core {

    void Resources::Init()
    {
        Ref<Model> defaultSphere = CreateRef<Model>(PrimitiveType::Sphere); 
        defaultSphere->Load();
        resources["Sphere"] = defaultSphere;

        Log::LogInfo("Resources initialized");
    }

    template<typename T>
    Ref<T> Resources::Load(const std::string& path)
    {
        if (resources.find(path) != resources.end())
        {
            return std::dynamic_pointer_cast<T>(resources[path]);
        }
        else
        {
            Ref<T> resource = CreateRef<T>(path);
            resource->Load();

            resources[path] = resource;
            return resource;
        }
    }

    template<typename T>
    void Resources::Unload(const std::string& path)
    {
        if (resources.find(path) != resources.end())
        {
            resources[path]->Cleanup();
            resources.erase(path);
        }
    }

    template Ref<Model> Resources::Load<Model>(const std::string& path);
    template void Resources::Unload<Model>(const std::string& path);

    template Ref<TextureAsset> Resources::Load<TextureAsset>(const std::string& path);
    template void Resources::Unload<TextureAsset>(const std::string& path);
}
