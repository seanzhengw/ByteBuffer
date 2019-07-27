// The example of WritableByteBuffer interface

// include ByteBuffer.h
#include <ByteBuffer/ByteBuffers.h>

// Create ByteBuffer with buffer capacity 32 bytes
ByteBuffer buf(32);

void this_function_will_not_read_anything(WritableByteBuffer *bytebuf)
{
    // WritableByteBuffer don't have Read() methods, it's write only.

    // Writable() returns spaces availiable for writes.
    if (bytebuf->Writable() >= 10)
    {
        bytebuf->Write("0123456789");
    }
}

void this_function_will_not_read_anything_either(WritableByteBuffer &bytebuf)
{
    if (bytebuf.Writable())
    {
        bytebuf.Write(' ');
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    // put 'x' into buffer
    buf.Write("x");

    this_function_will_not_read_anything(&buf);
    this_function_will_not_read_anything_either(buf);

    // since the buf never read, next buf.Read() should be 'x'
    if (buf.Read() != 'x')
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