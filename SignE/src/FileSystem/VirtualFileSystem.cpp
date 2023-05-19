#include "VirtualFileSystem.h"
#include "Log.h"

#include <vector>
#include <fstream>

namespace SignE::Core::VFS {

void VirtualFileSystem::Mount(std::string path, std::string mountPoint) {
  mounts[mountPoint] = path;
}

void VirtualFileSystem::Unmount(std::string mountPoint) {
  mounts.erase(mountPoint);
}

std::string VirtualFileSystem::ReadFile(std::string path) {
  std::ifstream file(path);
  std::string content((std::istreambuf_iterator<char>(file)),
                      (std::istreambuf_iterator<char>()));
  return content;
}

} // namespace SignE::Core::VFS
