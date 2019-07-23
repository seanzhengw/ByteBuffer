#ifndef BYTEBUFFER_READABLEBYTEBUFFER_H_
#define BYTEBUFFER_READABLEBYTEBUFFER_H_

#include <stdint.h>
#include "ByteBufferBase.h"

// ReadableByteBuffer is a stream-like read interface for byte array.
class ReadableByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    virtual ~ReadableByteBuffer(){};

    // Rewinds this buffer, read position set to zero.
    virtual void Rewind() = 0;

    // Return readable bytes count
    virtual size_type Remaining() = 0;
    // Read one byte from this buffer
    virtual uint8_t Read() = 0;
    // Read bytes from this buffer
    virtual void Read(void *buf, size_type size) = 0;
};

#endif