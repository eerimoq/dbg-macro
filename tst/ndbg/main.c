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

TEST(dbg_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        printf("%d\n", dbg(1));
    }

    ASSERT_EQ(stdoutput, "1\n");
}

TEST(dbgb_output)
{
    CAPTURE_OUTPUT(stdoutput, stderrput) {
        printf("%d\n", dbg(1));
    }

    ASSERT_EQ(stdoutput, "1\n");
}

TEST(dbga_output)
{
    int a[3] = { 1, 2, 3 };

    CAPTURE_OUTPUT(stdoutput, stderrput) {
        printf("%d\n", dbga(a, 3)[1]);
        (void)dbga(a, 3);
    }

    ASSERT_EQ(stdoutput, "2\n");
}
