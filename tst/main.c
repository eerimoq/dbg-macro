/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * This file is part of the dbg-macro project.
 */

#include "dbg.h"
#include "errno.h"
#include "nala.h"
#define FLF(test, line)                         \
    "main.c:" #line ": (" #test "_output) "

TEST(char_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg((char)'a');
        dbg((char *)"hello");
        dbg((const char *)"hello");
    }

    ASSERT_EQ(stderrput,
              FLF(char, 38) "(char)'a' = 97\n"
              FLF(char, 39) "(char *)\"hello\" = \"hello\"\n"
              FLF(char, 40) "(const char *)\"hello\" = \"hello\"\n");
}

TEST(schar_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg((signed char)'a');
        dbg((signed char *)"hello");
        dbg((const signed char *)"hello");
    }

    ASSERT_EQ(
        stderrput,
        FLF(schar, 52) "(signed char)'a' = 97\n"
        FLF(schar, 53) "(signed char *)\"hello\" = \"hello\"\n"
        FLF(schar, 54) "(const signed char *)\"hello\" = \"hello\"\n");
}

TEST(uchar_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg((unsigned char)'a');
        dbg((unsigned char *)"hello");
        dbg((const unsigned char *)"hello");
    }

    ASSERT_EQ(stderrput,
              FLF(uchar, 67) "(unsigned char)'a' = 97\n"
              FLF(uchar, 68) "(unsigned char *)\"hello\" = \"hello\"\n"
              FLF(uchar, 69) "(const unsigned char *)\"hello\" = \"hello\"\n");
}

TEST(short_output)
{
    short array[] = { 1, 2 };
    const short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(short, 84) "array[0] = 1 (0x1)\n"
              FLF(short, 85) "array = [1, 2] (length: 2)\n"
              FLF(short, 86) "const_array = [1, 2] (length: 2)\n");
}

TEST(ushort_output)
{
    unsigned short array[] = { 1, 2 };
    const unsigned short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(ushort, 101) "array[0] = 1 (0x1)\n"
              FLF(ushort, 102) "array = [1, 2] (length: 2)\n"
              FLF(ushort, 103) "const_array = [1, 2] (length: 2)\n");
}

TEST(int_output)
{
    int array[] = { 1, 2 };
    const int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(int, 118) "array[0] = 1 (0x1)\n"
              FLF(int, 119) "array = [1, 2] (length: 2)\n"
              FLF(int, 120) "const_array = [1, 2] (length: 2)\n");
}

TEST(uint_output)
{
    unsigned int array[] = { 1, 2 };
    const unsigned int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(uint, 135) "array[0] = 1 (0x1)\n"
              FLF(uint, 136) "array = [1, 2] (length: 2)\n"
              FLF(uint, 137) "const_array = [1, 2] (length: 2)\n");
}

TEST(long_output)
{
    long array[] = { 1, 2 };
    const long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(long, 152) "array[0] = 1 (0x1)\n"
              FLF(long, 153) "array = [1, 2] (length: 2)\n"
              FLF(long, 154) "const_array = [1, 2] (length: 2)\n");
}

TEST(ulong_output)
{
    unsigned long array[] = { 1, 2 };
    const unsigned long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(ulong, 169) "array[0] = 1 (0x1)\n"
              FLF(ulong, 170) "array = [1, 2] (length: 2)\n"
              FLF(ulong, 171) "const_array = [1, 2] (length: 2)\n");
}

TEST(llong_output)
{
    long long array[] = { 1, 2 };
    const long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(llong, 186) "array[0] = 1 (0x1)\n"
              FLF(llong, 187) "array = [1, 2] (length: 2)\n"
              FLF(llong, 188) "const_array = [1, 2] (length: 2)\n");
}

TEST(ullong_output)
{
    unsigned long long array[] = { 1, 2 };
    const unsigned long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(ullong, 203) "array[0] = 1 (0x1)\n"
              FLF(ullong, 204) "array = [1, 2] (length: 2)\n"
              FLF(ullong, 205) "const_array = [1, 2] (length: 2)\n");
}

