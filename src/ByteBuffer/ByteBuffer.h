#ifndef BYTEBUFFER_BYTEBUFFER_H_
#define BYTEBUFFER_BYTEBUFFER_H_

// uncomment this line for using StaticByteBuffer as ByteBuffer
// #define BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT

// uncomment this line for just DynamicByteBuffer and StaticByteBuffer
// #define BYTEBUFFER_USING_NOTHING_AS_DEFAULT

#include "DynamicByteBuffer.h"
#include "StaticByteBuffer.h"

#ifndef BYTEBUFFER_USING_NOTHING_AS_DEFAULT
#ifndef BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT
using ByteBuffer = DynamicByteBuffer;
#else // #ifndef BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT
using ByteBuffer = StaticByteBuffer;
#endif // #ifndef BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT
#endif // ifndef BYTEBUFFER_USING_NOTHING_AS_DEFAULT

#endif