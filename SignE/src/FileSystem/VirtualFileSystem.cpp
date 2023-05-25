#include "VirtualFileSystem.h"
#include "Log.h"

#include <string>
#include <vector>
#include <fstream>

namespace SignE::Core::VFS
{

std::map<std::string, std::string> VirtualFileSystem::mounts;

void VirtualFileSystem::Mount(std::string path, std::string mountPoint)
{
    Log::LogInfo("Mounting: " + path + " to " + mountPoint);
    mounts[mountPoint] = path;
}

void VirtualFileSystem::Unmount(std::string mountPoint)
{
    Log::LogInfo("Unmounting: " + mountPoint);
    mounts.erase(mountPoint);
}

std::string VirtualFileSystem::ReadFile(std::string path)
{
    std::string absolutePath = GetAbsolutePath(path);

    std::ifstream file(absolutePath);
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return content;
}

std::string VirtualFileSystem::GetAbsolutePath(std::string path)
{
    auto isFile = path.find_last_of('.') > path.find_last_of('/');
    auto fileName = isFile ? path.substr(path.find_last_of('/') + 1) : "";

    auto folderPath = isFile ? path.substr(0, path.find_last_of('/')) : path;
    auto mountPoint = folderPath.substr(0, folderPath.find_first_of('/'));

    if (mounts.find(mountPoint) != mounts.end())
    {
        auto aboslutePath = mounts[mountPoint] + folderPath.substr(mountPoint.size());
        return isFile ? aboslutePath + "/" + fileName : aboslutePath;
    }

    Log::LogError("Mount point not found: " + mountPoint);
    return "";
}
} // namespace SignE::Core::VFS
