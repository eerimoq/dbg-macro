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
#include "nala.h"

#define FLF(test, line)                                 \
    "\x1b[02mmain.c:" #line ": (" #test "_output) "     \
    "\x1b[0m\x1b[36m\x1b[1m"

TEST(dbg_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbg(1);
    }

    ASSERT_EQ(stderrput, FLF(dbg, 39) "1\x1b[0m = \x1b[01m1 (0x1)\n\x1b[0m");
}

TEST(dbgb_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgb(1);
    }

    ASSERT_EQ(stderrput, FLF(dbgb, 48) "1\x1b[0m = \x1b[01mtrue\n\x1b[0m");
}

TEST(dbga_output)
{
    int a[3] = { 1, 2, 3 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbga(a, 3);
    }

    ASSERT_EQ(stderrput,
              FLF(dbga, 59) "a\x1b[0m = \x1b[01m[1, 2, 3] (length: 3)\n\x1b[0m");
}

TEST(dbgh_output)
{
    uint8_t a[3] = { 1, 2, 3 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        dbgh(a, sizeof(a));
    }

    ASSERT_EQ(stderrput,
              FLF(dbgh, 71) "a \x1b[0m(size: 3):\n\x1b[01m"
              "    00000000: 01 02 03                                         '...'\n"
              "\x1b[0m");
}
