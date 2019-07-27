#ifndef BYTEBUFFER_DYNAMICBYTEBUFFER_H_
#define BYTEBUFFER_DYNAMICBYTEBUFFER_H_

#include "ByteBufferBase.h"
#include "ReadableByteBuffer.h"
#include "WritableByteBuffer.h"
#include <string.h>

// ByteBuffer is a class for byte array operating,
// use array with stream-like read/write interface.
class DynamicByteBuffer : public ReadableByteBuffer, public WritableByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    // Initialize with buffer size
    DynamicByteBuffer(size_type size = 64);
    // Copy another ByteBuffer
    DynamicByteBuffer(const DynamicByteBuffer &b);
    // Copy another ByteBuffer, this discard current datas
    DynamicByteBuffer &operator=(const DynamicByteBuffer &b);
    // Destroy
    virtual ~DynamicByteBuffer();

    // Resize this buffer,
    // if new size is smaller than current, over sized datas would discard.
    // if new size is smaller than current read/write position,
    // read/write position would set to new size. (means reach buffer end)
    void Resize(size_type size);
    // Compacts this buffer,
    // put unread bytes to the buffer head, make more writable spaces.
    void Compact();
    // Reset everything of this buffer
    void Reset();
    // Return write position
    size_type GetWritePos();
    // Return read position
    size_type GetReadPos();
    // Return buffer size
    size_type GetSize();
    // Set write position
    void SetWritePos(size_type pos);
    // Set read position
    void SetReadPos(size_type pos);

    virtual size_type Writable() override;
    virtual void Write(uint8_t b) override;
    virtual void Write(const uint8_t *bytes, size_type size) override;
    virtual void Write(const char *str) override;
    virtual void Write(const char *str, size_type size) override;

    virtual void Rewind() override;
    virtual size_type Remaining() override;
    virtual uint8_t Read() override;
    virtual void Read(void *buf, size_type size) override;

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
    size_type mSize;
    // write position
    size_type mWrites;
    // Read position
    size_type mReads;
    // Buffer
    uint8_t *mBuf;
};

inline DynamicByteBuffer::DynamicByteBuffer(size_type size) : mSize(size), mWrites(0), mReads(0), mBuf(new uint8_t[size])
{
}

inline DynamicByteBuffer::DynamicByteBuffer(const DynamicByteBuffer &b) : mSize(b.mSize), mWrites(b.mWrites), mReads(b.mReads), mBuf(new uint8_t[b.mSize])
{
    memcpy(mBuf, b.mBuf, mWrites);
}

inline DynamicByteBuffer &DynamicByteBuffer::operator=(const DynamicByteBuffer &b)
{
    delete[] mBuf;
    mSize = b.mSize;
    mWrites = b.mWrites;
    mReads = b.mReads;
    mBuf = new uint8_t[b.mSize];
    memcpy(mBuf, b.mBuf, mWrites);
    return (*this);
}

inline DynamicByteBuffer::~DynamicByteBuffer()
{
    delete[] mBuf;
}

inline void DynamicByteBuffer::Resize(size_type size)
{
    uint8_t *buf = mBuf;
    mBuf = new uint8_t[size];
    mSize = size;
    mWrites = mWrites > mSize ? mSize : mWrites;
    mReads = mReads > mSize ? mSize : mReads;
    memcpy(mBuf, buf, mSize);
    delete[] buf;
}

inline void DynamicByteBuffer::Rewind()
{
    mReads = 0;
}

inline void DynamicByteBuffer::Compact()
{
    if (mReads == 0)
    {
        return;
    }
    size_type size = Remaining();
    memmove(mBuf, mBuf + mReads, size);
    mReads = 0;
    mWrites = size;
}

inline void DynamicByteBuffer::Reset()
{
    mReads = 0;
    mWrites = 0;
}

inline DynamicByteBuffer::size_type DynamicByteBuffer::GetWritePos()
{
    return mWrites;
}

inline DynamicByteBuffer::size_type DynamicByteBuffer::GetReadPos()
{
    return mReads;
}

inline DynamicByteBuffer::size_type DynamicByteBuffer::GetSize()
{
    return mSize;
}

inline void DynamicByteBuffer::SetWritePos(size_type pos)
{
    mWrites = pos;
}

inline void DynamicByteBuffer::SetReadPos(size_type pos)
{
    mReads = pos;
}

inline DynamicByteBuffer::size_type DynamicByteBuffer::Writable()
{
    return mSize - mWrites;
}

inline void DynamicByteBuffer::Write(uint8_t b)
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = b;
        mWrites++;
    }
}

inline void DynamicByteBuffer::Write(const uint8_t *bytes, size_type size)
{
    if (Writable() >= size)
    {
        memcpy(&mBuf[mWrites], bytes, size);
        mWrites += size;
    }
}

inline void DynamicByteBuffer::Write(const char *str)
{
    Write((uint8_t *)str, strlen(str));
}

inline void DynamicByteBuffer::Write(const char *str, size_type size)
{
    Write((const uint8_t *)str, size);
}

inline DynamicByteBuffer::size_type DynamicByteBuffer::Remaining()
{
    return mWrites - mReads;
}

inline uint8_t DynamicByteBuffer::Read()
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

inline void DynamicByteBuffer::Read(void *buf, size_type size)
{
    size_type readsize = Remaining() >= size ? size : Remaining();
    memcpy(buf, &mBuf[mReads], readsize);
    mReads += readsize;
}

inline const char *DynamicByteBuffer::CString()
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = 0;
    } else {
        mBuf[mSize - 1] = 0;
    }
    return (const char *)(&mBuf[mReads]);
}

inline uint8_t *DynamicByteBuffer::GetBuf()
{
    return mBuf;
}

inline uint8_t &DynamicByteBuffer::operator[](unsigned int i)
{
    return mBuf[i];
}

inline uint8_t DynamicByteBuffer::operator[](unsigned int i) const
{
    return mBuf[i];
}

#endif