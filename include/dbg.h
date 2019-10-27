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
#include <stdio.h>
#include <ctype.h>

/* Library version. */
#define DBG_VERSION "0.9.0"

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

/**
 * Hexdump of given size at given address. Returns the result of given
 * expression.
 */
#    define dbgh(expr, size)                                            \
    _Generic((expr),                                                    \
             char *: dbg_hexdump_char_p,                                \
             const char *: dbg_hexdump_const_char_p,                    \
             signed char *: dbg_hexdump_schar_p,                        \
             const signed char *: dbg_hexdump_const_schar_p,            \
             unsigned char *: dbg_hexdump_uchar_p,                      \
             const unsigned char *: dbg_hexdump_const_uchar_p,          \
             short *: dbg_hexdump_short_p,                              \
             const short *: dbg_hexdump_const_short_p,                  \
             unsigned short *: dbg_hexdump_ushort_p,                    \
             const unsigned short *: dbg_hexdump_const_ushort_p,        \
             int *: dbg_hexdump_int_p,                                  \
             const int *: dbg_hexdump_const_int_p,                      \
             unsigned int *: dbg_hexdump_uint_p,                        \
             const unsigned int *: dbg_hexdump_const_uint_p,            \
             long *: dbg_hexdump_long_p,                                \
             const long *: dbg_hexdump_const_long_p,                    \
             unsigned long *: dbg_hexdump_ulong_p,                      \
             const unsigned long *: dbg_hexdump_const_ulong_p,          \
             long long *: dbg_hexdump_llong_p,                          \
             const long long *: dbg_hexdump_const_llong_p,              \
             unsigned long long *: dbg_hexdump_ullong_p,                \
             const unsigned long long *: dbg_hexdump_const_ullong_p,    \
             float *: dbg_hexdump_float_p,                              \
             const float *: dbg_hexdump_const_float_p,                  \
             double *: dbg_hexdump_double_p,                            \
             const double *: dbg_hexdump_const_double_p,                \
             void *: dbg_hexdump_p,                                     \
             const void *: dbg_hexdump_const_p)                         \
    (__FILE__, __LINE__, __func__, #expr, expr, size)
#else
#    define dbg(expr) (expr)
#    define dbga(expr, length) (expr)
#    define dbgb(expr) (expr)
#    define dbgh(expr, size) (expr)
#endif

/* Colorful output selection. */
#ifndef DBG_NCOLOR
#    define DBG_LOC "\x1b[02m"
#    define DBG_EXPR "\x1b[0m\x1b[36m\x1b[1m"
#    define DBG_VALUE "\x1b[01m"
#    define DBG_RESET "\x1b[0m"
#    define DBG_FORMAT(format)                          \
    DBG_LOC "%s:%d: (%s) " DBG_EXPR "%s" DBG_RESET      \
    " = " DBG_VALUE format "\n" DBG_RESET
#    define DBG_FORMAT_HEX(format, hexformat)                   \
    DBG_LOC "%s:%d: (%s) " DBG_EXPR "%s" DBG_RESET              \
    " = " DBG_VALUE format " (0x" hexformat ")\n" DBG_RESET
#    define DBG_FORMAT_ARRAY_BEGIN                                      \
    DBG_LOC "%s:%d: (%s) " DBG_EXPR "%s" DBG_RESET " = " DBG_VALUE "["
#    define DBG_FORMAT_ARRAY_END   "] (length: %u)\n" DBG_RESET
#    define DBG_FORMAT_HEXDUMP_BEGIN                    \
    DBG_LOC "%s:%d: (%s) " DBG_EXPR "%s " DBG_RESET "(size: %u):\n" DBG_VALUE
#    define DBG_FORMAT_HEXDUMP_END DBG_RESET
#else
#    define DBG_FORMAT(format)     "%s:%d: (%s) %s = " format "\n"
#    define DBG_FORMAT_HEX(format, hexformat)           \
    "%s:%d: (%s) %s = " format " (0x" hexformat ")\n"
#    define DBG_FORMAT_ARRAY_BEGIN "%s:%d: (%s) %s = ["
#    define DBG_FORMAT_ARRAY_END   "] (length: %u)\n"
#    define DBG_FORMAT_HEXDUMP_BEGIN "%s:%d: (%s) %s (size: %u):\n"
#endif

/* Custom output stream. */
#ifdef DBG_OSTREAM
extern FILE *DBG_OSTREAM;
#else
#    define DBG_OSTREAM stderr
#endif

#define DBG_FUNC_CONST_P(name, type, format)                            \
    static inline const type *dbg_const_ ## name ## _p(                 \
        const char *file_p,                                             \
        int line,                                                       \
        const char *func_p,                                             \
        const char *expr_p,                                             \
        const type *value_p,                                            \
        int length)                                                     \
    {                                                                   \
        int i;                                                          \
        char *delim_p;                                                  \
                                                                        \
        fprintf(DBG_OSTREAM,                                            \
                DBG_FORMAT_ARRAY_BEGIN,                                 \
                file_p,                                                 \
                line,                                                   \
                func_p,                                                 \
                expr_p);                                                \
        delim_p = "";                                                   \
                                                                        \
        for (i = 0; i < length; i++) {                                  \
            fprintf(DBG_OSTREAM, "%s" format, delim_p, value_p[i]);     \
            delim_p = ", ";                                             \
        }                                                               \
                                                                        \
        fprintf(DBG_OSTREAM, DBG_FORMAT_ARRAY_END, length);             \
                                                                        \
        return (value_p);                                               \
    }

