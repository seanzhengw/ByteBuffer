// This benchmark suppose the program going to reads unknown numbers of bytes
// from some interfaces, and comapre the time usages of using native array,
// Arduino String and ByteBuffer to store the incoming bytes.

#include <ByteBuffer/ByteBuffers.h>

// incoming bytes amount
const size_t TestSize = 512;

void TestArrayWrite(uint8_t *arr, size_t &buf_size, const size_t arr_size, const size_t size);
void TestArrayWrite_AvoidOptimize(uint8_t *arr, volatile size_t &buf_size, const size_t arr_size, const size_t size);
void TestStringPlus(String &str, const size_t size);
void TestStringConcat(String &str, const size_t size);
void TestDynamicByteBufferWrite(DynamicByteBuffer &buf, const size_t size);
void TestDynamicByteBufferWriteAndToString(DynamicByteBuffer &buf, const size_t size);
template <size_t buf_size>
void TestStaticByteBufferWrite(StaticByteBuffer<buf_size> &buf, const size_t size);
template <size_t buf_size>
void TestStaticByteBufferWriteAndToString(StaticByteBuffer<buf_size> &buf, const size_t size);

uint8_t global_arr[TestSize];
String global_string;
DynamicByteBuffer global_dynamin_buf(TestSize);
StaticByteBuffer<TestSize> global_stataic_buf;

size_t avoid_opt;
String str_avoid_opt;
String str_avoid_opt_;
String str_avoid_opt1_;
String str_avoid_opt2;
String str_avoid_opt2_;

