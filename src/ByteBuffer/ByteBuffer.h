#ifndef BYTEBUFFER_BYTEBUFFER_H_
#define BYTEBUFFER_BYTEBUFFER_H_

#include "ReadableByteBuffer.h"
#include "WritableByteBuffer.h"

// ByteBuffer is a class for byte array operating,
// use array with stream-like read/write interface.
class ByteBuffer : public ReadableByteBuffer, WritableByteBuffer
{
public:
    // Initialize with buffer size
    ByteBuffer(size_t size = 64);
    // Copy another ByteBuffer
    ByteBuffer(const ByteBuffer &b);
    // Copy another ByteBuffer, this discard current datas
    ByteBuffer &operator=(const ByteBuffer &b);
    // Destroy
    ~ByteBuffer();

    // Resize this buffer,
    // if new size is smaller than current, over sized datas would discard.
    // if new size is smaller than current read/write position,
    // read/write position would set to new size. (means reach buffer end)
    void Resize(size_t size);
    // Compacts this buffer,
    // put unread bytes to the buffer head, make more writable spaces.
    void Compact();
    // Reset everything of this buffer
    void Reset();
    // Return write position
    size_t GetWritePos();
    // Return read position
    size_t GetReadPos();
    // Return buffer size
    size_t GetSize();

    virtual size_t Writable() override;
    virtual void Write(uint8_t b) override;
    virtual void Write(const uint8_t *bytes, size_t size) override;
    virtual void Write(const char *str) override;
    virtual void Write(const char *str, size_t size) override;

    virtual void Rewind() override;
    virtual size_t Remaining() override;
    virtual uint8_t Read() override;
    virtual void Read(void *buf, size_t size) override;

    // Return a null-terminated string from readable bytes
    const char *CString();
    // Return direct pointer.
    uint8_t *GetBuf();
    // Direct access buffer c-array-style
    uint8_t &operator[](unsigned int i);
    // Direct access buffer c-array-style
    uint8_t operator[](unsigned int i) const;

private:
    // Buffer size
    size_t mSize;
    // write position
    size_t mWrites;
    // Read position
    size_t mReads;
    // Buffer
    uint8_t *mBuf;
};

#endif