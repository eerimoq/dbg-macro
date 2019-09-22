#include "dbg.h"
#include "narwhal.h"

TEST(char_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((char)'a');
        dbg((char *)"hello");
        dbg((const char *)"hello");
    }

    ASSERT_EQ(output,
              "main.c:7: (char)'a' = 97\n"
              "main.c:8: (char *)\"hello\" = \"hello\"\n"
              "main.c:9: (const char *)\"hello\" = \"hello\"\n");
}

TEST(schar_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((signed char)'a');
        dbg((signed char *)"hello");
        dbg((const signed char *)"hello");
    }

    ASSERT_EQ(output,
              "main.c:21: (signed char)'a' = 97\n"
              "main.c:22: (signed char *)\"hello\" = \"hello\"\n"
              "main.c:23: (const signed char *)\"hello\" = \"hello\"\n");
}

TEST(uchar_output)
{
    CAPTURE_OUTPUT(output) {
        dbg((unsigned char)'a');
        dbg((unsigned char *)"hello");
        dbg((const unsigned char *)"hello");
    }

    ASSERT_EQ(output,
              "main.c:35: (unsigned char)'a' = 97\n"
              "main.c:36: (unsigned char *)\"hello\" = \"hello\"\n"
              "main.c:37: (const unsigned char *)\"hello\" = \"hello\"\n");
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
              "main.c:52: array[0] = 1\n"
              "main.c:53: array = [1, 2] (length: 2)\n"
              "main.c:54: const_array = [1, 2] (length: 2)\n");
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
              "main.c:69: array[0] = 1\n"
              "main.c:70: array = [1, 2] (length: 2)\n"
              "main.c:71: const_array = [1, 2] (length: 2)\n");
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
              "main.c:86: array[0] = 1\n"
              "main.c:87: array = [1, 2] (length: 2)\n"
              "main.c:88: const_array = [1, 2] (length: 2)\n");
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
              "main.c:103: array[0] = 1\n"
              "main.c:104: array = [1, 2] (length: 2)\n"
              "main.c:105: const_array = [1, 2] (length: 2)\n");
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
              "main.c:120: array[0] = 1\n"
              "main.c:121: array = [1, 2] (length: 2)\n"
              "main.c:122: const_array = [1, 2] (length: 2)\n");
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
              "main.c:137: array[0] = 1\n"
              "main.c:138: array = [1, 2] (length: 2)\n"
              "main.c:139: const_array = [1, 2] (length: 2)\n");
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
              "main.c:154: array[0] = 1\n"
              "main.c:155: array = [1, 2] (length: 2)\n"
              "main.c:156: const_array = [1, 2] (length: 2)\n");
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
              "main.c:171: array[0] = 1\n"
              "main.c:172: array = [1, 2] (length: 2)\n"
              "main.c:173: const_array = [1, 2] (length: 2)\n");
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
              "main.c:188: array[0] = 1.000000\n"
              "main.c:189: array = [1.000000, 2.000000] (length: 2)\n"
              "main.c:190: const_array = [1.000000, 2.000000] (length: 2)\n");
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
              "main.c:205: array[0] = 1.000000\n"
              "main.c:206: array = [1.000000, 2.000000] (length: 2)\n"
              "main.c:207: const_array = [1.000000, 2.000000] (length: 2)\n");
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
              "main.c:222: array[0] = true\n"
              "main.c:223: array = [true, false] (length: 2)\n"
              "main.c:224: const_array = [true, false] (length: 2)\n"
              "main.c:225: 1 = true\n");
}

TEST(char_logic)
{
    ASSERT_EQ(dbg((char)'a'), 'a');
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