#define DBG_FUNC_P(name, type, format)                          \
    static inline type *dbg_ ## name ## _p(const char *file_p,  \
                                           int line,            \
                                           const char *func_p,  \
                                           const char *expr_p,  \
                                           type *value_p,       \
                                           int length)          \
    {                                                           \
        dbg_const_ ## name ## _p(file_p,                        \
                                 line,                          \
                                 func_p,                        \
                                 expr_p,                        \
                                 value_p,                       \
                                 length);                       \
                                                                \
        return (value_p);                                       \
    }

#define DBG_FUNC_HEXDUMP_CONST_P(name, type)                    \
    static inline const type *dbg_hexdump_const_ ## name ## _p( \
        const char *file_p,                                     \
        int line,                                               \
        const char *func_p,                                     \
        const char *expr_p,                                     \
        const type *value_p,                                    \
        size_t size)                                            \
    {                                                           \
        dbg_hexdump(file_p,                                     \
                    line,                                       \
                    func_p,                                     \
                    expr_p,                                     \
                    (const void *)value_p,                      \
                    size);                                      \
                                                                \
        return (value_p);                                       \
    }

#define DBG_FUNC_HEXDUMP_P(name, type)                                  \
    static inline type *dbg_hexdump_ ## name ## _p(const char *file_p,  \
                                                   int line,            \
                                                   const char *func_p,  \
                                                   const char *expr_p,  \
                                                   type *value_p,       \
                                                   size_t size)         \
    {                                                                   \
        dbg_hexdump_const_ ## name ## _p(file_p,                        \
                                         line,                          \
                                         func_p,                        \
                                         expr_p,                        \
                                         value_p,                       \
                                         size);                         \
                                                                        \
        return (value_p);                                               \
    }

#define DBG_FUNC(name, type, format)                    \
    static inline type dbg_ ## name(const char *file_p, \
                                    int line,           \
                                    const char *func_p, \
                                    const char *expr_p, \
                                    type value)         \
    {                                                   \
        fprintf(DBG_OSTREAM,                            \
                DBG_FORMAT(format),                     \
                file_p,                                 \
                line,                                   \
                func_p,                                 \
                expr_p,                                 \
                value);                                 \
                                                        \
        return (value);                                 \
    }                                                   \
    DBG_FUNC_CONST_P(name, type, format)                \
    DBG_FUNC_P(name, type, format)                      \
    DBG_FUNC_HEXDUMP_CONST_P(name, type)                \
    DBG_FUNC_HEXDUMP_P(name, type)

