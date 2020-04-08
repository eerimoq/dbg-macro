#include <libgen.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <getopt.h>
// #include "subprocess.h"
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
 * This file is part of the subprocess project.
 */

#ifndef NALA_SUBPROCESS_H
#define NALA_SUBPROCESS_H

#include <string.h>
#include <stdbool.h>

#define NALA_SUBPROCESS_VERSION "0.5.0"

typedef void (*nala_subprocess_entry_t)(void *arg_p);

struct nala_subprocess_output_t {
    /* Always null-terminated. */
    char *buf_p;
    /* Buffer length, not incuding last null-termination. */
    size_t length;
    /* Buffer size, including unused bytes. */
    size_t size;
};

struct nala_subprocess_result_t {
    int exit_code;
    int signal_number;
    struct nala_subprocess_output_t stdout;
    struct nala_subprocess_output_t stderr;
};

/**
 * Call given function with given argument in a subprocess. Returns
 * captured subprocess' exit code, or NULL if the subprocess could not
 * be started.
 */
struct nala_subprocess_result_t *nala_subprocess_call(nala_subprocess_entry_t entry,
                                                      void *arg_p);

/**
 * Call given function with given argument in a subprocess. Returns
 * captured subprocess' stdout, stderr and exit code, or NULL if the
 * subprocess could not be started.
 */
struct nala_subprocess_result_t *nala_subprocess_call_output(nala_subprocess_entry_t entry,
                                                             void *arg_p);

/**
 * Execute given command in a subprocess. Returns captured subprocess'
 * exit code, or NULL if the subprocess could not be started.
 */
struct nala_subprocess_result_t *nala_subprocess_exec(const char *command_p);

/**
 * Execute given command in a subprocess. Returns captured subprocess'
 * stdout, stderr and exit code, or NULL if the subprocess could not
 * be started.
 */
struct nala_subprocess_result_t *nala_subprocess_exec_output(const char *command_p);

/**
 * Returns true if the subprocess was started and exited with 0,
 * otherwise false.
 */
bool nala_subprocess_completed_successfully(struct nala_subprocess_result_t *result_p);

/**
 * Print subprocess exit code, stdout and stderr.
 */
void nala_subprocess_result_print(struct nala_subprocess_result_t *self_p);

/**
 * Free given result.
 */
void nala_subprocess_result_free(struct nala_subprocess_result_t *self_p);

#endif

// #include "traceback.h"
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
 * This file is part of the traceback project.
 */

#include <stdbool.h>

#define NALA_TRACEBACK_VERSION "0.8.0"

typedef bool (*nala_traceback_skip_filter_t)(void *arg_p, const char *line_p);

/**
 * Format given traceback. buffer_pp and depth are compatible with
 * backtrace() output.
 */
char *nala_traceback_format(void **buffer_pp,
                       int depth,
                       const char *prefix_p,
                       const char *header_p,
                       nala_traceback_skip_filter_t skip_filter,
                       void *arg_p);

/**
 * Create a traceback string.
 */
char *nala_traceback_string(const char *prefix_p,
                       const char *header_p,
                       nala_traceback_skip_filter_t skip_filter,
                       void *arg_p);

/**
 * Print a traceback.
 */
void nala_traceback_print(const char *prefix_p,
                     const char *header_p,
                     nala_traceback_skip_filter_t skip_filter,
                     void *arg_p);

#include "nala.h"
// #include "diff/diff.h"
#ifndef NALA_DIFF_H
#define NALA_DIFF_H

#include <stdlib.h>

struct NalaDiffMatrix
{
    size_t rows;
    size_t columns;
    int *content;
};

enum NalaDiffChunkType
{
    NALA_DIFF_CHUNK_TYPE_MATCHED,
    NALA_DIFF_CHUNK_TYPE_ADDED,
    NALA_DIFF_CHUNK_TYPE_REPLACED,
    NALA_DIFF_CHUNK_TYPE_DELETED
};

struct NalaDiff
{
    size_t size;
    struct NalaDiffChunk *chunks;
};

struct NalaDiffChunk
{
    enum NalaDiffChunkType type;
    size_t original_start;
    size_t original_end;
    size_t modified_start;
    size_t modified_end;
};

struct NalaDiffMatrix *nala_new_diff_matrix(size_t rows, size_t columns);
struct NalaDiffMatrix *nala_new_diff_matrix_from_lengths(size_t original_length,
                                                         size_t modified_lengths);
void nala_diff_matrix_fill_from_strings(struct NalaDiffMatrix *diff_matrix,
                                        const char *original,
                                        const char *modified);
void nala_diff_matrix_fill_from_lines(struct NalaDiffMatrix *diff_matrix,
                                      const char *original,
                                      const char *modified);
struct NalaDiff nala_diff_matrix_get_diff(const struct NalaDiffMatrix *diff_matrix);

size_t nala_diff_matrix_index(const struct NalaDiffMatrix *diff_matrix,
                              size_t row,
                              size_t column);
int nala_diff_matrix_get(const struct NalaDiffMatrix *diff_matrix,
                         size_t row,
                         size_t column);
void nala_diff_matrix_set(const struct NalaDiffMatrix *diff_matrix,
                          size_t row,
                          size_t column,
                          int value);

struct NalaDiff nala_diff_strings_lengths(const char *original,
                                          size_t original_length,
                                          const char *modified,
                                          size_t modified_length);
struct NalaDiff nala_diff_strings(const char *original, const char *modified);
struct NalaDiff nala_diff_lines(const char *original, const char *modified);

void nala_free_diff_matrix(struct NalaDiffMatrix *diff_matrix);

#endif

// #include "hexdump/hexdump.h"
#ifndef NALA_HEXDUMP_H
#define NALA_HEXDUMP_H

#include <stdint.h>
#include <stdlib.h>

char *nala_hexdump(const uint8_t *buffer, size_t size, size_t bytes_per_row);

#endif

// #include "utils.h"
#ifndef NALA_UTILS_H
#define NALA_UTILS_H

#include <stdbool.h>
#include <stdio.h>

int nala_min_int(int a, int b);
size_t nala_min_size_t(size_t a, size_t b);
size_t nala_count_chars(const char *string, char chr);
const char *nala_next_line(const char *string);
const char *nala_next_lines(const char *string, size_t lines);

#endif

// #include "hf.h"
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
 * This file is part of the humanfriendly project.
 */

#include <unistd.h>

#define NALA_HF_VERSION "0.2.0"

/**
 * Get the username of the currently logged in user. Returns the
 * current username, the default username, or NULL if the current user
 * cannot be determined and default_p is NULL.
 */
char *nala_hf_get_username(char *buf_p, size_t size, const char *default_p);

/**
 * Get the hostname. Returns the hostname, the default hostname, or
 * NULL if the hostname cannot be determined and default_p is NULL.
 */
char *nala_hf_get_hostname(char *buf_p, size_t size, const char *default_p);

/**
 * Format given timespan in milliseconds into given buffer.
 */
char *nala_hf_format_timespan(char *buf_p,
                              size_t size,
                              unsigned long long timespan_ms);


#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"

#define ANSI_BOLD "\x1b[1m"
#define ANSI_RESET "\x1b[0m"

#define COLOR(color, ...) ANSI_RESET ANSI_COLOR_##color __VA_ARGS__ ANSI_RESET

#define BOLD(...) ANSI_RESET ANSI_BOLD __VA_ARGS__ ANSI_RESET

#define COLOR_BOLD(color, ...)                                          \
    ANSI_RESET ANSI_COLOR_##color ANSI_BOLD __VA_ARGS__ ANSI_RESET

struct job_request_t {
    struct nala_test_t *test_p;
    int number;
};

struct job_response_t {
    struct nala_test_t *test_p;
    struct nala_test_t test;
};

struct tests_t {
    struct nala_test_t *head_p;
    struct nala_test_t *tail_p;
};

struct capture_output_t {
    bool running;
    char **output_pp;
    size_t length;
    int original_fd;
    FILE *temporary_file_p;
    FILE *original_file_p;
    FILE *stdout_p;
};

static struct nala_test_t *current_test_p = NULL;

static struct tests_t tests = {
    .head_p = NULL,
    .tail_p = NULL
};

static struct capture_output_t capture_stdout;
static struct capture_output_t capture_stderr;

__attribute__ ((weak)) void nala_assert_all_mocks_completed(void)
{
}

__attribute__ ((weak)) void nala_reset_all_mocks(void)
{
}

__attribute__ ((weak)) void nala_suspend_all_mocks(void)
{
}

__attribute__ ((weak)) void nala_resume_all_mocks(void)
{
}

__attribute__ ((weak)) int nala_print_call_mask = 0;

static bool continue_on_failure = false;
static const char *report_json_file_p = "report.json";
static int number_of_jobs = 1;

static const char *get_node(void)
{
    static char buf[128];

    return (nala_hf_get_hostname(&buf[0], sizeof(buf), "*** unknown ***"));
}

static const char *get_user(void)
{
    static char buf[128];

    return (nala_hf_get_username(&buf[0], sizeof(buf), "*** unknown ***"));
}

static const char *format_timespan(float elapsed_time_ms)
{
    static char buf[128];

    return (nala_hf_format_timespan(&buf[0],
                                    sizeof(buf),
                                    (unsigned long long)elapsed_time_ms));
}

static void color_start(FILE *file_p, const char *color_p)
{
    fprintf(file_p, "%s%s%s", ANSI_RESET, color_p, ANSI_BOLD);
}

static void color_reset(FILE *file_p)
{
    fprintf(file_p, "%s", ANSI_RESET);
}

static char *format_suite_prefix(struct nala_test_t *test_p,
                                 char *buf_p,
                                 size_t size)
{
    size_t length;

    strncpy(buf_p, test_p->file_p, size);
    buf_p = basename(buf_p);
    length = strlen(buf_p);

    if (length < 2) {
        return ("");
    }

    buf_p[length - 2] = '\0';

    if (strcmp(buf_p, "main") == 0) {
        return ("");
    }

    strcat(buf_p, "::");

    return (buf_p);
}

static char *full_test_name(struct nala_test_t *test_p)
{
    static char buf[512];
    char suite[512];
    char *suite_p;

    suite_p = format_suite_prefix(test_p, &suite[0], sizeof(suite));
    snprintf(&buf[0], sizeof(buf), "%s%s", suite_p, test_p->name_p);

    return (&buf[0]);
}

static void capture_output_init(struct capture_output_t *self_p,
                                FILE *file_p)
{
    self_p->output_pp = NULL;
    self_p->length = 0;
    self_p->original_file_p = file_p;
    self_p->stdout_p = fdopen(dup(fileno(file_p)), "w");
}

