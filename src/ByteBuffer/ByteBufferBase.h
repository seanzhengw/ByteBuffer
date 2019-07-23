#ifndef BYTEBUFFER_BYTEBUFFERBASE_H_
#define BYTEBUFFER_BYTEBUFFERBASE_H_

#include <stddef.h>

class ByteBufferBase
{
public:
    using size_type = size_t;

private:
    ByteBufferBase() = delete;
};

#endif