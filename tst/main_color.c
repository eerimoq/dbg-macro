#include "dbg.h"
#include "narwhal.h"

#define FLF(test, line)                                                 \
    "\x1b[02mmain_color.c:" #line ": (_narwhal_test_function_" #test "_output) " \
    "\x1b[0m\x1b[36m\x1b[1m"

TEST(dbg_output)
{
    CAPTURE_OUTPUT(output) {
        dbg(1);
    }

    ASSERT_EQ(output, FLF(dbg, 11) "1\x1b[0m = \x1b[01m1\n\x1b[0m");
}

TEST(dbgb_output)
{
    CAPTURE_OUTPUT(output) {
        dbgb(1);
    }

    ASSERT_EQ(output, FLF(dbgb, 20) "1\x1b[0m = \x1b[01mtrue\n\x1b[0m");
}

TEST(dbga_output)
{
    int a[3] = { 1, 2, 3 };

    CAPTURE_OUTPUT(output) {
        dbga(a, 3);
    }

    ASSERT_EQ(output,
              FLF(dbga, 31) "a\x1b[0m = \x1b[01m[1, 2, 3] (length: 3)\n\x1b[0m");
}

int main()
{
    return (RUN_TESTS(
                dbg_output,
                dbgb_output,
                dbga_output
            ));
}