static void capture_output_destroy(struct capture_output_t *self_p)
{
    if (self_p->output_pp != NULL) {
        if (*self_p->output_pp != NULL) {
            free(*self_p->output_pp);
        }

        self_p->output_pp = NULL;
    }

    if (self_p->stdout_p != NULL) {
        fflush(self_p->stdout_p);
        fclose(self_p->stdout_p);
    }
}

static void capture_output_redirect(struct capture_output_t *self_p)
{
    fflush(self_p->original_file_p);

    self_p->temporary_file_p = tmpfile();
    self_p->original_fd = dup(fileno(self_p->original_file_p));

    while ((dup2(fileno(self_p->temporary_file_p),
                 fileno(self_p->original_file_p)) == -1)
           && (errno == EINTR));
}

static void capture_output_restore(struct capture_output_t *self_p)
{
    fflush(self_p->original_file_p);

    while ((dup2(self_p->original_fd, fileno(self_p->original_file_p)) == -1)
           && (errno == EINTR));

    close(self_p->original_fd);
}

static void capture_output_start(struct capture_output_t *self_p,
                                 char **output_pp)
{
    self_p->output_pp = output_pp;
    self_p->length = 0;
    self_p->running = true;
    capture_output_redirect(self_p);
}

static void capture_output_stop(struct capture_output_t *self_p)
{
    size_t nmembers;

    if (!self_p->running) {
        return;
    }

    self_p->running = false;
    capture_output_restore(self_p);

    self_p->length = (size_t)ftell(self_p->temporary_file_p);
    fseek(self_p->temporary_file_p, 0, SEEK_SET);
    *self_p->output_pp = malloc(self_p->length + 1);

    if (*self_p->output_pp == NULL) {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    if (self_p->length > 0) {
        nmembers = fread(*self_p->output_pp,
                         self_p->length,
                         1,
                         self_p->temporary_file_p);

        if (nmembers != 1) {
            printf("Failed to read capture output.\n");
            exit(1);
        }
    }

    (*self_p->output_pp)[self_p->length] = '\0';
    fclose(self_p->temporary_file_p);

    printf("%s", *self_p->output_pp);
}

FILE *nala_get_stdout(void)
{
    if (capture_stdout.running) {
        return (capture_stdout.stdout_p);
    } else {
        return (stdout);
    }
}

static float timeval_to_ms(struct timeval *timeval_p)
{
    float res;

    res = (float)timeval_p->tv_usec;
    res /= 1000;
    res += (float)(1000 * timeval_p->tv_sec);

    return (res);
}

static void print_test_failure_report_begin(void)
{
    printf("\n"
           "------------------------------"
           "--------------------"
           "-----------------------------\n");
    printf("\n");
}

static void print_test_failure_report_end(void)
{
    printf("\n");
}

static void print_signal_failure(struct nala_test_t *test_p)
{
    print_test_failure_report_begin();
    printf("  Test:  " COLOR_BOLD(CYAN, "%s\n"), full_test_name(current_test_p));
    printf("  Error: " COLOR_BOLD(RED, "Terminated by signal %d.\n"),
           test_p->signal_number);
    print_test_failure_report_end();
}

static const char *test_result(struct nala_test_t *test_p, bool color)
{
    const char *result_p;

    if (test_p->executed) {
        if (test_p->exit_code == 0) {
            if (color) {
                result_p = COLOR_BOLD(GREEN, "PASSED");
            } else {
                result_p = "PASSED";
            }
        } else {
            if (color) {
                result_p = COLOR_BOLD(RED, "FAILED");
            } else {
                result_p = "FAILED";
            }
        }
    } else {
        if (color) {
            result_p = COLOR_BOLD(YELLOW, "SKIPPED");
        } else {
            result_p = "SKIPPED";
        }
    }

    return (result_p);
}

static void print_test_result(struct nala_test_t *test_p)
{
    printf("%s %s (" COLOR_BOLD(YELLOW, "%s") ")",
           test_result(test_p, true),
           full_test_name(test_p),
           format_timespan(test_p->elapsed_time_ms));

    if (test_p->signal_number != -1) {
        printf(" (signal: %d)", test_p->signal_number);
    }

    printf("\n");
    fflush(stdout);
}

static void print_summary(struct nala_test_t *test_p,
                          float elapsed_time_ms)
{
    int total;
    int passed;
    int failed;
    int skipped;

    total = 0;
    passed = 0;
    failed = 0;
    skipped = 0;

    while (test_p != NULL) {
        total++;

        if (test_p->executed) {
            if (test_p->exit_code == 0) {
                passed++;
            } else {
                failed++;
            }
        } else {
            skipped++;
        }

        test_p = test_p->next_p;
    }

    printf("\nTests: ");

    if (failed > 0) {
        printf(COLOR_BOLD(RED, "%d failed") ", ", failed);
    }

    if (passed > 0) {
        printf(COLOR_BOLD(GREEN, "%d passed") ", ", passed);
    }

    if (skipped > 0) {
        printf(COLOR_BOLD(YELLOW, "%d skipped") ", ", skipped);
    }

    printf("%d total\n", total);
    printf("Time: " COLOR_BOLD(YELLOW, "%s") "\n",
           format_timespan(elapsed_time_ms));
}

static void write_report_json(struct nala_test_t *test_p)
{
    FILE *file_p;

    file_p = fopen(report_json_file_p, "w");

    if (file_p == NULL) {
        fprintf(stderr,
                "error: Failed to open JSON report '%s' with '%s'.\n",
                report_json_file_p,
                strerror(errno));
        exit(1);
    }

    fprintf(file_p,
            "{\n"
            "    \"name\": \"-\",\n"
            "    \"date\": \"-\",\n"
            "    \"node\": \"%s\",\n"
            "    \"user\": \"%s\",\n"
            "    \"testcases\": [\n",
            get_node(),
            get_user());

    while (test_p != NULL) {
        fprintf(file_p,
                "        {\n"
                "            \"name\": \"%s\",\n"
                "            \"description\": [],\n"
                "            \"result\": \"%s\",\n"
                "            \"execution_time\": \"%s\"\n"
                "        }%s\n",
                full_test_name(test_p),
                test_result(test_p, false),
                format_timespan(test_p->elapsed_time_ms),
                (test_p->next_p != NULL ? "," : ""));
        test_p = test_p->next_p;
    }

    fprintf(file_p,
            "    ]\n"
            "}\n");
    fclose(file_p);
}

static void test_entry(void *arg_p)
{
    struct nala_test_t *test_p;

    test_p = (struct nala_test_t *)arg_p;
    capture_output_init(&capture_stdout, stdout);
    capture_output_init(&capture_stderr, stderr);
    nala_reset_all_mocks();
    test_p->func();
    nala_exit(0);
}

static int run_test(struct nala_test_t *test_p)
{
    int res;
    struct timeval start_time;
    struct timeval end_time;
    struct timeval elapsed_time;
    struct nala_subprocess_result_t *result_p;

    res = 0;
    gettimeofday(&start_time, NULL);
    current_test_p = test_p;
    test_p->before_fork_func();

    result_p = nala_subprocess_call(test_entry, test_p);

    test_p->executed = true;
    test_p->exit_code = result_p->exit_code;
    test_p->signal_number = result_p->signal_number;
    nala_subprocess_result_free(result_p);

    if (test_p->exit_code != 0) {
        res = 1;
    }

    gettimeofday(&end_time, NULL);
    timersub(&end_time, &start_time, &elapsed_time);
    test_p->elapsed_time_ms = timeval_to_ms(&elapsed_time);

    if (test_p->signal_number != -1) {
        print_signal_failure(test_p);
    }

    print_test_result(test_p);

    return (res);
}

static int run_tests_sequentially(struct nala_test_t *test_p)
{
    int res;
    int exit_code;

    exit_code = 0;

    while (test_p != NULL) {
        res = run_test(test_p);

        if (res != 0) {
            exit_code = res;

            if (!continue_on_failure) {
                break;
            }
        }

        test_p = test_p->next_p;
    }

    return (exit_code);
}

static int run_tests_in_parallel_child(struct nala_test_t *test_p,
                                       int request_fds[2],
                                       int response_fds[2])
{
    int previous_number;
    ssize_t size;
    int exit_code;
    struct job_request_t request;
    struct job_response_t response;
    int res;

    close(request_fds[1]);
    close(response_fds[0]);

    exit_code = 0;
    previous_number = 0;

    while (true) {
        size = read(request_fds[0], &request, sizeof(request));

        if (size == 0) {
            break;
        }

        if (size != sizeof(request)) {
            perror("request read");
            exit(1);
        }

        while (previous_number < request.number) {
            previous_number++;
            test_p = test_p->next_p;
        }

        res = run_test(test_p);

        if (res != 0) {
            exit_code = res;
        }

        response.test_p = request.test_p;
        response.test = *test_p;

        size = write(response_fds[1], &response, sizeof(response));

        if (size != sizeof(response)) {
            perror("response write");
            exit(1);
        }
    }

    close(request_fds[0]);
    close(response_fds[1]);

    return (exit_code);
}

static void write_job_request(int fd,
                              struct nala_test_t *test_p,
                              int number)
{
    struct job_request_t request;
    ssize_t size;

    request.test_p = test_p;
    request.number = number;

    size = write(fd, &request, sizeof(request));

    if (size != sizeof(request)) {
        perror("request write");
        exit(1);
    }
}

static int read_job_response(int fd)
{
    struct job_response_t response;
    ssize_t size;
    struct nala_test_t *test_p;

    size = read(fd, &response, sizeof(response));

    if (size == 0) {
        return (1);
    }

    if (size != sizeof(response)) {
        perror("response read");
        exit(1);
    }

    /* Copy test result to this process's list. */
    test_p = response.test_p;
    test_p->executed = response.test.executed;
    test_p->exit_code = response.test.exit_code;
    test_p->signal_number = response.test.signal_number;
    test_p->elapsed_time_ms = response.test.elapsed_time_ms;

    return (test_p->exit_code);
}

static int run_tests_in_parallel(struct nala_test_t *test_p)
{
    int res;
    int request_fds[2];
    int response_fds[2];
    int i;
    pid_t *pids_p;
    int status;
    int exit_code;
    int number_of_outstanding_requests;
    int number;

    res = pipe(&request_fds[0]);

    if (res != 0) {
        fprintf(stderr, "error: request pipe open\n");
        exit(1);
    }

    res = pipe(&response_fds[0]);

    if (res != 0) {
        fprintf(stderr, "error: response pipe open\n");
        exit(1);
    }

    /* Create workers. */
    pids_p = alloca((size_t)number_of_jobs * sizeof(*pids_p));

    for (i = 0; i < number_of_jobs; i++) {
        pids_p[i] = fork();

        if (pids_p[i] < 0) {
            fprintf(stderr, "error: Failed to create worker process\n");
            exit(1);
        } else if (pids_p[i] == 0) {
            exit(run_tests_in_parallel_child(test_p,
                                             request_fds,
                                             response_fds));
        }
    }

    close(response_fds[1]);

    /* Keep the workers busy. */
    number_of_outstanding_requests = 0;
    number = 0;

    while (test_p != NULL) {
        if (number_of_outstanding_requests == number_of_jobs) {
            res = read_job_response(response_fds[0]);
            number_of_outstanding_requests--;

            if ((res != 0) && !continue_on_failure) {
                break;
            }
        }

        write_job_request(request_fds[1], test_p, number);
        number_of_outstanding_requests++;
        number++;
        test_p = test_p->next_p;
    }

    close(request_fds[1]);

    /* Read remaining responses. */
    while (number_of_outstanding_requests > 0) {
        (void)read_job_response(response_fds[0]);
        number_of_outstanding_requests--;
    }

    close(request_fds[0]);
    close(response_fds[0]);

    /* Wait for all workers to exit. */
    exit_code = 0;

    for (i = 0; i < number_of_jobs; i++) {
        waitpid(pids_p[i], &status, 0);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != 0) {
                exit_code = 1;
            }
        }

        if (WIFSIGNALED(status)) {
            exit_code = 1;
        }
    }

    return (exit_code);
}