TEST(float_output)
{
    float array[] = { 1, 2 };
    const float const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(float, 220) "array[0] = 1.000000\n"
              FLF(float, 221) "array = [1.000000, 2.000000] (length: 2)\n"
              FLF(float, 222) "const_array = [1.000000, 2.000000] (length: 2)\n");
}

TEST(double_output)
{
    double array[] = { 1, 2 };
    const double const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
    }

    ASSERT_EQ(stderrput,
              FLF(double, 237) "array[0] = 1.000000\n"
              FLF(double, 238) "array = [1.000000, 2.000000] (length: 2)\n"
              FLF(double, 239) "const_array = [1.000000, 2.000000] (length: 2)\n");
}

TEST(bool_output)
{
    bool array[] = { true, false };
    const bool const_array[] = { true, false };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(array[0]);
        dbga(array, 2);
        dbga(const_array, 2);
        dbgb(1);
    }

    ASSERT_EQ(stderrput,
              FLF(bool, 254) "array[0] = true\n"
              FLF(bool, 255) "array = [true, false] (length: 2)\n"
              FLF(bool, 256) "const_array = [true, false] (length: 2)\n"
              FLF(bool, 257) "1 = true\n");
}

TEST(pointer_output)
{
    int a = 1;

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(&a);
    }

    ASSERT_SUBSTRING(stderrput, FLF(pointer, 272) "&a = 0x");
}

TEST(char_hexdump_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh((char *)"hello", 6);
        dbgh((const char *)"hello", 6);
    }

    ASSERT_EQ(
        stderrput,
        FLF(char_hexdump, 281) "(char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n"
        FLF(char_hexdump, 282) "(const char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n");
}

TEST(schar_hexdump_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh((signed char *)"hello", 6);
        dbgh((const signed char *)"hello", 6);
    }

    ASSERT_EQ(
        stderrput,
        FLF(schar_hexdump, 296) "(signed char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n"
        FLF(schar_hexdump, 297) "(const signed char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n");
}

TEST(uchar_hexdump_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh((unsigned char *)"hello", 6);
        dbgh((const unsigned char *)"hello", 6);
    }

    ASSERT_EQ(
        stderrput,
        FLF(uchar_hexdump, 311) "(unsigned char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n"
        FLF(uchar_hexdump, 312) "(const unsigned char *)\"hello\" (size: 6):\n"
        "    00000000: 68 65 6c 6c 6f 00                                'hello.'\n");
}

TEST(short_hexdump_output)
{
    short array[] = { 1, 2 };
    const short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(short_hexdump, 329) "array (size: 4):\n"
        "    00000000: 01 00 02 00                                      '....'\n"
        FLF(short_hexdump, 330) "const_array (size: 4):\n"
        "    00000000: 01 00 02 00                                      '....'\n");
}

TEST(ushort_hexdump_output)
{
    unsigned short array[] = { 1, 2 };
    const unsigned short const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(ushort_hexdump, 347) "array (size: 4):\n"
        "    00000000: 01 00 02 00                                      '....'\n"
        FLF(ushort_hexdump, 348) "const_array (size: 4):\n"
        "    00000000: 01 00 02 00                                      '....'\n");
}

TEST(int_hexdump_output)
{
    int array[] = { 1, 2 };
    const int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(int_hexdump, 365) "array (size: 8):\n"
        "    00000000: 01 00 00 00 02 00 00 00                          '........'\n"
        FLF(int_hexdump, 366) "const_array (size: 8):\n"
        "    00000000: 01 00 00 00 02 00 00 00                          '........'\n");
}

TEST(uint_hexdump_output)
{
    unsigned int array[] = { 1, 2 };
    const unsigned int const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(uint_hexdump, 383) "array (size: 8):\n"
        "    00000000: 01 00 00 00 02 00 00 00                          '........'\n"
        FLF(uint_hexdump, 384) "const_array (size: 8):\n"
        "    00000000: 01 00 00 00 02 00 00 00                          '........'\n");
}

TEST(long_hexdump_output)
{
    long array[] = { 1, 2 };
    const long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(long_hexdump, 401) "array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n"
        FLF(long_hexdump, 402) "const_array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n");
}

TEST(ulong_hexdump_output)
{
    unsigned long array[] = { 1, 2 };
    const unsigned long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(ulong_hexdump, 419) "array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n"
        FLF(ulong_hexdump, 420) "const_array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n");
}

