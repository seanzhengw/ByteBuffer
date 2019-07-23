#ifndef BYTEBUFFER_WRITABLEBYTEBUFFER_H_
#define BYTEBUFFER_WRITABLEBYTEBUFFER_H_

#include <stdint.h>
#include "ByteBufferBase.h"

// WritableByteBuffer is a stream-like write interface for byte array.
class WritableByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    virtual ~WritableByteBuffer(){};

    // Return writable bytes size.
    virtual size_type Writable() = 0;
    // Write one byte into this buffer
    virtual void Write(uint8_t b) = 0;
    // Write bytes into this buffer
    virtual void Write(const uint8_t *bytes, size_type size) = 0;
    // Write a null-terminated string into this buffer
    virtual void Write(const char *str) = 0;
    // Write n size bytes from a c-string into this buffer
    virtual void Write(const char *str, size_type size) = 0;
};

#endif