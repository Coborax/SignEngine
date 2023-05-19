#ifndef VFS_H
#define VFS_H

#include <map>
#include <string>

namespace SignE::Core::VFS {

    class VirtualFileSystem {
    public:
        void Mount(std::string path, std::string mountPoint);
        void Unmount(std::string mountPoint);

        std::string ReadFile(std::string path);
        void WriteFile(std::string path, std::string data);

        std::string GetMountPoint(std::string path);
        std::string GetPath(std::string path);

    private:
        std::map<std::string, std::string> mounts;
    };
    
    static VirtualFileSystem& Instance() {
        static VirtualFileSystem vfs;
        return vfs;
    }
}

#endif // !#ifndef VFS_H