void setup()
{
    global_string.reserve(TestSize);

    Serial.begin(9600);
    while (!Serial)
        ;

    Serial.print("Testing write ");
    Serial.print(TestSize - 1);
    Serial.println(" char into ''Local'' Array, Arduino String and Bytebuffer.");
    Serial.flush();

    // array operating
    {
        uint32_t arrat_write_start = micros();
        uint8_t arr[TestSize];
        size_t arr_buf_size = 0;
        size_t arr_size = TestSize;
        TestArrayWrite(arr, arr_buf_size, arr_size, TestSize);
        uint32_t arrat_write_end = micros();
        Serial.print("Array Write ---------------------------- ");
        Serial.print(arrat_write_end - arrat_write_start);
        Serial.println(" us");
        Serial.flush();
    }

    // array operating, avoid compiler optimize
    // the for loop array writing will not optimize,
    // it gives same situation as for loop calling ByteBuffer::Write()
    {
        uint32_t arrat_write_no_opt_start = micros();
        uint8_t arr2[TestSize];
        size_t arr_buf_size2 = 0;
        size_t arr_size2 = TestSize;
        TestArrayWrite_AvoidOptimize(arr2, arr_buf_size2, arr_size2, TestSize);
        uint32_t arrat_write_no_opt_end = micros();
        Serial.print("Array Write Avoid For loop Optimize ---- ");
        Serial.print(arrat_write_no_opt_end - arrat_write_no_opt_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use Arduino String to buffer incoming bytes
    // with operator+=
    {
        uint32_t str_plus_start = micros();
        String str1 = "";
        str1.reserve(TestSize - 1);
        TestStringPlus(str1, TestSize);
        uint32_t str_plus_end = micros();
        Serial.print("Arduino String += ---------------------- ");
        Serial.print(str_plus_end - str_plus_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use Arduino String to buffer incoming bytes
    // with method concat(char)
    {
        uint32_t str_concat_start = micros();
        String str2 = "";
        str2.reserve(TestSize - 1);
        TestStringConcat(str2, TestSize);
        uint32_t str_concat_end = micros();
        Serial.print("Arduino String concat ------------------ ");
        Serial.print(str_concat_end - str_concat_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use ByteBuffer to buffer incoming bytes
    {
        uint32_t buf_write_start = micros();
        DynamicByteBuffer buf(TestSize);
        TestDynamicByteBufferWrite(buf, TestSize);
        uint32_t buf_write_end = micros();
        Serial.print("DynamicByteBuffer write ---------------- ");
        Serial.print(buf_write_end - buf_write_start);
        Serial.println(" us");
        Serial.flush();
        str_avoid_opt1_ = buf.CString();
    }

    // use ByteBuffer to buffer incoming bytes
    // and convert to Arduino String at the end
    {
        uint32_t buf_write_and_convert_start = micros();
        DynamicByteBuffer buf(TestSize);
        TestDynamicByteBufferWriteAndToString(buf, TestSize);
        uint32_t buf_write_and_convert_end = micros();
        Serial.print("DynamicByteBuffer write and to String -- ");
        Serial.print(buf_write_and_convert_end - buf_write_and_convert_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use StaticByteBuffer to buffer incoming bytes
    {
        uint32_t staticbuf_write_start = micros();
        StaticByteBuffer<TestSize> buf;
        TestStaticByteBufferWrite(buf, TestSize);
        uint32_t staticbuf_write_end = micros();
        Serial.print("StaticByteBuffer write ----------------- ");
        Serial.print(staticbuf_write_end - staticbuf_write_start);
        Serial.println(" us");
        Serial.flush();
        str_avoid_opt_ = buf.CString();
    }

    // use StaticByteBuffer to buffer incoming bytes
    // and convert to Arduino String at the end
    {
        uint32_t staticbuf_write_and_convert_start = micros();
        StaticByteBuffer<TestSize> buf;
        TestStaticByteBufferWriteAndToString(buf, TestSize);
        uint32_t staticbuf_write_and_convert_end = micros();
        Serial.print("StaticByteBuffer write and to String --- ");
        Serial.print(staticbuf_write_and_convert_end - staticbuf_write_and_convert_start);
        Serial.println(" us");
        Serial.flush();
    }

    Serial.print("Testing write ");
    Serial.print(TestSize - 1);
    Serial.println(" char into ''Global'' Array, Arduino String and Bytebuffer.");
    Serial.flush();

    // array operating
    {
        uint32_t arrat_write_start = micros();
        size_t arr_buf_size = 0;
        size_t arr_size = TestSize;
        TestArrayWrite(global_arr, arr_buf_size, arr_size, TestSize);
        uint32_t arrat_write_end = micros();
        Serial.print("Array Write ---------------------------- ");
        Serial.print(arrat_write_end - arrat_write_start);
        Serial.println(" us");
        Serial.flush();
    }

    // array operating, avoid compiler optimize
    // the for loop array writing will not optimize,
    // it gives same situation as for loop calling ByteBuffer::Write()
    {
        uint32_t arrat_write_no_opt_start = micros();
        size_t arr_buf_size2 = 0;
        size_t arr_size2 = TestSize;
        TestArrayWrite_AvoidOptimize(global_arr, arr_buf_size2, arr_size2, TestSize);
        uint32_t arrat_write_no_opt_end = micros();
        Serial.print("Array Write Avoid For loop Optimize ---- ");
        Serial.print(arrat_write_no_opt_end - arrat_write_no_opt_start);
        Serial.println(" us");
        Serial.flush();

        for (size_t i = 0; i < TestSize; i++)
        {
            avoid_opt += global_arr[i];
        }
    }

    // use Arduino String to buffer incoming bytes
    // with operator+=
    {
        global_string = "";
        uint32_t str_plus_start = micros();
        TestStringPlus(global_string, TestSize);
        uint32_t str_plus_end = micros();
        Serial.print("Arduino String += ---------------------- ");
        Serial.print(str_plus_end - str_plus_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use Arduino String to buffer incoming bytes
    // with method concat(char)
    {
        global_string = "";
        uint32_t str_concat_start = micros();
        TestStringConcat(global_string, TestSize);
        uint32_t str_concat_end = micros();
        Serial.print("Arduino String concat ------------------ ");
        Serial.print(str_concat_end - str_concat_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use ByteBuffer to buffer incoming bytes
    {
        uint32_t buf_write_start = micros();
        TestDynamicByteBufferWrite(global_dynamin_buf, TestSize);
        uint32_t buf_write_end = micros();
        Serial.print("DynamicByteBuffer write ---------------- ");
        Serial.print(buf_write_end - buf_write_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use ByteBuffer to buffer incoming bytes
    // and convert to Arduino String at the end
    {
        global_dynamin_buf.Reset();
        uint32_t buf_write_and_convert_start = micros();
        TestDynamicByteBufferWriteAndToString(global_dynamin_buf, TestSize);
        uint32_t buf_write_and_convert_end = micros();
        Serial.print("DynamicByteBuffer write and to String -- ");
        Serial.print(buf_write_and_convert_end - buf_write_and_convert_start);
        Serial.println(" us");
        Serial.flush();
    }

    // use StaticByteBuffer to buffer incoming bytes
    {
        uint32_t staticbuf_write_start = micros();
        TestStaticByteBufferWrite(global_stataic_buf, TestSize);
        uint32_t staticbuf_write_end = micros();
        Serial.print("StaticByteBuffer write ----------------- ");
        Serial.print(staticbuf_write_end - staticbuf_write_start);
        Serial.println(" us");
        Serial.flush();
    }

    str_avoid_opt2_ = str_avoid_opt2;

    // use StaticByteBuffer to buffer incoming bytes
    // and convert to Arduino String at the end
    {
        global_stataic_buf.Reset();
        uint32_t staticbuf_write_and_convert_start = micros();
        TestStaticByteBufferWriteAndToString(global_stataic_buf, TestSize);
        uint32_t staticbuf_write_and_convert_end = micros();
        Serial.print("StaticByteBuffer write and to String --- ");
        Serial.print(staticbuf_write_and_convert_end - staticbuf_write_and_convert_start);
        Serial.println(" us");
        Serial.flush();
    }

    Serial.println("Test done.");
    Serial.flush();

    Serial.end();
    Serial.println(avoid_opt);
    Serial.println(str_avoid_opt);
    Serial.println(str_avoid_opt_);
    Serial.println(str_avoid_opt1_);
    Serial.println(str_avoid_opt2);
    Serial.println(str_avoid_opt2_);
}

void loop()
{
}

void TestArrayWrite(uint8_t *arr, size_t &buf_size, const size_t arr_size, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        if (buf_size < arr_size)
        {
            arr[buf_size] = i;
            buf_size++;
        }
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

void TestArrayWrite_AvoidOptimize(uint8_t *arr, volatile size_t &buf_size, const size_t arr_size, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        if (buf_size < arr_size)
        {
            arr[buf_size] = i;
            buf_size++;
        }
    }
    arr[writesize] = 0;
}

void TestStringPlus(String &str, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        str += (char)i;
    }
}

void TestStringConcat(String &str, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        str.concat((char)i);
    }
}

void TestDynamicByteBufferWrite(DynamicByteBuffer &buf, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
}

void TestDynamicByteBufferWriteAndToString(DynamicByteBuffer &buf, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
    str_avoid_opt = buf.CString();
}

template <size_t buf_size>
void TestStaticByteBufferWrite(StaticByteBuffer<buf_size> &buf, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
}

template <size_t buf_size>
void TestStaticByteBufferWriteAndToString(StaticByteBuffer<buf_size> &buf, const size_t size)
{
    const size_t writesize = size - 1;
    for (size_t i = 0; i < writesize; i++)
    {
        buf.Write((char)i);
    }
    str_avoid_opt2 = buf.CString();
}