#ifndef BYTEBUFFER_BYTEBUFFER_H_
#define BYTEBUFFER_BYTEBUFFER_H_

#include "ReadableByteBuffer.h"
#include "WritableByteBuffer.h"
#include <string.h>

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

inline ByteBuffer::ByteBuffer(size_t size) : mSize(size), mWrites(0), mReads(0), mBuf(new uint8_t[size])
{
}

inline ByteBuffer::ByteBuffer(const ByteBuffer &b) : mSize(b.mSize), mWrites(b.mWrites), mReads(b.mReads), mBuf(new uint8_t[b.mSize])
{
    memcpy(mBuf, b.mBuf, mWrites);
}

inline ByteBuffer &ByteBuffer::operator=(const ByteBuffer &b)
{
    delete[] mBuf;
    mSize = b.mSize;
    mWrites = b.mWrites;
    mReads = b.mReads;
    mBuf = new uint8_t[b.mSize];
    memcpy(mBuf, b.mBuf, mWrites);
    return (*this);
}

inline ByteBuffer::~ByteBuffer()
{
    delete[] mBuf;
}

inline void ByteBuffer::Resize(size_t size)
{
    uint8_t *buf = mBuf;
    mBuf = new uint8_t[size];
    mSize = size;
    mWrites = mWrites > mSize ? mSize : mWrites;
    mReads = mReads > mSize ? mSize : mReads;
    memcpy(mBuf, buf, mSize);
    delete[] buf;
}

inline void ByteBuffer::Rewind()
{
    mReads = 0;
}

inline void ByteBuffer::Compact()
{
    if (mReads == 0)
    {
        return;
    }
    size_t size = Remaining();
    memmove(mBuf, mBuf + mReads, size);
    mReads = 0;
    mWrites = size;
}

inline void ByteBuffer::Reset()
{
    mReads = 0;
    mWrites = 0;
}

inline size_t ByteBuffer::GetWritePos()
{
    return mWrites;
}

inline size_t ByteBuffer::GetReadPos()
{
    return mReads;
}

inline size_t ByteBuffer::GetSize()
{
    return mSize;
}

inline size_t ByteBuffer::Writable()
{
    return mSize - mWrites;
}

inline void ByteBuffer::Write(uint8_t b)
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = b;
        mWrites++;
    }
}

inline void ByteBuffer::Write(const uint8_t *bytes, size_t size)
{
    if (Writable() >= size)
    {
        memcpy(&mBuf[mWrites], bytes, size);
        mWrites += size;
    }
}

inline void ByteBuffer::Write(const char *str)
{
    Write((uint8_t *)str, strlen(str));
}

inline void ByteBuffer::Write(const char *str, size_t size)
{
    Write((const uint8_t *)str, size);
}

inline size_t ByteBuffer::Remaining()
{
    return mWrites - mReads;
}

inline uint8_t ByteBuffer::Read()
{
    if (mWrites > mReads)
    {
        return mBuf[mReads++];
    }
    else
    {
        return 0;
    }
}

inline void ByteBuffer::Read(void *buf, size_t size)
{
    size_t readsize = Remaining() >= size ? size : Remaining();
    memcpy(buf, &mBuf[mReads], readsize);
    mReads += readsize;
}

inline const char *ByteBuffer::CString()
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = 0;
    }
    return (const char *)(&mBuf[mReads]);
}

inline uint8_t *ByteBuffer::GetBuf()
{
    return mBuf;
}

inline uint8_t &ByteBuffer::operator[](unsigned int i)
{
    return mBuf[i];
}

inline uint8_t ByteBuffer::operator[](unsigned int i) const
{
    return mBuf[i];
}

#endif