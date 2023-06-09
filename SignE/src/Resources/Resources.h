#ifndef RESOURCES_H
#define RESOURCES_H

#include "Ref.h"
#include <string>
#include <unordered_map>

namespace SignE::Core
{

class Asset
{
public:
    Asset(const std::string& path) : absolutePath(path), name(path.substr(path.find_last_of("/\\") + 1)) {};
    virtual ~Asset() = default;

    virtual void Load() = 0;
    virtual void Cleanup() = 0;

    const std::string& GetPath() const { return absolutePath; }
    const std::string& GetName() const { return name; }
private:
    std::string absolutePath;
    std::string name;
};

class Resources
{
public:
    void Init();

    template<typename T>
    Ref<T> Load(const std::string& path);

    template<typename T>
    void Unload(const std::string& path);

    static Resources& Instance()
    {
        static Resources resources;
        return resources;
    }

private:
    std::unordered_map<std::string, Ref<Asset>> resources;
};
} // namespace SignE::Core

#endif // !#ifndef RESOURCES_H
