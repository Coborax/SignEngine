#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Ref.h"

namespace SignE::Core::Renderer
{

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual unsigned int GetCount() const = 0;

    static Ref<IndexBuffer> Create(const unsigned int* data, unsigned int count);
};

} // namespace SignE::Core::Renderer

#endif // !#ifndef INDEXBUFFER_H
