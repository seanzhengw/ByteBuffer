#ifndef BYTEBUFFER_LINEARBYTEBUFFER_H_
#define BYTEBUFFER_LINEARBYTEBUFFER_H_

#include "GenericByteBuffer.h"

class LinearByteBuffer  : public GenericByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    virtual ~LinearByteBuffer() = 0;

    virtual size_type Writable() override = 0;
    virtual void Write(uint8_t b) override = 0;
    virtual void Write(const uint8_t *bytes, size_type size) override = 0;
    virtual void Write(const char *str) override = 0;
    virtual void Write(const char *str, size_type size) override = 0;

    virtual size_type Remaining() override = 0;
    virtual uint8_t Read() override = 0;
    virtual void Read(void *buf, size_type size) override = 0;

    virtual void Reset() override = 0;
    virtual size_type GetSize() override = 0;

    virtual void Rewind() = 0;
    virtual void Compact() = 0;
};

inline LinearByteBuffer::~LinearByteBuffer() {}

#endif
