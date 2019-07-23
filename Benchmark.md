ByteBuffer Benchmark
===

See [Source Code](example/Benchmark/Benchmark.ino) in the examples.

This benchmark suppose the program going to reads unknown numbers of bytes 
from some interfaces, and comapre the time usages of using native array,
Arduino String and ByteBuffer to store the incoming bytes.

This Benchmark try to avoid compiler optimize for array for loop access, it
should gives a same situation as for loop calling `ByteBuffer::Write()` or 
Arduino `String::concat()`

**TestSize = 512**

    Testing write 511 char into ''Local'' Array, Arduino String and Bytebuffer.
    Array Write ---------------------------- 684 us
    Array Write Avoid For loop Optimize ---- 1676 us
    Arduino String += ---------------------- 3708 us
    Arduino String concat ------------------ 3716 us
    DynamicByteBuffer write ---------------- 1680 us
    DynamicByteBuffer write and to String -- 1632 us
    StaticByteBuffer write ----------------- 1352 us
    StaticByteBuffer write and to String --- 1300 us
    Testing write 511 char into ''Global'' Array, Arduino String and Bytebuffer.
    Array Write ---------------------------- 584 us
    Array Write Avoid For loop Optimize ---- 1032 us
    Arduino String += ---------------------- 3672 us
    Arduino String concat ------------------ 3668 us
    DynamicByteBuffer write ---------------- 1644 us
    DynamicByteBuffer write and to String -- 1628 us
    StaticByteBuffer write ----------------- 1320 us
    StaticByteBuffer write and to String --- 1300 us
    Test done.

It shows when using `ByteBuffer::Write()`  to concatenation bytes to string is 
123% ~ 177% more faster than `String::concat(char c)`, but it still 30% slower 
than using global array, 56% slower than optimized array for lopp operation.

Native array operating usually gets compiler optimize, try to move a local 
array to global space, many function calls and array accesses will get 
optimize and run faster.

Arduino String use dynamic memoey allocation, it calls `realloc` if the char 
buffer is not enough to store incoming chars, in worst case, calling 
`String::concat(char)` for every single char, it's `realloc` every times for 
one more byte space.

In the benchmark program, I called `String::reserve(size_t)` before concat any 
char, it still gets bad performance, And I notice `String::concat(char c)` 
declares a `char buf[2]` to make a null-terminated string and calls 
`String::concat(const char *cstr, unsigned int length)`, and then 
`String::concat(const char *cstr, unsigned int length)` is going to check the 
parameter cstr not null and length not 0, it unnecessary and not optimized by 
compiler.

So, I change the code inside `String::concat(char c)` from this

    unsigned char String::concat(char c)
    {
        char buf[2];
        buf[0] = c;
        buf[1] = 0;
        return concat(buf, 1);
    }

to this

    unsigned char String::concat(char c)
    {
        unsigned int newlen = len + 1;
        if (!reserve(newlen)) return 0;
        buffer[len] = c;
        len = newlen;
        return 1;
    }

And test again

**TestSize = 512**

    Start Testing write 511 char into ''Local'' Array, Arduino String and Bytebuffer.
    Array Write ---------------------------- 684 us
    Array Write Avoid For loop Optimize ---- 1676 us
    Arduino String += ---------------------- 2584 us
    Arduino String concat ------------------ 2592 us
    DynamicByteBuffer write ---------------- 1684 us
    DynamicByteBuffer write and to String -- 1636 us
    StaticByteBuffer write ----------------- 1356 us
    StaticByteBuffer write and to String --- 1300 us
    Start Testing write 511 char into ''Global'' Array, Arduino String and Bytebuffer.
    Array Write ---------------------------- 584 us
    Array Write Avoid For loop Optimize ---- 1032 us
    Arduino String += ---------------------- 2548 us
    Arduino String concat ------------------ 2544 us
    DynamicByteBuffer write ---------------- 1644 us
    DynamicByteBuffer write and to String -- 1624 us
    StaticByteBuffer write ----------------- 1316 us
    StaticByteBuffer write and to String --- 1300 us
    Test done.

`String::concat(char c)` gets better performance, but no change in results.

In conclusion, ByteBuffer is faster for char (or byte) buffering, but not 
extreme performance like array operations, using ByteBuffer also gives better 
program interface for read/write, passing ByteBuffer as parameters won't lose 
array size and bufferd bytes size, there are many advantages to make me use 
ByteBuffer, and the choice is yours.
