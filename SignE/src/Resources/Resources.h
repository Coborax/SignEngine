#ifndef RESOURCES_H
#define RESOURCES_H

#include "Ref.h"
#include <string>
#include <unordered_map>

namespace SignE::Core
{

class Resource
{
public:
    Resource() = default;
    virtual ~Resource() = default;

    virtual void Load(const std::string& path) = 0;
    virtual void Cleanup() = 0;

private:
    std::string name;
};

class Resources
{
public:
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
    std::unordered_map<std::string, Ref<Resource>> resources;
};
} // namespace SignE::Core

#endif // !#ifndef RESOURCES_H
