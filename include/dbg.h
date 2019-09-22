#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define DBG_FUNC(name, type)                                            \
    type dbg_ ## name(const char *file_p,                               \
                      int line,                                         \
                      const char *expression_p,                         \
                      type value);                                      \
                                                                        \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *expression_p,      \
                                         const type *value_p,           \
                                         int length);                   \
                                                                        \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *expression_p,                  \
                             type *value_p,                             \
                             int length);

#define DBG_FUNC_CHAR(name, type)                                       \
    type dbg_ ## name(const char *file_p,                               \
                      int line,                                         \
                      const char *expression_p,                         \
                      type value);                                      \
                                                                        \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *expression_p,      \
                                         const type *value_p);          \
                                                                        \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *expression_p,                  \
                             type *value_p);

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

/**
 * Prints and returns the value of a given expression for quick and
 * dirty debugging.
 */
#define dbg(expression)                                 \
    _Generic((expression),                              \
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
             const unsigned char *: dbg_const_uchar_p)  \
    (__FILE__, __LINE__, #expression, expression)

#define dbga(expression, length)                                \
    _Generic((expression),                                      \
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
    (__FILE__, __LINE__, #expression, expression, length)

#define dbgb(expression)                                                \
    dbg_bool(__FILE__, __LINE__, #expression, expression)