#define DBG_FUNC_HEX(name, type, format, hexformat)     \
    static inline type dbg_ ## name(const char *file_p, \
                                    int line,           \
                                    const char *func_p, \
                                    const char *expr_p, \
                                    type value)         \
    {                                                   \
        fprintf(DBG_OSTREAM,                            \
                DBG_FORMAT_HEX(format, hexformat),      \
                file_p,                                 \
                line,                                   \
                func_p,                                 \
                expr_p,                                 \
                value,                                  \
                value);                                 \
                                                        \
        return (value);                                 \
    }                                                   \
    DBG_FUNC_CONST_P(name, type, format)                \
    DBG_FUNC_P(name, type, format)                      \
    DBG_FUNC_HEXDUMP_CONST_P(name, type)                \
    DBG_FUNC_HEXDUMP_P(name, type)

#define DBG_FUNC_CHAR_CONST_P(name, type)               \
    static inline const type *dbg_const_ ## name ## _p( \
        const char *file_p,                             \
        int line,                                       \
        const char *func_p,                             \
        const char *expr_p,                             \
        const type *value_p)                            \
    {                                                   \
        fprintf(DBG_OSTREAM,                            \
                DBG_FORMAT("\"%s\""),                   \
                file_p,                                 \
                line,                                   \
                func_p,                                 \
                expr_p,                                 \
                value_p);                               \
                                                        \
        return (value_p);                               \
    }

#define DBG_FUNC_CHAR_P(name, type)                                     \
    static inline type *dbg_ ## name ## _p(const char *file_p,          \
                                           int line,                    \
                                           const char *func_p,          \
                                           const char *expr_p,          \
                                           type *value_p)               \
    {                                                                   \
        dbg_const_ ## name ## _p(file_p, line, func_p, expr_p, value_p); \
                                                                        \
        return (value_p);                                               \
    }

#define DBG_FUNC_CHAR(name, type, format)               \
    static inline type dbg_ ## name(const char *file_p, \
                                    int line,           \
                                    const char *func_p, \
                                    const char *expr_p, \
                                    type value)         \
    {                                                   \
        fprintf(DBG_OSTREAM,                            \
                DBG_FORMAT(format),                     \
                file_p,                                 \
                line,                                   \
                func_p,                                 \
                expr_p,                                 \
                value);                                 \
                                                        \
        return (value);                                 \
    }                                                   \
    DBG_FUNC_CHAR_CONST_P(name, type)                   \
    DBG_FUNC_CHAR_P(name, type)                         \
    DBG_FUNC_HEXDUMP_CONST_P(name, type)                \
    DBG_FUNC_HEXDUMP_P(name, type)

static inline const char *dbg_format_bool(bool value)
{
    return (value ? "true" : "false");
}

static inline bool dbg_bool(const char *file_p,
              int line,
              const char *func_p,
              const char *expr_p,
              bool value)
{
    fprintf(DBG_OSTREAM,
            DBG_FORMAT("%s"),
            file_p,
            line,
            func_p,
            expr_p,
            dbg_format_bool(value));

    return (value);
}

static inline const bool *dbg_const_bool_p(const char *file_p,
                             int line,
                             const char *func_p,
                             const char *expr_p,
                             const bool *value_p,
                             int length)
{
    int i;
    char *delim_p;

    fprintf(DBG_OSTREAM, DBG_FORMAT_ARRAY_BEGIN, file_p, line, func_p, expr_p);
    delim_p = "";

    for (i = 0; i < length; i++) {
        fprintf(DBG_OSTREAM, "%s%s", delim_p, dbg_format_bool(value_p[i]));
        delim_p = ", ";
    }

    fprintf(DBG_OSTREAM, DBG_FORMAT_ARRAY_END, length);

    return (value_p);
}

static inline bool *dbg_bool_p(const char *file_p,
                               int line,
                               const char *func_p,
                               const char *expr_p,
                               bool *value_p,
                               int length)
{
    (void)dbg_const_bool_p(file_p, line, func_p, expr_p, value_p, length);

    return (value_p);
}

