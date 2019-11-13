#ifndef NALA_H
#define NALA_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "0.11.0"

#define TEST(name)                                      \
    void name(void);                                    \
    void name ## _before_fork() {}                      \
    static struct nala_test_t nala_test_ ## name = {    \
        .name_p = #name,                                \
        .func = name,                                   \
        .before_fork_func = name ## _before_fork,       \
        .next_p = NULL                                  \
    };                                                  \
    __attribute__ ((constructor))                       \
    void nala_constructor_ ## name(void)                \
    {                                                   \
        nala_register_test(&nala_test_ ## name);        \
    }                                                   \
    void name(void)

#define NALA_TEST_FAILURE(message_p)                    \
    nala_test_failure(__FILE__, __LINE__, message_p)

#define NALA_PRINT_FORMAT(value)                        \
    _Generic((value),                                   \
             char: "%c",                                \
             const char: "%c",                          \
             signed char: "%hhd",                       \
             const signed char: "%hhd",                 \
             unsigned char: "%hhu",                     \
             const unsigned char: "%hhu",               \
             signed short: "%hd",                       \
             const signed short: "%hd",                 \
             unsigned short: "%hu",                     \
             const unsigned short: "%hu",               \
             signed int: "%d",                          \
             const signed int: "%d",                    \
             unsigned int: "%u",                        \
             const unsigned int: "%u",                  \
             long int: "%ld",                           \
             const long int: "%ld",                     \
             unsigned long int: "%lu",                  \
             const unsigned long int: "%lu",            \
             long long int: "%lld",                     \
             const long long int: "%lld",               \
             unsigned long long int: "%llu",            \
             const unsigned long long int: "%llu",      \
             float: "%f",                               \
             const float: "%f",                         \
             double: "%f",                              \
             const double: "%f",                        \
             long double: "%Lf",                        \
             const long double: "%Lf",                  \
             char *: "\"%s\"",                          \
             const char *: "\"%s\"",                    \
             bool: "%d",                                \
    default: "%p")

#define NALA_BINARY_ASSERTION(left, right, check, format, formatter)    \
    if (!check((left), (right))) {                                      \
        char _nala_assert_format[512];                                  \
                                                                        \
        snprintf(&_nala_assert_format[0],                               \
                 sizeof(_nala_assert_format),                           \
                 format,                                                \
                 NALA_PRINT_FORMAT(left),                               \
                 NALA_PRINT_FORMAT(right));                             \
        NALA_TEST_FAILURE(formatter(_nala_assert_format,                \
                                    (left),                             \
                                    (right)));                          \
    }                                                                   \

#define NALA_CHECK_EQ(left, right)                      \
    _Generic(                                           \
        (left),                                         \
        char *: _Generic(                               \
            (right),                                    \
            char *: nala_check_string_equal(            \
                (char *)(uintptr_t)(left),              \
                (char *)(uintptr_t)(right)),            \
            const char *: nala_check_string_equal(      \
                (char *)(uintptr_t)(left),              \
                (char *)(uintptr_t)(right)),            \
            default: false),                            \
        const char *: _Generic(                         \
            (right),                                    \
            char *: nala_check_string_equal(            \
                (char *)(uintptr_t)(left),              \
                (char *)(uintptr_t)(right)),            \
            const char *: nala_check_string_equal(      \
                (char *)(uintptr_t)(left),              \
                (char *)(uintptr_t)(right)),            \
            default: false),                            \
        default: (left) == (right))

#define NALA_CHECK_NE(left, right)                              \
    _Generic(                                                   \
        (left),                                                 \
        char *: _Generic(                                       \
            (right),                                            \
            char *: (!nala_check_string_equal(                  \
                         (char *)(uintptr_t)(left),             \
                         (char *)(uintptr_t)(right))),          \
            const char *: (!nala_check_string_equal(            \
                               (char *)(uintptr_t)(left),       \
                               (char *)(uintptr_t)(right))),    \
            default: true),                                     \
        const char *: _Generic(                                 \
            (right),                                            \
            char *: (!nala_check_string_equal(                  \
                         (char *)(uintptr_t)(left),             \
                         (char *)(uintptr_t)(right))),          \
            const char *: (!nala_check_string_equal(            \
                               (char *)(uintptr_t)(left),       \
                               (char *)(uintptr_t)(right))),    \
            default: true),                                     \
        default: (left) != (right))

#define NALA_CHECK_LT(left, right) ((left) < (right))

#define NALA_CHECK_LE(left, right) ((left) <= (right))

#define NALA_CHECK_GT(left, right) ((left) > (right))

#define NALA_CHECK_GE(left, right) ((left) >= (right))

#define NALA_CHECK_SUBSTRING(left, right)       \
    nala_check_substring(left, right)

#define NALA_CHECK_NOT_SUBSTRING(left, right)   \
    (!nala_check_substring(left, right))

#define NALA_FORMAT_EQ(format, left, right)                     \
    _Generic(                                                   \
        (left),                                                 \
        char *: _Generic(                                       \
            (right),                                            \
            char *: nala_format_string(                         \
                format,                                         \
                (char *)(uintptr_t)(left),                      \
                (char *)(uintptr_t)(right)),                    \
            const char *: nala_format_string(                   \
                format,                                         \
                (char *)(uintptr_t)(left),                      \
                (char *)(uintptr_t)(right)),                    \
            default: nala_format(format, (left), (right))),     \
        const char *: _Generic(                                 \
            (right),                                            \
            char *: nala_format_string(                         \
                format,                                         \
                (char *)(uintptr_t)(left),                      \
                (char *)(uintptr_t)(right)),                    \
            const char *: nala_format_string(                   \
                format,                                         \
                (char *)(uintptr_t)(left),                      \
                (char *)(uintptr_t)(right)),                    \
            default: nala_format(format, (left), (right))),     \
        default: nala_format(format, (left), (right)))

#define ASSERT_EQ(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_EQ,                                \
                          "First argument %s is not equal to %s.\n",    \
                          NALA_FORMAT_EQ)