static int run_tests(struct nala_test_t *tests_p)
{
    int exit_code;
    struct timeval start_time;
    struct timeval end_time;
    struct timeval elapsed_time;
    struct nala_test_t *test_p;

    test_p = tests_p;

    while (test_p != NULL) {
        test_p->executed = false;
        test_p = test_p->next_p;
    }

    test_p = tests_p;
    gettimeofday(&start_time, NULL);

    if (number_of_jobs == 1) {
        exit_code = run_tests_sequentially(test_p);
    } else {
        exit_code = run_tests_in_parallel(test_p);
    }

    gettimeofday(&end_time, NULL);
    timersub(&end_time, &start_time, &elapsed_time);
    print_summary(tests_p, timeval_to_ms(&elapsed_time));
    fflush(stdout);
    write_report_json(tests_p);

    return (exit_code);
}

bool nala_check_string_equal(const char *actual_p, const char *expected_p)
{
    if (actual_p == expected_p) {
        return (true);
    }

    return ((actual_p != NULL)
            && (expected_p != NULL)
            && (strcmp(actual_p, expected_p) == 0));
}

const char *nala_format(const char *format_p, ...)
{
    va_list vl;
    size_t size;
    char *buf_p;
    FILE *file_p;

    nala_suspend_all_mocks();
    file_p = open_memstream(&buf_p, &size);
    color_start(file_p, ANSI_COLOR_RED);
    va_start(vl, format_p);
    vfprintf(file_p, format_p, vl);
    va_end(vl);
    color_reset(file_p);
    fputc('\0', file_p);
    fclose(file_p);
    nala_resume_all_mocks();

    return (buf_p);
}

static const char *display_inline_diff(FILE *file_p,
                                       const struct NalaDiff *inline_diff,
                                       size_t lines,
                                       const char *string,
                                       size_t *line_number,
                                       bool use_original)
{
    struct NalaDiffChunk *inline_chunk = &inline_diff->chunks[0];
    size_t line_index = 0;
    size_t index = 0;

    for (size_t i = 0; i < lines; i++) {
        const char *next = nala_next_line(string);
        size_t line_length = (size_t)(next - string);

        char line_prefix[64];

        if (use_original) {
            snprintf(line_prefix,
                     sizeof(line_prefix),
                     "- " BOLD("%ld"),
                     *line_number);
            fprintf(file_p, " %19s" " |  ", line_prefix);
        } else {
            snprintf(line_prefix,
                     sizeof(line_prefix),
                     COLOR(RED, "+ ") COLOR_BOLD(RED, "%ld"),
                     *line_number);
            fprintf(file_p, " %37s" COLOR(RED, " |  "), line_prefix);
        }

        while (index - line_index < line_length) {
            size_t chunk_end =
                use_original ? inline_chunk->original_end : inline_chunk->modified_end;

            size_t start = index - line_index;
            size_t end = nala_min_size_t(chunk_end - line_index, line_length);

            size_t characters = end - start;

            if (inline_chunk->type == NALA_DIFF_CHUNK_TYPE_MATCHED) {
                fprintf(file_p, "%.*s", (int)characters, string + index - line_index);
            } else if (characters > 0) {
                if (use_original) {
                    fprintf(file_p,
                            BOLD("%.*s"),
                            (int)characters,
                            string + index - line_index);
                } else {
                    fprintf(file_p,
                            COLOR_BOLD(RED, "%.*s"),
                            (int)characters,
                            string + index - line_index);
                }
            }

            index += characters;

            if (index >= chunk_end) {
                inline_chunk++;
            }
        }

        fprintf(file_p, "\n");

        if (!use_original) {
            (*line_number)++;
        }

        string = next + 1;
        line_index += line_length + 1;
        index = line_index;
    }

    return string;
}

static void print_string_diff(FILE *file_p,
                              const char *original,
                              const char *modified)
{
    nala_suspend_all_mocks();
    fprintf(file_p, "  Diff:\n\n");

    struct NalaDiff diff = nala_diff_lines(original, modified);

    size_t line_number = 1;

    for (size_t chunk_index = 0; chunk_index < diff.size; chunk_index++) {
        struct NalaDiffChunk *chunk = &diff.chunks[chunk_index];

        size_t original_lines = chunk->original_end - chunk->original_start;
        size_t modified_lines = chunk->modified_end - chunk->modified_start;

        if (chunk->type == NALA_DIFF_CHUNK_TYPE_MATCHED) {
            for (size_t i = 0; i < original_lines; i++) {
                const char *original_next = nala_next_line(original);
                const char *modified_next = nala_next_line(modified);

                if (original_lines < 7 || (i < 2 && chunk_index > 0) ||
                    (original_lines - i < 3 && chunk_index < diff.size - 1)) {
                    fprintf(file_p, COLOR(MAGENTA, "%8zu"), line_number);
                    fprintf(file_p, " |  %.*s\n", (int)(original_next - original), original);
                } else if (i == 2) {
                    fprintf(file_p, "   :\n");
                }

                line_number++;
                original = original_next + 1;
                modified = modified_next + 1;
            }
        } else if (chunk->type == NALA_DIFF_CHUNK_TYPE_REPLACED) {
            const char *original_end = nala_next_lines(original, original_lines);
            const char *modified_end = nala_next_lines(modified, modified_lines);

            size_t original_length = (size_t)(original_end - original);
            size_t modified_length = (size_t)(modified_end - modified);

            struct NalaDiff inline_diff =
                nala_diff_strings_lengths(original,
                                          original_length,
                                          modified,
                                          modified_length);

            original = display_inline_diff(file_p,
                                           &inline_diff,
                                           original_lines,
                                           original,
                                           &line_number,
                                           true);
            modified = display_inline_diff(file_p,
                                           &inline_diff,
                                           modified_lines,
                                           modified,
                                           &line_number,
                                           false);

            free(inline_diff.chunks);
        } else if (chunk->type == NALA_DIFF_CHUNK_TYPE_DELETED) {
            for (size_t i = 0; i < original_lines; i++) {
                const char *original_next = nala_next_line(original);

                char line_prefix[64];
                snprintf(line_prefix,
                         sizeof(line_prefix),
                         COLOR(RED, "- ") COLOR_BOLD(RED, "%ld"),
                         line_number);

                fprintf(file_p, " %37s", line_prefix);
                fprintf(file_p, COLOR(RED, " |  ") COLOR_BOLD(RED, "%.*s\n"),
                        (int)(original_next - original),
                        original);

                original = original_next + 1;
            }
        } else if (chunk->type == NALA_DIFF_CHUNK_TYPE_ADDED) {
            for (size_t i = 0; i < modified_lines; i++) {
                const char *modified_next = nala_next_line(modified);

                char line_prefix[64];
                snprintf(line_prefix,
                         sizeof(line_prefix),
                         COLOR(RED, "+ ") COLOR_BOLD(RED, "%ld"),
                         line_number);

                fprintf(file_p, " %37s", line_prefix);
                fprintf(file_p, COLOR(RED, " |  ") COLOR_BOLD(RED, "%.*s\n"),
                        (int)(modified_next - modified),
                        modified);

                line_number++;
                modified = modified_next + 1;
            }
        }
    }

    free(diff.chunks);
    fprintf(file_p, "\n");
    nala_resume_all_mocks();
}

const char *nala_format_string(const char *format_p, ...)
{
    size_t size;
    char *buf_p;
    FILE *file_p;
    va_list vl;
    const char *left_p;
    const char *right_p;

    nala_suspend_all_mocks();

    va_start(vl, format_p);
    left_p = va_arg(vl, const char *);
    right_p = va_arg(vl, const char *);
    va_end(vl);

    file_p = open_memstream(&buf_p, &size);
    color_start(file_p, ANSI_COLOR_RED);
    fprintf(file_p, format_p, left_p, right_p);
    fprintf(file_p, " See diff for details.\n");
    color_reset(file_p);

    if (right_p == NULL) {
        right_p = "<null>";
    }

    if (left_p == NULL) {
        left_p = "<null>";
    }

    print_string_diff(file_p, right_p, left_p);
    fputc('\0', file_p);
    fclose(file_p);

    nala_resume_all_mocks();

    return (buf_p);
}

static void print_with_line_prefix(FILE *file_p,
                                   const char *prefix_p,
                                   const char *string_p)
{
    fprintf(file_p, "%s", prefix_p);

    while (*string_p != '\0') {
        fputc(string_p[0], file_p);

        if (*string_p == '\n') {
            fprintf(file_p, "%s", prefix_p);
        }

        string_p++;
    }
}

const char *nala_format_substring(const char *format_p,
                                  const char *haystack_p,
                                  const char *needle_p)
{
    size_t size;
    char *buf_p;
    FILE *file_p;

    nala_suspend_all_mocks();

    file_p = open_memstream(&buf_p, &size);
    color_start(file_p, ANSI_COLOR_RED);
    fprintf(file_p, "%s", format_p);
    fprintf(file_p, " See below for details.\n");
    color_reset(file_p);

    if (haystack_p == NULL) {
        haystack_p = "<null>";
    }

    if (needle_p == NULL) {
        needle_p = "<null>";
    }

    fprintf(file_p, "  Haystack:\n\n");
    print_with_line_prefix(file_p, "    ", haystack_p);
    fprintf(file_p, "\n");
    fprintf(file_p, "  Needle:\n\n");
    print_with_line_prefix(file_p, "    ", needle_p);
    fprintf(file_p, "\n");
    fputc('\0', file_p);
    fclose(file_p);

    nala_resume_all_mocks();

    return (buf_p);
}

