// This benchmark suppose the program going to reads unknown numbers of bytes
// from some interfaces, and comapre the time usages of using native array,
// Arduino String and ByteBuffer to store the incoming bytes.

#include <ByteBuffer.h>

// incoming bytes amount
const size_t TestSize = 512;

void TestArrayWrite(uint8_t *arr, size_t &buf_size, const size_t arr_size, const size_t size);
void TestArrayWrite_AvoidOptimize(uint8_t *arr,volatile size_t &buf_size, const size_t arr_size, const size_t size);
void TestStringPlus(const size_t size);
void TestStringConcat(const size_t size);
void TestByteBufferWrite(const size_t size);
void TestByteBufferWriteAndToString(const size_t size);

size_t avoid_opt;
String str_avoid_opt;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    Serial.print("Start Testing write ");
    Serial.print(TestSize - 1);
    Serial.println(" char into Array, Arduino String and Bytebuffer.");
    Serial.flush();

    // array operating
    uint32_t arrat_write_start = micros();
    uint8_t arr[TestSize];
    size_t arr_buf_size = 0;
    size_t arr_size = TestSize;
    TestArrayWrite(arr, arr_buf_size, arr_size, TestSize);
    uint32_t arrat_write_end = micros();
    Serial.print("Array Write :                        ");
    Serial.print(arrat_write_end - arrat_write_start);
    Serial.println(" us");
    Serial.flush();

    // array operating, avoid compiler optimize
    // the for loop array writing will not optimize, 
    // it gives same situation as for loop calling ByteBuffer::Write()
    uint32_t arrat_write_no_opt_start = micros();
    uint8_t arr2[TestSize];
    size_t arr_buf_size2 = 0;
    size_t arr_size2 = TestSize;
    TestArrayWrite_AvoidOptimize(arr2, arr_buf_size2, arr_size2, TestSize);
    uint32_t arrat_write_no_opt_end = micros();
    Serial.print("Array Write Avoid For loop Optimize: ");
    Serial.print(arrat_write_no_opt_end - arrat_write_no_opt_start);
    Serial.println(" us");
    Serial.flush();

    // use Arduino String to buffer incoming bytes
    // with operator+=
    uint32_t str_plus_start = micros();
    TestStringPlus(TestSize);
    uint32_t str_plus_end = micros();
    Serial.print("Arduino String +=:                   ");
    Serial.print(str_plus_end - str_plus_start);
    Serial.println(" us");
    Serial.flush();

    // use Arduino String to buffer incoming bytes
    // with method concat(char)
    uint32_t str_concat_start = micros();
    TestStringConcat(TestSize);
    uint32_t str_concat_end = micros();
    Serial.print("Arduino String concat:               ");
    Serial.print(str_concat_end - str_concat_start);
    Serial.println(" us");
    Serial.flush();

    // use ByteBuffer to buffer incoming bytes
    uint32_t buf_write_start = micros();
    TestByteBufferWrite(TestSize);
    uint32_t buf_write_end = micros();
    Serial.print("ByteBuffer write:                    ");
    Serial.print(buf_write_end - buf_write_start);
    Serial.println(" us");
    Serial.flush();

    // use ByteBuffer to buffer incoming bytes
    // and convert to Arduino String at the end
    uint32_t buf_write_and_convert_start = micros();
    TestByteBufferWriteAndToString(TestSize);
    uint32_t buf_write_and_convert_end = micros();
    Serial.print("ByteBuffer write and to String:      ");
    Serial.print(buf_write_and_convert_end - buf_write_and_convert_start);
    Serial.println(" us");
    Serial.flush();

    Serial.println("Test done.");
    Serial.flush();

    Serial.end();
    // these lines avoid compiler notice that arr and arr2 are totally not used
    Serial.print(arr_buf_size);
    Serial.write(arr, arr_size);
    Serial.print(arr_buf_size2);
    Serial.write(arr2, arr_size2);
    Serial.print(str_avoid_opt);
}

void loop()
{
}

void ArrayWrite(uint8_t *arr, size_t &buf_size, const size_t arr_size, uint8_t b)
{
    if (buf_size < arr_size)
    {
        arr[buf_size] = b;
        buf_size++;
    }
}

void TestArrayWrite(uint8_t *arr, size_t &buf_size, const size_t arr_size, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        ArrayWrite(arr, buf_size, arr_size, i);
    }
    arr[writesize] = 0;
}

void ArrayWrite_AvoidOptimize(uint8_t *arr, volatile size_t &buf_size, const size_t arr_size, uint8_t b)
{
    if (buf_size < arr_size)
    {
        arr[buf_size] = b;
        buf_size++;
    }
}

void TestArrayWrite_AvoidOptimize(uint8_t *arr,volatile size_t &buf_size, const size_t arr_size, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        ArrayWrite_AvoidOptimize(arr, buf_size, arr_size, i);
    }
    arr[writesize] = 0;
}

void TestStringPlus(const size_t size)
{
    const size_t writesize = size - 1;
    String str = "";
    str.reserve(writesize);
    for (size_t i = 0; i < writesize; i++)
    {
        str += (char)i;
    }
}

void TestStringConcat(const size_t size)
{
    const size_t writesize = size - 1;
    String str = "";
    str.reserve(writesize);
    for (size_t i = 0; i < writesize; i++)
    {
        str.concat((char)i);
    }
}

void TestByteBufferWrite(const size_t size)
{
    const size_t writesize = size - 1;
    ByteBuffer buf(size);
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
}

void TestByteBufferWriteAndToString(const size_t size)
{
    const size_t writesize = size - 1;
    ByteBuffer buf(size);
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
    str_avoid_opt = buf.CString();
}