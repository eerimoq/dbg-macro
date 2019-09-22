#include "dbg.h"
#include <stdio.h>

#define FUNC_CONST_P(name, type, format)                                \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *expression_p,      \
                                         const type *value_p,           \
                                         int length)                    \
    {                                                                   \
        int i;                                                          \
        char *delim_p;                                                  \
                                                                        \
        printf("%s:%d: %s = [", file_p, line, expression_p);            \
        delim_p = "";                                                   \
                                                                        \
        for (i = 0; i < length; i++) {                                  \
            printf("%s" format, delim_p, value_p[i]);                   \
            delim_p = ", ";                                             \
        }                                                               \
                                                                        \
        printf("] (length: %u)\n", length);                             \
                                                                        \
        return (value_p);                                               \
    }

#define FUNC_P(name, type, format)                                      \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *expression_p,                  \
                             type *value_p,                             \
                             int length)                                \
    {                                                                   \
        dbg_const_ ## name ## _p(file_p, line, expression_p, value_p, length); \
                                                                        \
        return (value_p);                                               \
    }

#define FUNC(name, type, format)                \
    type dbg_ ## name(const char *file_p,       \
                      int line,                 \
                      const char *expression_p, \
                      type value)               \
    {                                           \
        printf("%s:%d: %s = " format "\n",      \
               file_p,                          \
               line,                            \
               expression_p,                    \
               value);                          \
                                                \
        return (value);                         \
    }                                           \
    FUNC_CONST_P(name, type, format)            \
    FUNC_P(name, type, format)

#define FUNC_CHAR_CONST_P(name, type)                                   \
    const type *dbg_const_ ## name ## _p(const char *file_p,            \
                                         int line,                      \
                                         const char *expression_p,      \
                                         const type *value_p)           \
    {                                                                   \
        printf("%s:%d: %s = \"%s\"\n",                                  \
               file_p,                                                  \
               line,                                                    \
               expression_p,                                            \
               value_p);                                                \
                                                                        \
        return (value_p);                                               \
    }

#define FUNC_CHAR_P(name, type)                                         \
    type *dbg_ ## name ## _p(const char *file_p,                        \
                             int line,                                  \
                             const char *expression_p,                  \
                             type *value_p)                             \
    {                                                                   \
        dbg_const_ ## name ## _p(file_p, line, expression_p, value_p);  \
                                                                        \
        return (value_p);                                               \
    }

#define FUNC_CHAR(name, type, format)           \
    type dbg_ ## name(const char *file_p,       \
                      int line,                 \
                      const char *expression_p, \
                      type value)               \
    {                                           \
        printf("%s:%d: %s = " format "\n",      \
               file_p,                          \
               line,                            \
               expression_p,                    \
               value);                          \
                                                \
        return (value);                         \
    }                                           \
    FUNC_CHAR_CONST_P(name, type)               \
    FUNC_CHAR_P(name, type)

bool dbg_bool(const char *file_p,
              int line,
              const char *expression_p,
              bool value)
{
    printf("%s:%d: %s = %s\n",
           file_p,
           line,
           expression_p,
           (value ? "true" : "false"));

    return (value);
}

const bool *dbg_const_bool_p(const char *file_p,
                             int line,
                             const char *expression_p,
                             const bool *value_p,
                             int length)
{
    int i;
    char *delim_p;

    printf("%s:%d: %s = [", file_p, line, expression_p);
    delim_p = "";

    for (i = 0; i < length; i++) {
        printf("%s%s", delim_p, (value_p[i] ? "true" : "false"));
        delim_p = ", ";
    }

    printf("] (length: %d)\n", length);

    return (value_p);
}

bool *dbg_bool_p(const char *file_p,
                 int line,
                 const char *expression_p,
                 bool *value_p,
                 int length)
{
    (void)dbg_const_bool_p(file_p, line, expression_p, value_p, length);

    return (value_p);
}

FUNC_CHAR(char, char, "%hhi")
FUNC_CHAR(schar, signed char, "%hhi")
FUNC_CHAR(uchar, unsigned char, "%hhu")
FUNC(short, short, "%hi")
FUNC(ushort, unsigned short, "%hu")
FUNC(int, int, "%d")
FUNC(uint, unsigned int, "%u")
FUNC(long, long, "%ld")
FUNC(ulong, unsigned long, "%lu")
FUNC(llong, long long, "%lld")
FUNC(ullong, unsigned long long, "%llu")
FUNC(float, float, "%f")
FUNC(double, double, "%lf")

void *dbg_pointer(const char *file_p,
                  int line,
                  const char *expression_p,
                  void *value_p)
{
    printf("%s:%d: %s = %p\n", file_p, line, expression_p, value_p);

    return (value_p);
}
