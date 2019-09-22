#include "dbg.h"
#include "narwhal.h"

#define FLF(test, line)                                                 \
    "main.c:" #line ": (_narwhal_test_function_" #test "_output) "

TEST(char_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((char)'a');
        dbg((char *)"hello");
        dbg((const char *)"hello");
    }

    ASSERT_EQ(output,
              FLF(char, 10) "(char)'a' = 97\n"
              FLF(char, 11) "(char *)\"hello\" = \"hello\"\n"
              FLF(char, 12) "(const char *)\"hello\" = \"hello\"\n");
}

TEST(schar_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((signed char)'a');
        dbg((signed char *)"hello");
        dbg((const signed char *)"hello");
    }

    ASSERT_EQ(
        output,
        FLF(schar, 24) "(signed char)'a' = 97\n"
        FLF(schar, 25) "(signed char *)\"hello\" = \"hello\"\n"
        FLF(schar, 26) "(const signed char *)\"hello\" = \"hello\"\n");
}

TEST(uchar_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((unsigned char)'a');
        dbg((unsigned char *)"hello");
        dbg((const unsigned char *)"hello");
    }

    ASSERT_EQ(output,
              FLF(uchar, 39) "(unsigned char)'a' = 97\n"
              FLF(uchar, 40) "(unsigned char *)\"hello\" = \"hello\"\n"
              FLF(uchar, 41) "(const unsigned char *)\"hello\" = \"hello\"\n");
}

TEST(short_output)
{
    short array[] = { 1, 2 };
    const short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(short, 56) "array[0] = 1\n"
              FLF(short, 57) "array = [1, 2] (length: 2)\n"
              FLF(short, 58) "const_array = [1, 2] (length: 2)\n");
}

TEST(ushort_output)
{
    unsigned short array[] = { 1, 2 };
    const unsigned short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(ushort, 73) "array[0] = 1\n"
              FLF(ushort, 74) "array = [1, 2] (length: 2)\n"
              FLF(ushort, 75) "const_array = [1, 2] (length: 2)\n");
}

TEST(int_output)
{
    int array[] = { 1, 2 };
    const int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(int, 90) "array[0] = 1\n"
              FLF(int, 91) "array = [1, 2] (length: 2)\n"
              FLF(int, 92) "const_array = [1, 2] (length: 2)\n");
}

TEST(uint_output)
{
    unsigned int array[] = { 1, 2 };
    const unsigned int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(uint, 107) "array[0] = 1\n"
              FLF(uint, 108) "array = [1, 2] (length: 2)\n"
              FLF(uint, 109) "const_array = [1, 2] (length: 2)\n");
}

TEST(long_output)
{
    long array[] = { 1, 2 };
    const long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(long, 124) "array[0] = 1\n"
              FLF(long, 125) "array = [1, 2] (length: 2)\n"
              FLF(long, 126) "const_array = [1, 2] (length: 2)\n");
}

TEST(ulong_output)
{
    unsigned long array[] = { 1, 2 };
    const unsigned long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(ulong, 141) "array[0] = 1\n"
              FLF(ulong, 142) "array = [1, 2] (length: 2)\n"
              FLF(ulong, 143) "const_array = [1, 2] (length: 2)\n");
}

TEST(llong_output)
{
    long long array[] = { 1, 2 };
    const long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(llong, 158) "array[0] = 1\n"
              FLF(llong, 159) "array = [1, 2] (length: 2)\n"
              FLF(llong, 160) "const_array = [1, 2] (length: 2)\n");
}

TEST(ullong_output)
{
    unsigned long long array[] = { 1, 2 };
    const unsigned long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(ullong, 175) "array[0] = 1\n"
              FLF(ullong, 176) "array = [1, 2] (length: 2)\n"
              FLF(ullong, 177) "const_array = [1, 2] (length: 2)\n");
}

TEST(float_output)
{
    float array[] = { 1, 2 };
    const float const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(float, 192) "array[0] = 1.000000\n"
              FLF(float, 193) "array = [1.000000, 2.000000] (length: 2)\n"
              FLF(float, 194) "const_array = [1.000000, 2.000000] (length: 2)\n");
}

TEST(double_output)
{
    double array[] = { 1, 2 };
    const double const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(output,
              FLF(double, 209) "array[0] = 1.000000\n"
              FLF(double, 210) "array = [1.000000, 2.000000] (length: 2)\n"
              FLF(double, 211) "const_array = [1.000000, 2.000000] (length: 2)\n");
}

TEST(bool_output)
{
    bool array[] = { true, false };
    const bool const_array[] = { true, false };

    CAPTURE_OUTPUT(output) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
        dbgb(1);
    }

    ASSERT_EQ(output,
              FLF(bool, 226) "array[0] = true\n"
              FLF(bool, 227) "array = [true, false] (length: 2)\n"
              FLF(bool, 228) "const_array = [true, false] (length: 2)\n"
              FLF(bool, 229) "1 = true\n");
}

TEST(pointer_output)
{
    int a = 1;

    CAPTURE_OUTPUT(output) {
        dbg(&a);
    }

    ASSERT_SUBSTRING(output, FLF(pointer, 244) "&a = 0x");
}

/* To test that the expression is evaluated once. */
static char char_once(char value)
{
    static bool called = false;

    if (called) {
        exit(1);
    }

    called = true;

    return (value);
}

TEST(char_logic)
{
    ASSERT_EQ(dbg(char_once('a')), 'a');
}

TEST(schar_logic)
{
    ASSERT_EQ(dbg((signed char)'a'), 'a');
}

TEST(uchar_logic)
{
    ASSERT_EQ(dbg((unsigned char)'a'), 'a');
}

TEST(short_logic)
{
    ASSERT_EQ(dbg((short)1), 1);
}

TEST(ushort_logic)
{
    ASSERT_EQ(dbg((unsigned short)1), 1);
}

TEST(int_logic)
{
    ASSERT_EQ(dbg((int)1), 1);
}

TEST(uint_logic)
{
    ASSERT_EQ(dbg((unsigned int)1), 1);
}

TEST(long_logic)
{
    ASSERT_EQ(dbg((long)1), 1);
}

TEST(ulong_logic)
{
    ASSERT_EQ(dbg((unsigned long)1), 1);
}

TEST(llong_logic)
{
    ASSERT_EQ(dbg((long long)1), 1);
}

TEST(ullong_logic)
{
    ASSERT_EQ(dbg((unsigned long long)1), 1);
}

TEST(float_logic)
{
    ASSERT_EQ(dbg((float)1.0), 1.0);
}

TEST(double_logic)
{
    ASSERT_EQ(dbg((double)1.0), 1.0);
}

TEST(bool_logic)
{
    ASSERT_EQ(dbg(true), true);
}

int main()
{
    return (RUN_TESTS(
                char_output,
                schar_output,
                uchar_output,
                short_output,
                ushort_output,
                int_output,
                uint_output,
                long_output,
                ulong_output,
                llong_output,
                ullong_output,
                float_output,
                double_output,
                bool_output,
                pointer_output,
                char_logic,
                schar_logic,
                uchar_logic,
                short_logic,
                ushort_logic,
                int_logic,
                uint_logic,
                long_logic,
                ulong_logic,
                llong_logic,
                ullong_logic,
                float_logic,
                double_logic,
                bool_logic
            ));
}
