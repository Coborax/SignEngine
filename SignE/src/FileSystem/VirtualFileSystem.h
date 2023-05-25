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

        std::string GetAbsolutePath(std::string path);

    private:
        static std::map<std::string, std::string> mounts;
    };
    
    static VirtualFileSystem& Instance() {
        static VirtualFileSystem vfs;
        return vfs;
    }
}

#endif // !#ifndef VFS_H
