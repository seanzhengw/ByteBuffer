// The example of ReadableByteBuffer interface

// include ByteBuffers.h
#include <ByteBuffers.h>

// Create ByteBuffer with buffer capacity 32 bytes
DynamicByteBuffer buf(32);

void this_function_will_not_write_anything(ReadableByteBuffer *bytebuf)
{
    // ReadableByteBuffer don't have Write() methods, it's read only.

    // Remaining() returns how many bytes can read.
    if (bytebuf->Remaining() >= 10)
    {
        uint8_t arr[10];
        bytebuf->Read(arr, 10);
    }
}

void this_function_will_not_write_anything_either(ReadableByteBuffer &bytebuf)
{
    if(!bytebuf.Remaining()){
        // rewind to read the buffer front the head.
        bytebuf.Rewind();
    }

    if (bytebuf.Remaining())
    {
        uint8_t b = bytebuf.Read();
        (void)b; // this line for aviod unused variable warning
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    // write 10 bytes into buf
    buf.Write("0123456789");

    const size_t writable = buf.Writable();

    this_function_will_not_write_anything(&buf);
    this_function_will_not_write_anything_either(buf);

    // since the buf never wrote again, writable space should not changed.
    if (buf.Writable() != writable)
    {
        Serial.println("error.");
    }
    else
    {
        Serial.println("example done.");
    }
}

void loop()
{
}