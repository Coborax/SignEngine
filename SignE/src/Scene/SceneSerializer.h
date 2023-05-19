#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

#include <algorithm>
#include <string>

#include "Ref.h"

namespace SignE::Core::Scene {
    class Scene;

    class SceneSerializer {
    public:
        explicit SceneSerializer(const Ref<Scene>& scene) : scene(scene) {}

        void Serialize(const std::string& filepath);
        void Deserialize(const std::string& filepath);

    private:
        Ref<Scene> scene;
    };
}


#endif // !#ifndef SCENE_SERIALIZER_H
