#ifndef BYTEBUFFER_READABLEBYTEBUFFER_H_
#define BYTEBUFFER_READABLEBYTEBUFFER_H_

#include <stddef.h>
#include <stdint.h>

// ReadableByteBuffer is a stream-like read interface for byte array.
class ReadableByteBuffer
{
public:
    virtual ~ReadableByteBuffer(){};

    // Rewinds this buffer, read position set to zero.
    virtual void Rewind() = 0;

    // Return readable bytes count
    virtual size_t Remaining() = 0;
    // Read one byte from this buffer
    virtual uint8_t Read() = 0;
    // Read bytes from this buffer
    virtual void Read(void *buf, size_t size) = 0;
};

#endif