const char *nala_format_memory(const char *prefix_p,
                               const void *left_p,
                               const void *right_p,
                               size_t size)
{
    size_t file_size;
    char *buf_p;
    FILE *file_p;
    char *left_hexdump_p;
    char *right_hexdump_p;

    nala_suspend_all_mocks();

    file_p = open_memstream(&buf_p, &file_size);
    fprintf(file_p,
            COLOR_BOLD(RED, "%sMemory mismatch. See diff for details.\n"),
            prefix_p);

    if (left_p == NULL) {
        left_p = "<null>";
    }

    if (right_p == NULL) {
        right_p = "<null>";
    }

    left_hexdump_p = nala_hexdump(left_p, size, 16);
    right_hexdump_p = nala_hexdump(right_p, size, 16);
    print_string_diff(file_p, right_hexdump_p, left_hexdump_p);
    free(left_hexdump_p);
    free(right_hexdump_p);
    fputc('\0', file_p);
    fclose(file_p);

    nala_resume_all_mocks();

    return (buf_p);
}

bool nala_check_substring(const char *string_p, const char *substring_p)
{
    return ((string_p != NULL)
            && (substring_p != NULL)
            && (strstr(string_p, substring_p) != NULL));
}

bool nala_check_memory(const void *left_p, const void *right_p, size_t size)
{
    return !(((left_p == NULL) && (right_p != NULL))
             || ((left_p != NULL) && (right_p == NULL))
             || (memcmp(left_p, right_p, size) != 0));
}

static bool traceback_skip_filter(void *arg_p, const char *line_p)
{
    (void)arg_p;

    if (strstr(line_p, "nala.c:") != NULL) {
        return (true);
    }

    if (strstr(line_p, "??") != NULL) {
        return (true);
    }

    return (false);
}

void nala_test_failure(const char *message_p)
{
    nala_suspend_all_mocks();
    nala_capture_output_stop();
    capture_output_destroy(&capture_stdout);
    capture_output_destroy(&capture_stderr);
    print_test_failure_report_begin();
    printf("  Test:  " COLOR_BOLD(CYAN, "%s\n"), full_test_name(current_test_p));
    printf("  Error: %s", message_p);
    printf("\n");
    nala_traceback_print("  ",
                         "Assert traceback (most recent call last):",
                         traceback_skip_filter,
                         NULL);
    print_test_failure_report_end();
    free((void *)message_p);
    exit(1);
}

void nala_capture_output_start(char **output_pp, char **errput_pp)
{
    nala_suspend_all_mocks();
    capture_output_start(&capture_stdout, output_pp);
    capture_output_start(&capture_stderr, errput_pp);
    nala_resume_all_mocks();
}

void nala_capture_output_stop(void)
{
    nala_suspend_all_mocks();
    capture_output_stop(&capture_stdout);
    capture_output_stop(&capture_stderr);
    nala_resume_all_mocks();
}

void nala_register_test(struct nala_test_t *test_p)
{
    if (tests.head_p == NULL) {
        tests.head_p = test_p;
    } else {
        tests.tail_p->next_p = test_p;
    }

    tests.tail_p = test_p;
}

int nala_run_tests(void)
{
    return (run_tests(tests.head_p));
}

static void print_usage_and_exit(const char *program_name_p, int exit_code)
{
    printf("usage: %s [-h] [-v] [-c] [-a] [-r] [-f] [-j] [<test-pattern>]\n"
           "\n"
           "Run tests.\n"
           "\n"
           "positional arguments:\n"
           "  test-pattern                  Only run tests matching given pattern. "
           "'^' matches\n"
           "                                the beginning and '$' matches the end "
           "of the test\n"
           "                                name.\n"
           "\n"
           "optional arguments:\n"
           "  -h, --help                    Show this help message and exit.\n"
           "  -v, --version                 Print version information.\n"
           "  -c, --continue-on-failure     Continue on test failure.\n"
           "  -a, --print-all-calls         Print all calls to ease debugging.\n"
           "  -r, --report-json-file        JSON test report file (default: "
           "report.json).\n"
           "  -f, --print-test-file-func    Print file:function for exactly "
           "one test.\n"
           "  -j, --jobs                    Run given number of tests in "
           "parallel\n"
           "                                (default: 1).\n",
           program_name_p);
    exit(exit_code);
}

static void print_version_and_exit(void)
{
    printf("%s\n", NALA_VERSION);
    exit(0);
}

static bool is_test_match(struct nala_test_t *test_p, const char *full_pattern_p)
{
    const char *full_test_name_p;
    size_t full_test_name_length;
    size_t pattern_length;
    size_t offset;
    bool match_beginning;
    bool match_end;
    char *pattern_p;

    pattern_length = strlen(full_pattern_p);

    if (pattern_length == 0) {
        return (true);
    }

    match_beginning = (full_pattern_p[0] == '^');
    match_end = (full_pattern_p[pattern_length - 1] == '$');
    pattern_p = alloca(pattern_length + 1);
    strcpy(pattern_p, full_pattern_p);

    if (match_beginning) {
        pattern_p++;
        pattern_length--;
    }

    if (match_end) {
        pattern_length--;
    }

    full_test_name_p = full_test_name(test_p);
    full_test_name_length = strlen(full_test_name_p);

    if (pattern_length > full_test_name_length) {
        return (false);
    }

    if (match_beginning || match_end) {
        if ((pattern_length == 0) && match_beginning && match_end) {
            return (false);
        }

        if (match_beginning) {
            if (strncmp(full_test_name_p, pattern_p, pattern_length) != 0) {
                return (false);
            }
        }

        if (match_end) {
            offset = (full_test_name_length - pattern_length);

            if (strncmp(&full_test_name_p[offset],
                        pattern_p,
                        pattern_length) != 0) {
                return (false);
            }
        }
    } else if (strstr(full_test_name_p, pattern_p) == NULL) {
        return (false);
    }

    return (true);
}

static void filter_tests(const char *test_pattern_p)
{
    struct nala_test_t *test_p;

    test_p = tests.head_p;
    tests.head_p = NULL;
    tests.tail_p = NULL;

    while (test_p != NULL) {
        if (is_test_match(test_p, test_pattern_p)) {
            nala_register_test(test_p);
        }

        test_p = test_p->next_p;
    }

    if (tests.tail_p != NULL) {
        tests.tail_p->next_p = NULL;
    }
}

static struct nala_test_t *find_test(const char *test_pattern_p)
{
    struct nala_test_t *test_p;
    struct nala_test_t *found_p;

    test_p = tests.head_p;
    found_p = NULL;

    while (test_p != NULL) {
        if (is_test_match(test_p, test_pattern_p)) {
            if (found_p == NULL) {
                found_p = test_p;
            } else {
                fprintf(stderr,
                        "error: '%s' matches more than one test.\n",
                        test_pattern_p);

                return (NULL);
            }
        }

        test_p = test_p->next_p;
    }

    if (found_p == NULL) {
        fprintf(stderr,
                "error: '%s' does not match any test.\n",
                test_pattern_p);

        return (NULL);
    }

    return (found_p);
}

static int print_test_file_func(const char *test_pattern_p)
{
    struct nala_test_t *test_p;

    test_p = find_test(test_pattern_p);

    if (test_p == NULL) {
        return (1);
    }

    printf("%s:%s\n", test_p->file_p, test_p->name_p);

    return (0);
}

__attribute__((weak)) int main(int argc, char *argv[])
{
    static struct option long_options[] = {
        { "help",                 no_argument,       NULL, 'h' },
        { "version",              no_argument,       NULL, 'v' },
        { "continue-on-failure",  no_argument,       NULL, 'c' },
        { "print-all-calls",      no_argument,       NULL, 'a' },
        { "report-json-file",     required_argument, NULL, 'r' },
        { "print-test-file-func", required_argument, NULL, 'f' },
        { "jobs",                 required_argument, NULL, 'j' },
        { NULL,                   no_argument,       NULL, 0 }
    };
    int option;

    /* Do not print function calls outside tests. */
    nala_suspend_all_mocks();

    while (1) {
        option = getopt_long(argc, argv, "hvcar:f:j:", &long_options[0], NULL);

        if (option == -1) {
            break;
        }

        switch (option) {

        case 'h':
            print_usage_and_exit(argv[0], 0);
            break;

        case 'v':
            print_version_and_exit();
            break;

        case 'c':
            continue_on_failure = true;
            break;

        case 'a':
            nala_print_call_mask = 0xff;
            break;

        case 'r':
            report_json_file_p = optarg;
            break;

        case 'f':
            return (print_test_file_func(optarg));

        case 'j':
            number_of_jobs = atoi(optarg);

            if (number_of_jobs < 1) {
                printf("error: At least one job is required, %d given.\n",
                       number_of_jobs);
                exit(1);
            }

            break;

        default:
            print_usage_and_exit(argv[0], 1);
        }
    }

    if (optind < argc) {
        filter_tests(argv[optind]);
    }

    return (nala_run_tests());
}

static bool mock_traceback_skip_filter(void *arg_p, const char *line_p)
{
    (void)arg_p;

    if (strstr(line_p, "nala.c:") != NULL) {
        return (true);
    }

    if (strstr(line_p, "nala_mocks.c:") != NULL) {
        return (true);
    }

    if (strstr(line_p, "??") != NULL) {
        return (true);
    }

    return (false);
}

char *nala_mock_traceback_format(void **buffer_pp, int depth)
{
    return (nala_traceback_format(buffer_pp,
                                  depth,
                                  "  ",
                                  "Mock traceback (most recent call last):",
                                  mock_traceback_skip_filter,
                                  NULL));
}

#define CHECK_EQ(actual, expected) ((actual) == (expected))

#define CHECK_NE(actual, expected) ((actual) != (expected))

#define CHECK_LT(actual, expected) ((actual) < (expected))

#define CHECK_LE(actual, expected) ((actual) <= (expected))

#define CHECK_GT(actual, expected) ((actual) > (expected))

#define CHECK_GE(actual, expected) ((actual) >= (expected))