#define ASSERT_NE(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_NE,                                \
                          "First argument %s is not different from %s.\n", \
                          nala_format)

#define ASSERT_LT(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_LT,                                \
                          "First argument %s is not less than %s.\n",   \
                          nala_format)

#define ASSERT_LE(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_LE,                                \
                          "First argument %s is not less than or equal to %s.\n", \
                          nala_format)

#define ASSERT_GT(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_GT,                                \
                          "First argument %s is not greater than %s.\n", \
                          nala_format)

#define ASSERT_GE(left, right)                                          \
    NALA_BINARY_ASSERTION(left,                                         \
                          right,                                        \
                          NALA_CHECK_GE,                                \
                          "First argument %s is not greater or equal to %s.\n", \
                          nala_format)

#define ASSERT_SUBSTRING(string, substring)                             \
    NALA_BINARY_ASSERTION(string,                                       \
                          substring,                                    \
                          NALA_CHECK_SUBSTRING,                         \
                          "First argument %s doesn't contain %s.\n",    \
                          nala_format)

#define ASSERT_NOT_SUBSTRING(string, substring)                 \
    NALA_BINARY_ASSERTION(string,                               \
                          substring,                            \
                          NALA_CHECK_NOT_SUBSTRING,             \
                          "First argument %s contains %s.\n",   \
                          nala_format)

#define ASSERT_MEMORY(left, right, size)                        \
    do {                                                        \
        if (memcmp((left), (right), (size)) != 0) {             \
            NALA_TEST_FAILURE(nala_format_memory((left),        \
                                                 (right),       \
                                                 (size)));      \
        }                                                       \
    } while (0)

#define ASSERT(cond)                            \
    if (!(cond)) {                              \
        NALA_TEST_FAILURE(strdup("Assert.\n")); \
    }

#define FAIL() NALA_TEST_FAILURE(strdup("Fail.\n"))

#define CAPTURE_OUTPUT(stdout_name, stderr_name)                        \
    int stdout_name ## i;                                               \
    static char *stdout_name = NULL;                                    \
    static char *stderr_name = NULL;                                    \
                                                                        \
    for (stdout_name ## i = 0, nala_capture_output_start(&stdout_name,  \
                                                         &stderr_name); \
         stdout_name ## i < 1;                                          \
         stdout_name ## i++, nala_capture_output_stop())

struct nala_test_t {
    const char *name_p;
    void (*func)(void);
    void (*before_fork_func)(void);
    int exit_code;
    int signal_number;
    float elapsed_time_ms;
    struct nala_test_t *next_p;
};

bool nala_check_string_equal(const char *actual_p, const char *expected_p);

const char *nala_format(const char *format_p, ...);

const char *nala_format_string(const char *format_p, ...);

const char *nala_format_memory(const void *left_p,
                               const void *right_p,
                               size_t size);

bool nala_check_substring(const char *actual_p, const char *expected_p);

void nala_capture_output_start(char **stdout_pp, char **stderr_pp);

void nala_capture_output_stop(void);

__attribute__ ((noreturn)) void nala_test_failure(const char *file_p,
                                                  int line,
                                                  const char *message_p);

void nala_register_test(struct nala_test_t *test_p);

int nala_run_tests(void);

#endif