static inline void *dbg_pointer(const char *file_p,
                                int line,
                                const char *func_p,
                                const char *expr_p,
                                void *value_p)
{
    fprintf(DBG_OSTREAM, DBG_FORMAT("%p"), file_p, line, func_p, expr_p, value_p);

    return (value_p);
}

static inline void dbg_print_ascii(const uint8_t *buf_p, size_t size)
{
    size_t i;

    if (size < 8) {
        fprintf(DBG_OSTREAM, " ");
    }

    for (i = 0; i < 16 - size; i++) {
        fprintf(DBG_OSTREAM, "   ");
    }

    fprintf(DBG_OSTREAM, "'");

    for (i = 0; i < size; i++) {
        fprintf(DBG_OSTREAM, "%c", isprint((int)buf_p[i]) ? buf_p[i] : '.');
    }

    fprintf(DBG_OSTREAM, "'");
}

static inline void dbg_hexdump(const char *file_p,
                               int line,
                               const char *func_p,
                               const char *expr_p,
                               const void *buf_p,
                               size_t size)
{
    int pos;
    const uint8_t *u8_buf_p;

    u8_buf_p = buf_p;
    pos = 0;

    fprintf(DBG_OSTREAM,
            DBG_FORMAT_HEXDUMP_BEGIN,
            file_p,
            line,
            func_p,
            expr_p,
            (int)size);

    while (size > 0) {
        if ((pos % 16) == 0) {
            fprintf(DBG_OSTREAM, "    %08x: ", pos);
        }

        fprintf(DBG_OSTREAM, "%02x ", u8_buf_p[pos] & 0xff);

        if ((pos % 16) == 7) {
            fprintf(DBG_OSTREAM, " ");
        }

        if ((pos % 16) == 15) {
            dbg_print_ascii(&u8_buf_p[pos - 15], 16);
            fprintf(DBG_OSTREAM, "\n");
        }

        pos++;
        size--;
    }

    if ((pos % 16) != 0) {
        dbg_print_ascii(&u8_buf_p[pos - (pos % 16)], pos % 16);
        fprintf(DBG_OSTREAM, "\n");
    }

#ifdef DBG_FORMAT_HEXDUMP_END
    fprintf(DBG_OSTREAM, DBG_FORMAT_HEXDUMP_END);
#endif
}

static inline void *dbg_hexdump_p(const char *file_p,
                                  int line,
                                  const char *func_p,
                                  const char *expr_p,
                                  void *buf_p,
                                  size_t size)
{
    dbg_hexdump(file_p, line, func_p, expr_p, buf_p, size);

    return (buf_p);
}

static inline const void *dbg_hexdump_const_p(const char *file_p,
                                              int line,
                                              const char *func_p,
                                              const char *expr_p,
                                              const void *buf_p,
                                              size_t size)
{
    dbg_hexdump(file_p, line, func_p, expr_p, buf_p, size);

    return (buf_p);
}

DBG_FUNC_CHAR(char, char, "%hhi")
DBG_FUNC_CHAR(schar, signed char, "%hhi")
DBG_FUNC_CHAR(uchar, unsigned char, "%hhu")
DBG_FUNC_HEX(short, short, "%hi", "%hx")
DBG_FUNC_HEX(ushort, unsigned short, "%hu", "%hx")
DBG_FUNC_HEX(int, int, "%d", "%x")
DBG_FUNC_HEX(uint, unsigned int, "%u", "%x")
DBG_FUNC_HEX(long, long, "%ld", "%lx")
DBG_FUNC_HEX(ulong, unsigned long, "%lu", "%lx")
DBG_FUNC_HEX(llong, long long, "%lld", "%llx")
DBG_FUNC_HEX(ullong, unsigned long long, "%llu", "%llx")
DBG_FUNC(float, float, "%f")
DBG_FUNC(double, double, "%lf")

#endif
