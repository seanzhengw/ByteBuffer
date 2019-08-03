#ifndef BYTEBUFFER_GENERICBYTEBUFFER_H_
#define BYTEBUFFER_GENERICBYTEBUFFER_H_

#include "ByteBufferBase.h"
#include "ReadableByteBuffer.h"
#include "WritableByteBuffer.h"

class GenericByteBuffer : public ReadableByteBuffer, public WritableByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    virtual ~GenericByteBuffer() = 0;

    virtual size_type Writable() override = 0;
    virtual void Write(uint8_t b) override = 0;
    virtual void Write(const uint8_t *bytes, size_type size) override = 0;
    virtual void Write(const char *str) override = 0;
    virtual void Write(const char *str, size_type size) override = 0;

    virtual size_type Remaining() override = 0;
    virtual uint8_t Read() override = 0;
    virtual void Read(void *buf, size_type size) override = 0;

    virtual void Reset() = 0;
    virtual size_type GetSize() = 0;
};

inline GenericByteBuffer::~GenericByteBuffer() {}

#endif