#define PRINT_FORMAT(value)                     \
    _Generic((value),                           \
             char: "%c",                        \
             signed char: "%hhd",               \
             unsigned char: "%hhu",             \
             signed short: "%hd",               \
             unsigned short: "%hu",             \
             signed int: "%d",                  \
             unsigned int: "%u",                \
             long int: "%ld",                   \
             unsigned long int: "%lu",          \
             long long int: "%lld",             \
             unsigned long long int: "%llu",    \
             float: "%f",                       \
             double: "%f",                      \
             long double: "%Lf",                \
             const char *: "\"%s\"",            \
             bool: "%d",                        \
             const void *: "%p")

#define PRINT_FORMAT_HEX(value)                 \
    _Generic((value),                           \
             signed char: "%hhx",               \
             unsigned char: "%hhx",             \
             signed short: "%hx",               \
             unsigned short: "%hx",             \
             signed int: "%x",                  \
             unsigned int: "%x",                \
             long int: "%lx",                   \
             unsigned long int: "%lx",          \
             long long int: "%llx",             \
             unsigned long long int: "%llx")

#define ASSERTION(actual, expected, check, format, formatter)   \
    do {                                                        \
        if (!check(actual, expected)) {                         \
            nala_reset_all_mocks();                             \
            char _nala_assert_format[512];                      \
                                                                \
            snprintf(&_nala_assert_format[0],                   \
                     sizeof(_nala_assert_format),               \
                     format,                                    \
                     PRINT_FORMAT(actual),                      \
                     PRINT_FORMAT(expected));                   \
            nala_test_failure(formatter(_nala_assert_format,    \
                                        actual,                 \
                                        expected));             \
        }                                                       \
    } while (0);

#define ASSERTION_WITH_HEX(actual, expected, check, format, formatter)  \
    do {                                                                \
        if (!check(actual, expected)) {                                 \
            nala_reset_all_mocks();                                     \
            char _nala_assert_format[512];                              \
                                                                        \
            snprintf(&_nala_assert_format[0],                           \
                     sizeof(_nala_assert_format),                       \
                     format,                                            \
                     PRINT_FORMAT(actual),                              \
                     PRINT_FORMAT(expected),                            \
                     PRINT_FORMAT_HEX(actual),                          \
                     PRINT_FORMAT_HEX(expected));                       \
            nala_test_failure(formatter(_nala_assert_format,            \
                                        actual,                         \
                                        expected,                       \
                                        actual,                         \
                                        expected));                     \
        }                                                               \
    } while (0);

#define BINARY_ASSERTION(actual, expected, op)                          \
    switch (op) {                                                       \
                                                                        \
    case NALA_CHECK_EQ:                                                 \
        ASSERTION(actual, expected, CHECK_EQ, "%s != %s\n", nala_format); \
        break;                                                          \
                                                                        \
    case NALA_CHECK_NE:                                                 \
        ASSERTION(actual, expected, CHECK_NE, "%s == %s\n", nala_format); \
        break;                                                          \
                                                                        \
    case NALA_CHECK_LT:                                                 \
        ASSERTION(actual, expected, CHECK_LT, "%s >= %s\n", nala_format); \
        break;                                                          \
                                                                        \
    case NALA_CHECK_LE:                                                 \
        ASSERTION(actual, expected, CHECK_LE, "%s > %s\n", nala_format); \
        break;                                                          \
                                                                        \
    case NALA_CHECK_GT:                                                 \
        ASSERTION(actual, expected, CHECK_GT, "%s <= %s\n", nala_format); \
        break;                                                          \
                                                                        \
    case NALA_CHECK_GE:                                                 \
        ASSERTION(actual, expected, CHECK_GE, "%s < %s\n", nala_format); \
        break;                                                          \
                                                                        \
    default:                                                            \
        FAIL("Internal nala error.");                                   \
        break;                                                          \
    }

#define BINARY_ASSERTION_WITH_HEX(actual, expected, op)                 \
    switch (op) {                                                       \
                                                                        \
    case NALA_CHECK_EQ:                                                 \
        ASSERTION_WITH_HEX(actual,                                      \
                           expected,                                    \
                           CHECK_EQ,                                    \
                           "%s != %s (0x%s != 0x%s)\n",                 \
                           nala_format);                                \
        break;                                                          \
                                                                        \
    case NALA_CHECK_NE:                                                 \
        ASSERTION_WITH_HEX(actual,                                      \
                           expected,                                    \
                           CHECK_NE,                                    \
                           "%s == %s (0x%s == 0x%s)\n",                 \
                           nala_format);                                \
        break;                                                          \
                                                                        \
    default:                                                            \
        BINARY_ASSERTION(actual, expected, op);                         \
        break;                                                          \
    }

