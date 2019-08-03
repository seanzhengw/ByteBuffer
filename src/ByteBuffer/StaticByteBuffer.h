#ifndef BYTEBUFFER_STATICBYTEBUFFER_H_
#define BYTEBUFFER_STATICBYTEBUFFER_H_

#include <string.h>
#include "LinearByteBuffer.h"

class StaticByteBufferHelper;

// StaticByteBuffer is a class for byte array operating,
// use array with stream-like read/write interface.
// use template to set compile time buffer size.
template <ByteBufferBase::size_type mSize>
class StaticByteBuffer : public LinearByteBuffer
{
    using size_type = ByteBufferBase::size_type;

public:
    // Initialize
    StaticByteBuffer();
    // Copy another ByteBuffer
    StaticByteBuffer(const StaticByteBuffer &b);
    // Copy another ByteBuffer, this overwrite current datas
    StaticByteBuffer &operator=(const StaticByteBuffer &b);
    // Destroy
    virtual ~StaticByteBuffer();

    // Compacts this buffer,
    // put unread bytes to the buffer head, make more writable spaces.
    virtual void Compact() override;
    // Reset everything of this buffer
    virtual void Reset() override;
    // Return write position
    size_type GetWritePos();
    // Return read position
    size_type GetReadPos();
    // Return buffer size
    virtual size_type GetSize() override;
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

    friend class StaticByteBufferHelper;

private:
    // write position
    size_type mWrites;
    // Read position
    size_type mReads;
    // Buffer
    uint8_t mBuf[mSize];
};

class StaticByteBufferHelper
{
public:
    template <ByteBufferBase::size_type newSize, ByteBufferBase::size_type oldSize>
    static StaticByteBuffer<newSize> ResizeByteBuffer(StaticByteBuffer<oldSize> &b);
};

template <ByteBufferBase::size_type newSize, ByteBufferBase::size_type oldSize>
inline StaticByteBuffer<newSize> StaticByteBufferHelper::ResizeByteBuffer(StaticByteBuffer<oldSize> &b)
{
    StaticByteBuffer<newSize> ret;
    ret.mWrites = b.mWrites > newSize ? newSize : b.mWrites;
    ret.mReads = b.mReads > newSize ? newSize : b.mReads;
    memcpy(ret.mBuf, b.mBuf, newSize > oldSize ? oldSize : newSize);
    return ret;
}

template <ByteBufferBase::size_type mSize>
inline StaticByteBuffer<mSize>::StaticByteBuffer() : mWrites(0), mReads(0)
{
}

template <ByteBufferBase::size_type mSize>
inline StaticByteBuffer<mSize>::StaticByteBuffer(const StaticByteBuffer &b) : mWrites(b.mWrites), mReads(b.mReads)
{
    memcpy(mBuf, b.mBuf, mWrites);
}

template <ByteBufferBase::size_type mSize>
inline StaticByteBuffer<mSize> &StaticByteBuffer<mSize>::operator=(const StaticByteBuffer<mSize> &b)
{
    mWrites = b.mWrites;
    mReads = b.mReads;
    memcpy(mBuf, b.mBuf, mWrites);
    return (*this);
}

template <ByteBufferBase::size_type mSize>
inline StaticByteBuffer<mSize>::~StaticByteBuffer()
{
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Rewind()
{
    mReads = 0;
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Compact()
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

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Reset()
{
    mReads = 0;
    mWrites = 0;
}

template <ByteBufferBase::size_type mSize>
inline ByteBufferBase::size_type StaticByteBuffer<mSize>::GetWritePos()
{
    return mWrites;
}

template <ByteBufferBase::size_type mSize>
inline ByteBufferBase::size_type StaticByteBuffer<mSize>::GetReadPos()
{
    return mReads;
}

template <ByteBufferBase::size_type mSize>
inline ByteBufferBase::size_type StaticByteBuffer<mSize>::GetSize()
{
    return mSize;
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::SetWritePos(size_type pos)
{
    mWrites = pos;
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::SetReadPos(size_type pos)
{
    mReads = pos;
}

template <ByteBufferBase::size_type mSize>
inline ByteBufferBase::size_type StaticByteBuffer<mSize>::Writable()
{
    return mSize - mWrites;
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Write(uint8_t b)
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = b;
        mWrites++;
    }
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Write(const uint8_t *bytes, size_type size)
{
    if (Writable() >= size)
    {
        memcpy(&mBuf[mWrites], bytes, size);
        mWrites += size;
    }
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Write(const char *str)
{
    Write((uint8_t *)str, strlen(str));
}

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Write(const char *str, size_type size)
{
    Write((const uint8_t *)str, size);
}

template <ByteBufferBase::size_type mSize>
inline ByteBufferBase::size_type StaticByteBuffer<mSize>::Remaining()
{
    return mWrites - mReads;
}

template <ByteBufferBase::size_type mSize>
inline uint8_t StaticByteBuffer<mSize>::Read()
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

template <ByteBufferBase::size_type mSize>
inline void StaticByteBuffer<mSize>::Read(void *buf, size_type size)
{
    size_type readsize = Remaining() >= size ? size : Remaining();
    memcpy(buf, &mBuf[mReads], readsize);
    mReads += readsize;
}

template <ByteBufferBase::size_type mSize>
inline const char *StaticByteBuffer<mSize>::CString()
{
    if (mWrites < mSize)
    {
        mBuf[mWrites] = 0;
    } else {
        mBuf[mSize - 1] = 0;
    }
    return (const char *)(&mBuf[mReads]);
}

template <ByteBufferBase::size_type mSize>
inline uint8_t *StaticByteBuffer<mSize>::GetBuf()
{
    return mBuf;
}

template <ByteBufferBase::size_type mSize>
inline uint8_t &StaticByteBuffer<mSize>::operator[](unsigned int i)
{
    return mBuf[i];
}

template <ByteBufferBase::size_type mSize>
inline uint8_t StaticByteBuffer<mSize>::operator[](unsigned int i) const
{
    return mBuf[i];
}

#endif