TEST(llong_hexdump_output)
{
    long long array[] = { 1, 2 };
    const long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(llong_hexdump, 437) "array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n"
        FLF(llong_hexdump, 438) "const_array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n");
}

TEST(ullong_hexdump_output)
{
    unsigned long long array[] = { 1, 2 };
    const unsigned long long const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(ullong_hexdump, 455) "array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n"
        FLF(ullong_hexdump, 456) "const_array (size: 16):\n"
        "    00000000: 01 00 00 00 00 00 00 00  02 00 00 00 00 00 00 00 '................'\n");
}

TEST(float_hexdump_output)
{
    float array[] = { 1, 2 };
    const float const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(float_hexdump, 473) "array (size: 8):\n"
        "    00000000: 00 00 80 3f 00 00 00 40                          '...?...@'\n"
        FLF(float_hexdump, 474) "const_array (size: 8):\n"
        "    00000000: 00 00 80 3f 00 00 00 40                          '...?...@'\n");
}

TEST(double_hexdump_output)
{
    double array[] = { 1, 2 };
    const double const_array[] = { 1, 2 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array, sizeof(array));
        dbgh(const_array, sizeof(const_array));
    }

    ASSERT_EQ(
        stderrput,
        FLF(double_hexdump, 491) "array (size: 16):\n"
        "    00000000: 00 00 00 00 00 00 f0 3f  00 00 00 00 00 00 00 40 '.......?.......@'\n"
        FLF(double_hexdump, 492) "const_array (size: 16):\n"
        "    00000000: 00 00 00 00 00 00 f0 3f  00 00 00 00 00 00 00 40 '.......?.......@'\n");
}

TEST(void_p_hexdump_output)
{
    int a = 1;

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh((void *)&a, sizeof(a));
        dbgh((const void *)&a, sizeof(a));
    }

    ASSERT_EQ(
        stderrput,
        FLF(void_p_hexdump, 508) "(void *)&a (size: 4):\n"
        "    00000000: 01 00 00 00                                      '....'\n"
        FLF(void_p_hexdump, 509) "(const void *)&a (size: 4):\n"
        "    00000000: 01 00 00 00                                      '....'\n");
}

TEST(hexdump_lengths_output)
{
    char array_1[] = { 1 };
    char array_7[] = { 1, 2, 3, 4, 5, 6, 7 };
    char array_8[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    char array_9[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(array_1, 0);
        dbgh(array_1, sizeof(array_1));
        dbgh(array_7, sizeof(array_7));
        dbgh(array_8, sizeof(array_8));
        dbgh(array_9, sizeof(array_9));
    }

    ASSERT_EQ(
        stderrput,
        FLF(hexdump_lengths, 528) "array_1 (size: 0):\n"
        FLF(hexdump_lengths, 529) "array_1 (size: 1):\n"
        "    00000000: 01                                               '.'\n"
        FLF(hexdump_lengths, 530) "array_7 (size: 7):\n"
        "    00000000: 01 02 03 04 05 06 07                             '.......'\n"
        FLF(hexdump_lengths, 531) "array_8 (size: 8):\n"
        "    00000000: 01 02 03 04 05 06 07 08                          '........'\n"
        FLF(hexdump_lengths, 532) "array_9 (size: 9):\n"
        "    00000000: 01 02 03 04 05 06 07 08  09                      '.........'\n");
}

TEST(error_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbge(-EAGAIN);
        dbge(0);
        dbge(EAGAIN);
    }

    ASSERT_EQ(stderrput,
              FLF(error, 551) "-EAGAIN = -11 (Resource temporarily unavailable)\n"
              FLF(error, 552) "0 = 0 (0x0)\n"
              FLF(error, 553) "EAGAIN = 11 (0xb)\n");
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
    char v = 1;

    ASSERT_EQ(dbg(char_once('a')), 'a');
    ASSERT_EQ(dbgh(&v, sizeof(v)), &v);
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

TEST(backtrace_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgbt();
    }

    ASSERT_SUBSTRING(
        stdoutput,
        "main.c:652: (backtrace_output) "
        "Backtrace (most recent call last):");
}