void nala_assert_char(char actual, char expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_schar(signed char actual, signed char expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_uchar(unsigned char actual, unsigned char expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_short(short actual, short expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_ushort(unsigned short actual, unsigned short expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_int(int actual, int expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_uint(unsigned int actual, unsigned int expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_long(long actual, long expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_ulong(unsigned long actual, unsigned long expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_llong(long long actual, long long expected, int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_ullong(unsigned long long actual,
                        unsigned long long expected,
                        int op)
{
    BINARY_ASSERTION_WITH_HEX(actual, expected, op);
}

void nala_assert_float(float actual, float expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_double(double actual, double expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_ldouble(long double actual, long double expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_bool(bool actual, bool expected, int op)
{
    BINARY_ASSERTION(actual, expected, op);
}

void nala_assert_ptr(const void *actual_p, const void *expected_p, int op)
{
    BINARY_ASSERTION(actual_p, expected_p, op);
}

typedef void (*format_array_item_t)(FILE *file_p, const void *value_p);

static char *format_array(const void *buf_p,
                          size_t item_size,
                          size_t size,
                          int i,
                          format_array_item_t format_item)
{
    size_t file_size;
    char *string_p;
    FILE *file_p;
    int length;
    int begin;
    int end;
    const char *c_buf_p;
    const char *delim_p;

    c_buf_p = (const char *)buf_p;
    length = (int)(size / item_size);
    begin = (i - 3);

    if (begin < 0) {
        begin = 0;
    }

    end = (i + 4);

    if (end > length) {
        end = length;
    }

    file_p = open_memstream(&string_p, &file_size);
    fprintf(file_p, "{ ");

    if (begin != 0) {
        fprintf(file_p, "..., ");
    }

    delim_p = "";

    for (i = begin; i < end; i++) {
        fprintf(file_p, "%s", delim_p);
        format_item(file_p, &c_buf_p[i * (int)item_size]);
        delim_p = ", ";
    }

    if (end != length) {
        fprintf(file_p, ", ...");
    }

    fprintf(file_p, " }");
    fputc('\0', file_p);
    fclose(file_p);

    return (string_p);
}

static void assert_array_failure(const void *actual_p,
                                 const void *expected_p,
                                 size_t item_size,
                                 size_t size,
                                 int i,
                                 format_array_item_t format_item)
{
    size_t file_size;
    char *buf_p;
    FILE *file_p;
    char *actual_string_p;
    char *expected_string_p;

    nala_suspend_all_mocks();

    file_p = open_memstream(&buf_p, &file_size);
    fprintf(file_p,
            COLOR_BOLD(RED, "The arrays differ at index %u. See diff for details.\n"),
            (unsigned)i);
    actual_string_p = format_array(actual_p,
                                   item_size,
                                   size,
                                   i,
                                   format_item);
    expected_string_p = format_array(expected_p,
                                     item_size,
                                     size,
                                     i,
                                     format_item);
    print_string_diff(file_p, expected_string_p, actual_string_p);
    free(actual_string_p);
    free(expected_string_p);
    fputc('\0', file_p);
    fclose(file_p);

    nala_resume_all_mocks();

    nala_test_failure(buf_p);
}

static void format_array_item_char(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%hhd", (int)*(char *)value_p);
}

static void format_array_item_schar(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%hhd", *(signed char *)value_p);
}

static void format_array_item_uchar(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%hhu", *(unsigned char *)value_p);
}

static void format_array_item_short(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%hd", *(short *)value_p);
}

static void format_array_item_ushort(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%hu", *(unsigned short *)value_p);
}

static void format_array_item_int(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%d", *(int *)value_p);
}

static void format_array_item_uint(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%u", *(unsigned *)value_p);
}

static void format_array_item_long(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%ld", *(long *)value_p);
}

static void format_array_item_ulong(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%lu", *(unsigned long *)value_p);
}

static void format_array_item_llong(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%lld", *(long long *)value_p);
}

static void format_array_item_ullong(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%llu", *(unsigned long long *)value_p);
}

static void format_array_item_float(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%f", *(float *)value_p);
}

static void format_array_item_double(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%f", *(double *)value_p);
}

static void format_array_item_ldouble(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%Lf", *(long double *)value_p);
}

static void format_array_item_bool(FILE *file_p, const void *value_p)
{
    fprintf(file_p, "%d", *(bool *)value_p);
}

#define ASSERT_ARRAY_TYPE(type, actual_p, expected_p, item_size, size) \
    size_t i;                                                           \
                                                                        \
    for (i = 0; i < size / item_size; i++) {                            \
        if (actual_p[i] != expected_p[i]) {                             \
            assert_array_failure(actual_p,                             \
                                  expected_p,                           \
                                  item_size,                            \
                                  size,                                 \
                                  (int)i,                               \
                                  format_array_item_ ## type);          \
        }                                                               \
    }                                                                   \

void nala_assert_array_char(const char *actual_p,
                             const char *expected_p,
                             size_t item_size,
                             size_t size)
{
    ASSERT_ARRAY_TYPE(char, actual_p, expected_p, item_size, size);
}

void nala_assert_array_schar(const signed char *actual_p,
                              const signed char *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(schar, actual_p, expected_p, item_size, size);
}

void nala_assert_array_uchar(const unsigned char *actual_p,
                              const unsigned char *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(uchar, actual_p, expected_p, item_size, size);
}

void nala_assert_array_short(const short *actual_p,
                              const short *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(short, actual_p, expected_p, item_size, size);
}

void nala_assert_array_ushort(const unsigned short *actual_p,
                               const unsigned short *expected_p,
                               size_t item_size,
                               size_t size)
{
    ASSERT_ARRAY_TYPE(ushort, actual_p, expected_p, item_size, size);
}

void nala_assert_array_int(const int *actual_p,
                            const int *expected_p,
                            size_t item_size,
                            size_t size)
{
    ASSERT_ARRAY_TYPE(int, actual_p, expected_p, item_size, size);
}

void nala_assert_array_uint(const unsigned int *actual_p,
                             const unsigned int *expected_p,
                             size_t item_size,
                             size_t size)
{
    ASSERT_ARRAY_TYPE(uint, actual_p, expected_p, item_size, size);
}

void nala_assert_array_long(const long *actual_p,
                             const long *expected_p,
                             size_t item_size,
                             size_t size)
{
    ASSERT_ARRAY_TYPE(long, actual_p, expected_p, item_size, size);
}

void nala_assert_array_ulong(const unsigned long *actual_p,
                              const unsigned long *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(ulong, actual_p, expected_p, item_size, size);
}

void nala_assert_array_llong(const long long *actual_p,
                              const long long *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(llong, actual_p, expected_p, item_size, size);
}

void nala_assert_array_ullong(const unsigned long long *actual_p,
                               const unsigned long long *expected_p,
                               size_t item_size,
                               size_t size)
{
    ASSERT_ARRAY_TYPE(ullong, actual_p, expected_p, item_size, size);
}

void nala_assert_array_float(const float *actual_p,
                              const float *expected_p,
                              size_t item_size,
                              size_t size)
{
    ASSERT_ARRAY_TYPE(float, actual_p, expected_p, item_size, size);
}

void nala_assert_array_double(const double *actual_p,
                               const double *expected_p,
                               size_t item_size,
                               size_t size)
{
    ASSERT_ARRAY_TYPE(double, actual_p, expected_p, item_size, size);
}

void nala_assert_array_ldouble(const long double *actual_p,
                                const long double *expected_p,
                                size_t item_size,
                                size_t size)
{
    ASSERT_ARRAY_TYPE(ldouble, actual_p, expected_p, item_size, size);
}

void nala_assert_array_bool(const bool *actual_p,
                             const bool *expected_p,
                             size_t item_size,
                             size_t size)
{
    ASSERT_ARRAY_TYPE(bool, actual_p, expected_p, item_size, size);
}

void nala_assert_array(const void *actual_p,
                       const void *expected_p,
                       size_t item_size,
                       size_t size)
{
    const char *c_actual_p;
    const char *c_expected_p;
    size_t i;
    char buf[512];

    c_actual_p = (const char *)actual_p;
    c_expected_p = (const char *)expected_p;

    for (i = 0; i < size; i += item_size) {
        if (memcmp(&c_actual_p[i], &c_expected_p[i], item_size) != 0) {
            snprintf(&buf[0],
                     sizeof(buf),
                     "The arrays differ at index %u. ",
                     (unsigned)(i / item_size));
            nala_test_failure(nala_format_memory(&buf[0],
                                                 &c_actual_p[i],
                                                 &c_expected_p[i],
                                                 item_size));
        }
    }
}

void nala_assert_string(const char *actual_p, const char *expected_p, int op)
{
    switch (op) {

    case NALA_CHECK_EQ:
        if (!nala_check_string_equal(actual_p, expected_p)) {
            nala_reset_all_mocks();
            nala_test_failure(nala_format_string("The strings are not equal.",
                                                 actual_p,
                                                 expected_p));
        }

        break;

    case NALA_CHECK_NE:
        if (nala_check_string_equal(actual_p, expected_p)) {
            nala_reset_all_mocks();
            nala_test_failure(nala_format("\"%s\" == \"%s\"\n",
                                          actual_p,
                                          expected_p));
        }

        break;

    default:
        FAIL("Internal nala error.");
        break;
    }
}

void nala_assert_substring(const char *haystack_p, const char *needle_p)
{
    if (!nala_check_substring(haystack_p, needle_p)) {
        nala_reset_all_mocks();
        nala_test_failure(
            nala_format_substring(
                "The haystack doesn't contain the needle.",
                haystack_p,
                needle_p));
    }
}

void nala_assert_not_substring(const char *haystack_p, const char *needle_p)
{
    ASSERTION(haystack_p,
              needle_p,
              !nala_check_substring,
              "%s contains %s\n",
              nala_format);
}

void nala_assert_memory(const void *actual_p, const void *expected_p, size_t size)
{
    if (!nala_check_memory(actual_p, expected_p, size)) {
        nala_reset_all_mocks();
        nala_test_failure(nala_format_memory("", actual_p, expected_p, size));
    }
}

void nala_assert(bool cond)
{
    if (!cond) {
        nala_reset_all_mocks();
        nala_test_failure(nala_format("false != true\n"));
    }
}

void nala_fail(const char *message_p)
{
    nala_reset_all_mocks();
    char message[strlen(message_p) + 2];
    strcpy(&message[0], message_p);
    strcat(&message[0], "\n");
    nala_test_failure(nala_format(&message[0]));
}

void nala_exit(int status)
{
    (void)status;

    nala_assert_all_mocks_completed();
    nala_reset_all_mocks();
    nala_suspend_all_mocks();
    capture_output_destroy(&capture_stdout);
    capture_output_destroy(&capture_stderr);
    exit(0);
}
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
 * This file is part of the subprocess project.
 */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>
#include <fcntl.h>
// #include "subprocess.h"


static void fatal_error(const char *message_p)
{
    perror(message_p);
    exit(1);
}

static int output_init(struct nala_subprocess_output_t *self_p)
{
    int res;

    res = -1;
    self_p->length = 0;
    self_p->size = 4096;
    self_p->buf_p = malloc(self_p->size);

    if (self_p->buf_p != NULL) {
        self_p->buf_p[0] = '\0';
        res = 0;
    }

    return (res);
}

static void output_append(struct nala_subprocess_output_t *self_p, int fd)
{
    ssize_t res;

    while (1) {
        res = read(fd,
                   &self_p->buf_p[self_p->length],
                   self_p->size - self_p->length - 1);

        if (res == 0) {
            break;
        } else if (res > 0) {
            self_p->length += (size_t)res;
            self_p->buf_p[self_p->length] = '\0';

            if ((self_p->length + 1) == self_p->size) {
                self_p->size += 4096;
                self_p->buf_p = realloc(self_p->buf_p, self_p->size);
            }
        } else if (errno == EAGAIN) {
            break;
        } else if (errno != EINTR) {
            /* ToDo: Fix. */
            fatal_error("read");
        }
    }
}

static void output_print(struct nala_subprocess_output_t *self_p,
                         const char *name_p)
{
    printf("%s (length: %ld):\n", name_p, self_p->length);
    printf("%s\n", self_p->buf_p);
}

static void redirect_output(int *fds_p, int fileno)
{
    close(fds_p[0]);
    while ((dup2(fds_p[1], fileno) == -1) && (errno == EINTR));
    close(fds_p[1]);
}

static void close_fds(int *fds_p)
{
    close(fds_p[0]);
    close(fds_p[1]);
}

static struct nala_subprocess_result_t *result_new(void)
{
    struct nala_subprocess_result_t *result_p;
    int res;

    result_p = malloc(sizeof(*result_p));

    if (result_p == NULL) {
        return (NULL);
    }

    result_p->exit_code = -1;
    result_p->signal_number = -1;
    res = output_init(&result_p->stdout);

    if (res != 0) {
        goto out1;
    }

    res = output_init(&result_p->stderr);

    if (res != 0) {
        goto out2;
    }

    return (result_p);

 out2:
    free(result_p->stdout.buf_p);

 out1:
    free(result_p);

    return (NULL);
}

static void call_child(nala_subprocess_entry_t entry,
                       void *arg_p)
{
    entry(arg_p);
}

static struct nala_subprocess_result_t *wait_for_pid(pid_t child_pid,
                                                     struct nala_subprocess_result_t *result_p)
{
    int status;

    waitpid(child_pid, &status, 0);

    if (result_p != NULL) {
        if (WIFEXITED(status)) {
            result_p->exit_code = WEXITSTATUS(status);
        }

        if (WIFSIGNALED(status)) {
            result_p->signal_number = WTERMSIG(status);
        }
    }

    return (result_p);
}

static struct nala_subprocess_result_t *call_parent(pid_t child_pid)
{
    return (wait_for_pid(child_pid, result_new()));
}

static void call_output_child(nala_subprocess_entry_t entry,
                              void *arg_p,
                              int *stdoutfds_p,
                              int *stderrfds_p)
{
    redirect_output(stdoutfds_p, STDOUT_FILENO);
    redirect_output(stderrfds_p, STDERR_FILENO);
    call_child(entry, arg_p);
}

static int prepare_for_poll(struct pollfd *fd_p, int fd)
{
    int res;

    res = fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    fd_p->fd = fd;
    fd_p->events = (POLLIN | POLLHUP);

    return (res);
}

static struct nala_subprocess_result_t *read_output(int stdout_fd, int stderr_fd)
{
    struct nala_subprocess_result_t *result_p;
    struct pollfd fds[2];
    int res;

    result_p = result_new();

    if (result_p == NULL) {
        return (NULL);
    }

    prepare_for_poll(&fds[0], stdout_fd);
    prepare_for_poll(&fds[1], stderr_fd);

    while (1) {
        res = poll(&fds[0], 2, -1);

        if (res >= 0) {
            if (fds[0].revents & POLLIN) {
                output_append(&result_p->stdout, stdout_fd);
            }

            if (fds[1].revents & POLLIN) {
                output_append(&result_p->stderr, stderr_fd);
            }

            if (fds[0].revents & POLLHUP) {
                break;
            }

            if (fds[1].revents & POLLHUP) {
                break;
            }
        } else if (errno != EINTR) {
            /* ToDo: Fix. */
            fatal_error("poll");
        }
    }

    return (result_p);
}

static struct nala_subprocess_result_t *call_output_parent(pid_t child_pid,
                                                           int *stdoutfds_p,
                                                           int *stderrfds_p)
{
    struct nala_subprocess_result_t *result_p;

    /* Close write ends. */
    close(stdoutfds_p[1]);
    close(stderrfds_p[1]);

    /* Read data from stdout and stderr pipes. */
    result_p = read_output(stdoutfds_p[0], stderrfds_p[0]);
    wait_for_pid(child_pid, result_p);

    close(stdoutfds_p[0]);
    close(stderrfds_p[0]);

    return (result_p);
}

static void exec_entry(const char *command_p)
{
    int res;

    res = execl("/bin/sh", "sh", "-c", command_p, NULL);

    if (res != 0) {
        exit(1);
    }
}

struct nala_subprocess_result_t *nala_subprocess_call(nala_subprocess_entry_t entry,
                                                      void *arg_p)
{
    pid_t pid;
    struct nala_subprocess_result_t *result_p;

    fflush(stdout);
    fflush(stderr);

    pid = fork();

    if (pid < 0) {
        result_p = NULL;
    } else if (pid == 0) {
        call_child(entry, arg_p);
        exit(0);
    } else {
        result_p = call_parent(pid);
    }

    return (result_p);
}

struct nala_subprocess_result_t *nala_subprocess_call_output(nala_subprocess_entry_t entry,
                                                             void *arg_p)
{
    pid_t pid;
    int stdoutfds[2];
    int stderrfds[2];
    struct nala_subprocess_result_t *result_p;

    fflush(stdout);
    fflush(stderr);

    if (pipe(stdoutfds) < 0) {
        return (NULL);
    }

    if (pipe(stderrfds) < 0) {
        goto out1;
    }

    pid = fork();

    if (pid < 0) {
        goto out2;
    } else if (pid == 0) {
        call_output_child(entry, arg_p, &stdoutfds[0], &stderrfds[0]);
        exit(0);
    } else {
        result_p = call_output_parent(pid, &stdoutfds[0], &stderrfds[0]);
    }

    return (result_p);

 out2:
    close_fds(&stderrfds[0]);

 out1:
    close_fds(&stdoutfds[0]);

    return (NULL);
}

struct nala_subprocess_result_t *nala_subprocess_exec(const char *command_p)
{
    return (nala_subprocess_call((nala_subprocess_entry_t)exec_entry,
                                 (void *)command_p));
}

struct nala_subprocess_result_t *nala_subprocess_exec_output(const char *command_p)
{
    return (nala_subprocess_call_output((nala_subprocess_entry_t)exec_entry,
                                        (void *)command_p));
}

bool nala_subprocess_completed_successfully(struct nala_subprocess_result_t *result_p)
{
    return ((result_p != NULL) && (result_p->exit_code == 0));
}

void nala_subprocess_result_print(struct nala_subprocess_result_t *self_p)
{
    printf("exit_code: %d\n", self_p->exit_code);
    output_print(&self_p->stdout, "stdout");
    output_print(&self_p->stderr, "stderr");
}

void nala_subprocess_result_free(struct nala_subprocess_result_t *self_p)
{
    free(self_p->stdout.buf_p);
    free(self_p->stderr.buf_p);
    free(self_p);
}
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
 * This file is part of the traceback project.
 */

#include <stdio.h>
#include <stdint.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
// #include "traceback.h"

// #include "subprocess.h"


#define DEPTH_MAX 100

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN  "\x1b[36m"
#define ANSI_RESET       "\x1b[0m"

#define COLOR(color, ...) ANSI_RESET ANSI_COLOR_##color __VA_ARGS__ ANSI_RESET

static void *fixaddr(void *address_p)
{
    return ((void *)(((uintptr_t)address_p) - 1));
}

static bool is_traceback_line(const char *line_p)
{
    if (strncmp(line_p, "traceback_print at ", 19) == 0) {
        return (true);
    }

    if (strncmp(line_p, "traceback_string at ", 20) == 0) {
        return (true);
    }

    return (false);
}

static char *strip_discriminator(char *line_p)
{
    char *discriminator_p;

    discriminator_p = strstr(line_p, " (discriminator");

    if (discriminator_p != NULL) {
        discriminator_p[0] = '\n';
        discriminator_p[1] = '\0';
    }

    return (line_p);
}

static void print_line(FILE *stream_p, const char *prefix_p, char *line_p)
{
    char *at_p;
    char *function_p;
    char *location_p;

    function_p = line_p;
    at_p = strstr(line_p, " at ");

    if (at_p == NULL) {
        fprintf(stream_p, "%s  %s", prefix_p, line_p);
        return;
    }

    at_p[0] = '\0';
    location_p = &at_p[4];

    fprintf(stream_p,
            "%s  " COLOR(GREEN, "%s") " at " COLOR(CYAN, "%s"),
            prefix_p,
            function_p,
            location_p);
}

char *nala_traceback_format(void **buffer_pp,
                       int depth,
                       const char *prefix_p,
                       const char *header_p,
                       nala_traceback_skip_filter_t skip_filter,
                       void *arg_p)
{
    char exe[256];
    char command[384];
    ssize_t size;
    int i;
    FILE *stream_p;
    size_t stream_size;
    struct nala_subprocess_result_t *result_p;
    char *string_p;

    if (prefix_p == NULL) {
        prefix_p = "";
    }

    if (header_p == NULL) {
        header_p = "Traceback (most recent call last):";
    }

    size = readlink("/proc/self/exe", &exe[0], sizeof(exe) - 1);

    if (size == -1) {
        return (NULL);
    }

    exe[size] = '\0';

    stream_p = open_memstream(&string_p, &stream_size);

    if (stream_p == NULL) {
        return (NULL);
    }

    fprintf(stream_p, "%s%s\n", prefix_p, header_p);

    for (i = (depth - 1); i >= 0; i--) {
        snprintf(&command[0],
                 sizeof(command),
                 "addr2line -f -p -e %s %p",
                 &exe[0],
                 fixaddr(buffer_pp[i]));

        result_p = nala_subprocess_exec_output(&command[0]);

        if (result_p->exit_code != 0) {
            nala_subprocess_result_free(result_p);
            continue;
        }

        if (is_traceback_line(result_p->stdout.buf_p)) {
            nala_subprocess_result_free(result_p);
            continue;
        }

        if (skip_filter != NULL) {
            if (skip_filter(arg_p, result_p->stdout.buf_p)) {
                nala_subprocess_result_free(result_p);
                continue;
            }
        }

        print_line(stream_p,
                   prefix_p,
                   strip_discriminator(result_p->stdout.buf_p));
        nala_subprocess_result_free(result_p);
    }

    fclose(stream_p);

    return (string_p);
}

char *nala_traceback_string(const char *prefix_p,
                       const char *header_p,
                       nala_traceback_skip_filter_t skip_filter,
                       void *arg_p)
{
    int depth;
    void *addresses[DEPTH_MAX];

    depth = backtrace(&addresses[0], DEPTH_MAX);

    return (nala_traceback_format(addresses,
                             depth,
                             prefix_p,
                             header_p,
                             skip_filter,
                             arg_p));
}

void nala_traceback_print(const char *prefix_p,
                       const char *header_p,
                     nala_traceback_skip_filter_t skip_filter,
                     void *arg_p)
{
    char *string_p;

    string_p = nala_traceback_string(prefix_p, header_p, skip_filter, arg_p);
    printf("%s", string_p);
    free(string_p);
}
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
 * This file is part of the humanfriendly project.
 */

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <pwd.h>
// #include "hf.h"


#define TIME_UNITS_MAX 7

static void nala_hf_null_last(char *buf_p, size_t size)
{
    buf_p[size - 1] = '\0';
}

char *nala_hf_get_username(char *buf_p, size_t size, const char *default_p)
{
    char *res_p;
    struct passwd *passwd_p;

    res_p = buf_p;
    passwd_p = getpwuid(geteuid());

    if (passwd_p == NULL) {
        if (default_p == NULL) {
            res_p = NULL;
        } else {
            strncpy(buf_p, default_p, size);
        }
    } else {
        strncpy(buf_p, passwd_p->pw_name, size);

        if (size > 0) {
            nala_hf_null_last(buf_p, size);
        }
    }

    nala_hf_null_last(buf_p, size);

    return (res_p);
}

char *nala_hf_get_hostname(char *buf_p, size_t size, const char *default_p)
{
    int res;
    char *res_p;

    res_p = buf_p;
    res = gethostname(buf_p, size);

    if (res != 0) {
        if (default_p == NULL) {
            res_p = NULL;
        } else {
            strncpy(buf_p, default_p, size);
        }
    }

    nala_hf_null_last(buf_p, size);

    return (res_p);
}

/* Common time units, used for formatting of time spans. */
struct time_unit_t {
    unsigned long divider;
    const char *unit_p;
};

static struct time_unit_t time_units[TIME_UNITS_MAX] = {
    {
        .divider = 60 * 60 * 24 * 7 * 52 * 1000ul,
        .unit_p = "y"
    },
    {
        .divider = 60 * 60 * 24 * 7 * 1000ul,
        .unit_p = "w"
    },
    {
        .divider = 60 * 60 * 24 * 1000ul,
        .unit_p = "d"
    },
    {
        .divider = 60 * 60 * 1000ul,
        .unit_p = "h"
    },
    {
        .divider = 60 * 1000ul,
        .unit_p = "m"
    },
    {
        .divider = 1000ul,
        .unit_p = "s"
    },
    {
        .divider = 1ul,
        .unit_p = "ms"
    }
};

static const char *get_delimiter(bool is_first, bool is_last)
{
    if (is_first) {
        return ("");
    } else if (is_last) {
        return (" and ");
    } else {
        return (", ");
    }
}

char *nala_hf_format_timespan(char *buf_p,
                              size_t size,
                              unsigned long long timespan_ms)
{
    int i;
    int res;
    unsigned long long count;
    size_t offset;

    strncpy(buf_p, "", size);
    offset = 0;

    for (i = 0; i < TIME_UNITS_MAX; i++) {
        count = (timespan_ms / time_units[i].divider);
        timespan_ms -= (count * time_units[i].divider);

        if (count == 0) {
            continue;
        }

        res = snprintf(&buf_p[offset],
                       size - offset,
                       "%s%llu%s",
                       get_delimiter(strlen(buf_p) == 0, timespan_ms == 0),
                       count,
                       time_units[i].unit_p);
        nala_hf_null_last(buf_p, size);

        if (res > 0) {
            offset += (size_t)res;
        }
    }

    if (strlen(buf_p) == 0) {
        strncpy(buf_p, "0s", size);
        nala_hf_null_last(buf_p, size);
    }

    return (buf_p);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
// #include "utils.h"


int nala_min_int(int a, int b)
{
    return a < b ? a : b;
}

size_t nala_min_size_t(size_t a, size_t b)
{
    return a < b ? a : b;
}

size_t nala_count_chars(const char *string, char chr)
{
    size_t count = 0;

    for (size_t i = 0; string[i] != '\0'; i++) {
        if (string[i] == chr) {
            count++;
        }
    }

    return count;
}

const char *nala_next_line(const char *string)
{
    char *next_line = strchr(string, '\n');

    if (next_line != NULL) {
        return next_line;
    } else {
        return string + strlen(string);
    }
}

const char *nala_next_lines(const char *string, size_t lines)
{
    const char *next_line = string;

    for (size_t i = 0; i < lines; i++) {
        next_line = nala_next_line(next_line) + 1;
    }

    return next_line;
}
// #include "diff.h"


#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// #include "../utils.h"
#ifndef NALA_UTILS_H
#define NALA_UTILS_H

#include <stdbool.h>
#include <stdio.h>

int nala_min_int(int a, int b);
size_t nala_min_size_t(size_t a, size_t b);
size_t nala_count_chars(const char *string, char chr);
const char *nala_next_line(const char *string);
const char *nala_next_lines(const char *string, size_t lines);

#endif


/*
 * Diff matrix initialization
 */

static void initialize_diff_matrix(struct NalaDiffMatrix *diff_matrix,
                                   size_t rows,
                                   size_t columns)
{
    diff_matrix->rows = rows;
    diff_matrix->columns = columns;
    diff_matrix->content = malloc(rows * columns * sizeof(int));
}

struct NalaDiffMatrix *nala_new_diff_matrix(size_t rows, size_t columns)
{
    struct NalaDiffMatrix *diff_matrix = malloc(sizeof(struct NalaDiffMatrix));
    initialize_diff_matrix(diff_matrix, rows, columns);

    return diff_matrix;
}

/*
 * Diff matrix operations
 */

struct NalaDiffMatrix *nala_new_diff_matrix_from_lengths(size_t original_length,
                                                         size_t modified_length)
{
    struct NalaDiffMatrix *diff_matrix =
        nala_new_diff_matrix(modified_length + 1, original_length + 1);

    for (size_t i = 0; i < diff_matrix->rows; i++) {
        nala_diff_matrix_set(diff_matrix, i, 0, (int)i);
    }

    for (size_t j = 0; j < diff_matrix->columns; j++) {
        nala_diff_matrix_set(diff_matrix, 0, j, (int)j);
    }

    return diff_matrix;
}

static void fill_different(struct NalaDiffMatrix *diff_matrix, size_t i, size_t j)
{
    nala_diff_matrix_set(
        diff_matrix,
        i,
        j,
        nala_min_int(nala_diff_matrix_get(diff_matrix, i - 1, j - 1),
                     nala_min_int(nala_diff_matrix_get(diff_matrix, i - 1, j),
                                  nala_diff_matrix_get(diff_matrix, i, j - 1))) +
        1);
}

static void fill_equal(struct NalaDiffMatrix *diff_matrix, size_t i, size_t j)
{
    nala_diff_matrix_set(diff_matrix,
                         i,
                         j,
                         nala_diff_matrix_get(diff_matrix, i - 1, j - 1));
}

void nala_diff_matrix_fill_from_strings(struct NalaDiffMatrix *diff_matrix,
                                        const char *original,
                                        const char *modified)
{
    for (size_t i = 1; i < diff_matrix->rows; i++) {
        for (size_t j = 1; j < diff_matrix->columns; j++) {
            if (original[j - 1] == modified[i - 1]) {
                fill_equal(diff_matrix, i, j);
            } else {
                fill_different(diff_matrix, i, j);
            }
        }
    }
}

void nala_diff_matrix_fill_from_lines(struct NalaDiffMatrix *diff_matrix,
                                      const char *original,
                                      const char *modified)
{
    const char *modified_pos;
    const char *modified_line = modified;

    for (size_t i = 1; i < diff_matrix->rows; i++) {
        modified_pos = nala_next_line(modified_line);
        size_t modified_line_length = (size_t)(modified_pos - modified_line);

        const char *original_pos;
        const char *original_line = original;

        for (size_t j = 1; j < diff_matrix->columns; j++) {
            original_pos = nala_next_line(original_line);
            size_t original_line_length = (size_t)(original_pos - original_line);

            if (original_line_length == modified_line_length &&
                strncmp(original_line, modified_line, original_line_length) == 0) {
                fill_equal(diff_matrix, i, j);
            } else {
                fill_different(diff_matrix, i, j);
            }

            original_line = original_pos + 1;
        }

        modified_line = modified_pos + 1;
    }
}

struct NalaDiff nala_diff_matrix_get_diff(const struct NalaDiffMatrix *diff_matrix)
{
    if (diff_matrix->rows == 1 && diff_matrix->columns == 1) {
        struct NalaDiff diff = { .size = 0, .chunks = NULL };
        return diff;
    }

    size_t capacity = 32;
    size_t size = 0;
    struct NalaDiffChunk *backtrack = malloc(capacity * sizeof(struct NalaDiffChunk));

    size_t i = diff_matrix->rows - 1;
    size_t j = diff_matrix->columns - 1;

    while (i > 0 || j > 0) {
        if (size == capacity) {
            capacity *= 2;
            backtrack = realloc(backtrack, capacity * sizeof(struct NalaDiffChunk));
        }

        struct NalaDiffChunk *current_chunk = &backtrack[size];
        size++;

        int current = nala_diff_matrix_get(diff_matrix, i, j);

        if (i > 0 && j > 0 && current == nala_diff_matrix_get(diff_matrix, i - 1, j - 1) + 1) {
            current_chunk->type = NALA_DIFF_CHUNK_TYPE_REPLACED;
            current_chunk->original_start = j - 1;
            current_chunk->original_end = j;
            current_chunk->modified_start = i - 1;
            current_chunk->modified_end = i;
            i--;
            j--;
        } else if (j > 0 && current == nala_diff_matrix_get(diff_matrix, i, j - 1) + 1) {
            current_chunk->type = NALA_DIFF_CHUNK_TYPE_DELETED;
            current_chunk->original_start = j - 1;
            current_chunk->original_end = j;
            current_chunk->modified_start = i;
            current_chunk->modified_end = i;
            j--;
        } else if (i > 0 && current == nala_diff_matrix_get(diff_matrix, i - 1, j) + 1) {
            current_chunk->type = NALA_DIFF_CHUNK_TYPE_ADDED;
            current_chunk->original_start = j;
            current_chunk->original_end = j;
            current_chunk->modified_start = i - 1;
            current_chunk->modified_end = i;
            i--;
        } else if (i > 0 && j > 0 && current == nala_diff_matrix_get(diff_matrix, i - 1, j - 1)) {
            current_chunk->type = NALA_DIFF_CHUNK_TYPE_MATCHED;
            current_chunk->original_start = j - 1;
            current_chunk->original_end = j;
            current_chunk->modified_start = i - 1;
            current_chunk->modified_end = i;
            i--;
            j--;
        }
    }

    struct NalaDiff diff = { size, malloc(size * sizeof(struct NalaDiffChunk)) };

    ssize_t backtrack_index = (ssize_t)size - 1;
    size_t chunk_index = 0;

    diff.chunks[chunk_index] = backtrack[backtrack_index];

    for (backtrack_index--; backtrack_index >= 0; backtrack_index--) {
        struct NalaDiffChunk *chunk = &backtrack[backtrack_index];
        struct NalaDiffChunk *previous_chunk = &diff.chunks[chunk_index];

        if (chunk->type == previous_chunk->type) {
            previous_chunk->original_end = chunk->original_end;
            previous_chunk->modified_end = chunk->modified_end;
        } else if ((chunk->type == NALA_DIFF_CHUNK_TYPE_REPLACED &&
                    previous_chunk->type != NALA_DIFF_CHUNK_TYPE_MATCHED) ||
                   (chunk->type != NALA_DIFF_CHUNK_TYPE_MATCHED &&
                    previous_chunk->type == NALA_DIFF_CHUNK_TYPE_REPLACED)) {
            previous_chunk->type = NALA_DIFF_CHUNK_TYPE_REPLACED;
            previous_chunk->original_end = chunk->original_end;
            previous_chunk->modified_end = chunk->modified_end;
        } else {
            chunk_index++;
            diff.chunks[chunk_index] = *chunk;
        }
    }

    free(backtrack);

    diff.size = chunk_index + 1;
    diff.chunks = realloc(diff.chunks, diff.size * sizeof(struct NalaDiffChunk));

    return diff;
}

size_t nala_diff_matrix_index(const struct NalaDiffMatrix *diff_matrix, size_t row, size_t column)
{
    return row * diff_matrix->columns + column;
}

int nala_diff_matrix_get(const struct NalaDiffMatrix *diff_matrix, size_t row, size_t column)
{
    return diff_matrix->content[nala_diff_matrix_index(diff_matrix, row, column)];
}

void nala_diff_matrix_set(const struct NalaDiffMatrix *diff_matrix,
                          size_t row,
                          size_t column,
                          int value)
{
    diff_matrix->content[nala_diff_matrix_index(diff_matrix, row, column)] = value;
}

/*
 * Higher-level wrappers
 */

struct NalaDiff nala_diff_strings_lengths(const char *original,
                                   size_t original_length,
                                   const char *modified,
                                   size_t modified_length)
{
    struct NalaDiffMatrix *diff_matrix =
        nala_new_diff_matrix_from_lengths(original_length, modified_length);

    nala_diff_matrix_fill_from_strings(diff_matrix, original, modified);

    struct NalaDiff diff = nala_diff_matrix_get_diff(diff_matrix);

    nala_free_diff_matrix(diff_matrix);

    return diff;
}

struct NalaDiff nala_diff_strings(const char *original, const char *modified)
{
    return nala_diff_strings_lengths(original, strlen(original), modified, strlen(modified));
}

struct NalaDiff nala_diff_lines(const char *original, const char *modified)
{
    size_t original_length = nala_count_chars(original, '\n') + 1;
    size_t modified_length = nala_count_chars(modified, '\n') + 1;

    struct NalaDiffMatrix *diff_matrix =
        nala_new_diff_matrix_from_lengths(original_length, modified_length);

    nala_diff_matrix_fill_from_lines(diff_matrix, original, modified);

    struct NalaDiff diff = nala_diff_matrix_get_diff(diff_matrix);

    nala_free_diff_matrix(diff_matrix);

    return diff;
}

/*
 * Cleanup
 */

void nala_free_diff_matrix(struct NalaDiffMatrix *diff_matrix)
{
    free(diff_matrix->content);
    free(diff_matrix);
}
// #include "hexdump.h"


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *nala_hexdump(const uint8_t *buffer, size_t size, size_t bytes_per_row)
{
    size_t dump_size;
    char *dump;
    FILE *stream = open_memstream(&dump, &dump_size);
    size_t offset = 0;

    if (buffer == NULL) {
        fprintf(stream, "<nil>\n");
    } else {
        while (offset < size) {
            fprintf(stream, "%06lX  ", offset);

            for (size_t i = 0; i < bytes_per_row; i++) {
                if (offset + i < size)             {
                    fprintf(stream, "%02X ", buffer[offset + i]);
                } else {
                    fprintf(stream, "-- ");
                }
            }

            fprintf(stream, " ");

            for (size_t i = 0; i < bytes_per_row; i++) {
                if (offset + i < size) {
                    uint8_t byte = buffer[offset + i];
                    fprintf(stream, "%c", isprint(byte) ? byte : '.');
                } else {
                    fprintf(stream, " ");
                }
            }

            offset += bytes_per_row;

            if (offset < size) {
                fprintf(stream, "\n");
            }
        }
    }
    
    fclose(stream);

    return dump;
}
