ByteBuffer
===

ByteBuffer provides a stream-like read/write interface for byte array.

## Feature

* Stream interface read/write ByteBuffer.
* Passing ByteBuffer easily with it's own properties.
* Copy ByteBuffer easily with a `=` operator.
* DynamicByteBuffer for runtime resizable buffer.
* StaticByteBuffer for compile time size buffer.

## Quickstart

    // create DynamicByteBuffer with 64 bytes capacity.
    DynamicByteBuffer buf(64);
    
    // Write byte
    buf.Write('a');

    // Write bytes, length 5.
    uint8_t byte_array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    buf.Write(byte_array, 5)

    // Write string
    const char* c_str = "abc"
    buf.Write(c_str);

    // Read byte
    uint8_t b = buf.Read();

    // Read bytes, length 5.
    uint8_t byte_array2[5];
    buf.Read(byte_array2, 5);

see [examples](examples) for using ByteBuffer in Arduino platform.

## Benchmark

See [Benchmark.md](Benchmark.md) for details.