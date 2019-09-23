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

#ifndef DBG_H
#define DBG_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Library version. */
#define DBG_VERSION "0.3.0"

#ifndef NDBG
/**
 * For primitive data types (int, float, etc.), strings and
 * pointers. Returns the result of given expression.
 */
#    define dbg(expr)                                   \
    _Generic((expr),                                    \
             char: dbg_char,                            \
             signed char: dbg_schar,                    \
             unsigned char: dbg_uchar,                  \
             short: dbg_short,                          \
             unsigned short: dbg_ushort,                \
             int: dbg_int,                              \
             unsigned int: dbg_uint,                    \
             long: dbg_long,                            \
             unsigned long: dbg_ulong,                  \
             long long: dbg_llong,                      \
             unsigned long long: dbg_ullong,            \
             float: dbg_float,                          \
             double: dbg_double,                        \
             bool: dbg_bool,                            \
             char *: dbg_char_p,                        \
             const char *: dbg_const_char_p,            \
             signed char *: dbg_schar_p,                \
             const signed char *: dbg_const_schar_p,    \
             unsigned char *: dbg_uchar_p,              \
             const unsigned char *: dbg_const_uchar_p,  \
             default: dbg_pointer)                      \
    (__FILE__, __LINE__, __func__, #expr, expr)

/**
 * For array of primitive data types. Returns the result of given
 * expression.
 */
#    define dbga(expr, length)                                  \
    _Generic((expr),                                            \
             short *: dbg_short_p,                              \
             const short *: dbg_const_short_p,                  \
             unsigned short *: dbg_ushort_p,                    \
             const unsigned short *: dbg_const_ushort_p,        \
             int *: dbg_int_p,                                  \
             const int *: dbg_const_int_p,                      \
             unsigned int *: dbg_uint_p,                        \
             const unsigned int *: dbg_const_uint_p,            \
             long *: dbg_long_p,                                \
             const long *: dbg_const_long_p,                    \
             unsigned long *: dbg_ulong_p,                      \
             const unsigned long *: dbg_const_ulong_p,          \
             long long *: dbg_llong_p,                          \
             const long long *: dbg_const_llong_p,              \
             unsigned long long *: dbg_ullong_p,                \
             const unsigned long long *: dbg_const_ullong_p,    \
             float *: dbg_float_p,                              \
             const float *: dbg_const_float_p,                  \
             double *: dbg_double_p,                            \
             const double *: dbg_const_double_p,                \
             bool *: dbg_bool_p,                                \
             const bool *: dbg_const_bool_p)                    \
    (__FILE__, __LINE__, __func__, #expr, expr, length)

/**
 * To force boolean true/false output. Returns the result of given
 * expression.
 */
#    define dbgb(expr)                                    \
    dbg_bool(__FILE__, __LINE__, __func__, #expr, expr)
#else
#    define dbg(expr) (expr)
#    define dbga(expr, length) (expr)
#    define dbgb(expr) (expr)
#endif

#define DBG_FUNC(name, type)                                            \
    type dbg_ ## name(const char *file_p,                               \
                      int line,                                         \
                      const char *func_p,                               \
                      const char *expr_p,                               \
                      type value);                                      \
                                                                        \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *func_p,            \
                                         const char *expr_p,            \
                                         const type *value_p,           \
                                         int length);                   \
                                                                        \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *func_p,                        \
                             const char *expr_p,                        \
                             type *value_p,                             \
                             int length)

#define DBG_FUNC_CHAR(name, type)                                       \
    type dbg_ ## name(const char *file_p,                               \
                      int line,                                         \
                      const char *func_p,                               \
                      const char *expr_p,                               \
                      type value);                                      \
                                                                        \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *func_p,            \
                                         const char *expr_p,            \
                                         const type *value_p);          \
                                                                        \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *func_p,                        \
                             const char *expr_p,                        \
                             type *value_p)

DBG_FUNC_CHAR(char, char);
DBG_FUNC_CHAR(schar, signed char);
DBG_FUNC_CHAR(uchar, unsigned char);
DBG_FUNC(short, short);
DBG_FUNC(ushort, unsigned short);
DBG_FUNC(int, int);
DBG_FUNC(uint, unsigned int);
DBG_FUNC(long, long);
DBG_FUNC(ulong, unsigned long);
DBG_FUNC(llong, long long);
DBG_FUNC(ullong, unsigned long long);
DBG_FUNC(float, float);
DBG_FUNC(double, double);
DBG_FUNC(bool, bool);

void *dbg_pointer(const char *file_p,
                  int line,
                  const char *func_p,
                  const char *expr_p,
                  void *value_p);

#endif
