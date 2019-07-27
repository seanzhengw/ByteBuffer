#ifndef BYTEBUFFER_BYTEBUFFERS_H_
#define BYTEBUFFER_BYTEBUFFERS_H_

// uncomment this line for using StaticByteBuffer as ByteBuffer
// #define BYTEBUFFER_USING_DYNAMICBYTEBUFFER_AS_DEFAULT

// uncomment this line for using StaticByteBuffer as ByteBuffer
// #define BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT

#include "DynamicByteBuffer.h"
#include "StaticByteBuffer.h"

#ifndef __MBED__
// mbed-os has class ByteBuffer at /mbed-os/drivers/internal/ByteBuffer.h
// using ByteBuffer = ..; would conflict

#if defined(BYTEBUFFER_USING_DYNAMICBYTEBUFFER_AS_DEFAULT)
using ByteBuffer = DynamicByteBuffer;
#elif defined(BYTEBUFFER_USING_STATICBYTEBUFFER_AS_DEFAULT)
using ByteBuffer = StaticByteBuffer;
#endif // #if defined(BYTEBUFFER_USING_DYNAMICBYTEBUFFER_AS_DEFAULT)

#endif // #ifndef __MBED__

#endif