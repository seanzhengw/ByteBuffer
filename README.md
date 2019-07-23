ByteBuffer
===

ByteBuffer provides a stream-like read/write interface for byte array.

## Quickstart

    // create ByteBuffer with 64 bytes capacity.
    ByteBuffer buf(64);
    
    // Write byte
    buf.Write('a');

    // Write bytes, length 5.
    uint8_t byte_array[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    buf.write(byte_array, 5)

    // Write string
    const char* c_str = "abc"
    buf.writeStr(c_str);

    // Read byte
    uint8_t b = buf.Read();

    // Read bytes, length 5.
    uint8_t byte_array2[5];
    buf.Read(byte_array2, 5);

see [examples](example) for using ByteBuffer in Arduion platform.