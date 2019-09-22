#include "dbg.h"
#include "narwhal.h"

TEST(dbg_output)
{
    CAPTURE_OUTPUT(output) {
        dbg(1);
    }

    ASSERT_EQ(output,
              "\x1b[02mmain_color.c:7: \x1b[0m\x1b[36m\x1b[1m1 \x1b[0m= "
              "\x1b[01m1\n\x1b[0m");
}

TEST(dbgb_output)
{
    CAPTURE_OUTPUT(output) {
        dbgb(1);
    }

    ASSERT_EQ(output,
              "\x1b[02mmain_color.c:18: \x1b[0m\x1b[36m\x1b[1m1 \x1b[0m= "
              "\x1b[01mtrue\n\x1b[0m");
}

TEST(dbga_output)
{
    int a[3] = { 1, 2, 3 };

    CAPTURE_OUTPUT(output) {
        dbga(a, 3);
    }

    ASSERT_EQ(output,
              "\x1b[02mmain_color.c:31: \x1b[0m\x1b[36m\x1b[1ma \x1b[0m= "
              "\x1b[01m[1, 2, 3] (length: 3)\n\x1b[0m");
}

int main()
{
    return (RUN_TESTS(
                dbg_output,
                dbgb_output,
                dbga_output
            ));
}
