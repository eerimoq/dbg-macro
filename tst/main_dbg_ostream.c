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

#include <stdio.h>
#include "dbg.h"
#include "nala.h"

#define FLF(test, line)                                         \
    "\x1b[02mmain_dbg_ostream.c:" #line ": (" #test "_output) " \
    "\x1b[0m\x1b[36m\x1b[1m"

FILE *my_ostream_p;

TEST(dbg_output)
{
    char output[1024];
    size_t size;

    my_ostream_p = fopen("test_dbg_ostream.txt", "w+");
    ASSERT_NE(my_ostream_p, NULL);
    dbg(1);
    ASSERT_EQ(fseek(my_ostream_p, 0, SEEK_SET), 0);
    size = fread(&output[0], 1, 1024, my_ostream_p);
    ASSERT_GT(size, 0);
    ASSERT_LT(size, 1024);
    output[size] = '\0';
    ASSERT_EQ((char *)output, FLF(dbg, 46) "1\x1b[0m = \x1b[01m1 (0x1)\n\x1b[0m");
}
