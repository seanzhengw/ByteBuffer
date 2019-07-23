#ifndef BYTEBUFFER_WRITABLEBYTEBUFFER_H_
#define BYTEBUFFER_WRITABLEBYTEBUFFER_H_

#include <stddef.h>
#include <stdint.h>

// WritableByteBuffer is a stream-like write interface for byte array.
class WritableByteBuffer
{
public:
    virtual ~WritableByteBuffer(){};

    // Return writable bytes size.
    virtual size_t Writable() = 0;
    // Write one byte into this buffer
    virtual void Write(uint8_t b) = 0;
    // Write bytes into this buffer
    virtual void Write(const uint8_t *bytes, size_t size) = 0;
    // Write a null-terminated string into this buffer
    virtual void Write(const char *str) = 0;
    // Write n size bytes from a c-string into this buffer
    virtual void Write(const char *str, size_t size) = 0;
};

#endif