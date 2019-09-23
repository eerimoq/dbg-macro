#include "dbg.h"

static int factorial(int n)
{
    if (dbgb(n <= 1)) {
        return dbg(1);
    } else {
        return dbg(n * factorial(n - 1));
    }
}

int main()
{
    char message[] = "hello";
    dbg(message);  // main.c:15: message = "hello"

    const int a = 2;
    const int b = dbg(3 * a) + 1;  // main.c:18: 3 * a = 6

    int numbers[2] = { b, 13 };
    dbga(numbers, 2);  // main.c:21: numbers = [7, 13] (length: 2)

    dbg(factorial(4));

    return (0);
}
