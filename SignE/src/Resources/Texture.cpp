#include "Texture.h"

#include "FileSystem/VirtualFileSystem.h"
#include "Renderer/Texture.h"

namespace SignE::Core
{
void TextureAsset::Load()
{
    auto absolutePath = VFS::Instance().GetAbsolutePath(GetPath());
    texture = Renderer::Texture::Create(absolutePath);
}

void TextureAsset::Cleanup()
{
    texture.reset();
}
} // namespace SignE::Core
