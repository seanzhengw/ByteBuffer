// The example of ByteBuffer usage

// include ByteBuffer.h
#include <ByteBuffer.h>

// Create ByteBuffer with buffer capacity 32 bytes
ByteBuffer buf(32);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    // show capacity
    Serial.print("buffer size: ");
    Serial.println(buf.GetSize());

    // write byte
    buf.Write(97);

    // write char
    buf.Write((uint8_t)'b');

    // write byte array (10 bytes, 99 ~ 108 is char "cdefghijkl")
    uint8_t arr[10] = {99, 100, 101, 102, 103, 104, 105, 106, 107, 108};
    buf.Write(arr, 10);

    // write c string (14 bytes, without null-terminated byte)
    buf.Write("mnopqrstuvwxyz");

    // write c string with size (5 bytes)
    buf.Write("0123456789", 5);

    Serial.println("buffer write 31 bytes.");

    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // show writable
    Serial.print("buffer writable: ");
    Serial.println(buf.Writable());

    // as c string
    Serial.print("as c string: ");
    Serial.println(buf.CString());

    // read byte
    Serial.print("read 1 byte: ");
    Serial.println(buf.Read());

    // read bytes
    uint8_t out[10];
    buf.Read(out, 10);

    Serial.print("read 10 bytes: ");
    for (size_t i = 0; i < 10; i++)
    {
        Serial.print(out[i]);
        Serial.print(' ');
    }
    Serial.println();

    // as c string won't show bytes already read.
    Serial.print("as c string: ");
    Serial.println(buf.CString());
    
    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // show writable
    Serial.print("buffer writable: ");
    Serial.println(buf.Writable());

    // show write position
    Serial.print("write position: ");
    Serial.println(buf.GetWritePos());

    // show read position
    Serial.print("read position: ");
    Serial.println(buf.GetReadPos());

    // use compact to move left bytes to buffer head
    buf.Compact();
    Serial.println("buffer compacted.");

    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // show writable
    Serial.print("buffer writable: ");
    Serial.println(buf.Writable());

    // show write position
    Serial.print("write position: ");
    Serial.println(buf.GetWritePos());

    // show read position
    Serial.print("read position: ");
    Serial.println(buf.GetReadPos());

    // resize to 64 bytes
    buf.Resize(64);
    Serial.println("buffer resize capacity to 64 bytes, left datas would keeped.");

    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());
    
    // show writable
    Serial.print("buffer writable: ");
    Serial.println(buf.Writable());

    // read 10 bytes
    buf.Read(out, 10);
    Serial.print("read 10 bytes: ");
    for (size_t i = 0; i < 10; i++)
    {
        Serial.print(out[i]);
        Serial.print(' ');
    }
    Serial.println();

    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // rewind buffer
    buf.Rewind();
    Serial.println("buffer rewind.");

    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // read 10 bytes
    buf.Read(out, 10);
    Serial.print("read 10 bytes: ");
    for (size_t i = 0; i < 10; i++)
    {
        Serial.print(out[i]);
        Serial.print(' ');
    }
    Serial.println();

    // direct access buffer by pointer
    uint8_t* buffer = buf.GetBuf();
    Serial.print("direct access buffer[0]~[9] by pointer: ");
    for (size_t i = 0; i < 10; i++)
    {
        Serial.print(buffer[i]);
        Serial.print(' ');
    }
    Serial.println();
    
    // direct access buffer by pointer
    Serial.println("direct access buffer[0]~[9] by pointer, add 1 to each byte.");
    for (size_t i = 0; i < 10; i++)
    {
        buffer[i] += 1;
    }
    
    // direct access buffer by subscipt
    Serial.println("direct access buffer[0]~[9] by subscipt, add 1 to each byte.");
    for (size_t i = 0; i < 10; i++)
    {
        buf[i] += 1;
    }

    // direct access buffer by subscipt
    Serial.print("direct access buffer[0]~[9] by subscipt: ");
    for (size_t i = 0; i < 10; i++)
    {
        Serial.print(buf[i]);
        Serial.print(' ');
    }
    Serial.println();

    // buffer copy
    Serial.println("copy buffer as buffer2.");
    ByteBuffer buf2(buf);
    // same as ByteBuffer buf2 = buf;

    // reset buffer
    buf.Reset();
    Serial.println("buffer reset.");
    
    // show remaining
    Serial.print("buffer remaining: ");
    Serial.println(buf.Remaining());

    // show writable
    Serial.print("buffer writable: ");
    Serial.println(buf.Writable());
    
    // buf2 is independent
    Serial.println("buffer2 is independent of buffer");
    // show remaining
    Serial.print("buffer2 remaining: ");
    Serial.println(buf2.Remaining());

    // show writable
    Serial.print("buffer2 writable: ");
    Serial.println(buf2.Writable());
    
    // existing buffer copy another buffer
    Serial.println("create buffer3 with 32 bytes capacity.");
    ByteBuffer buf3(32);
    Serial.println("copy buffe2 to existing buffer3.");
    buf3 = buf2;
    
    // buf3 is independent`
    Serial.println("buffer3 is independent of buffer2");

    // reset buffer
    buf2.Reset();
    Serial.println("buffer2 reset.");
    
    // show remaining
    Serial.print("buffer3 remaining: ");
    Serial.println(buf3.Remaining());

    // show writable
    Serial.print("buffer3 writable: ");
    Serial.println(buf3.Writable());

    Serial.println("example done.");
}

void loop()
{
}