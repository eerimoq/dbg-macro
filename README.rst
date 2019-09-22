About
=====
A macro for printf-style debugging fans.

Example
=======

.. code-block:: c

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
       dbg(numbers);  // main.c:21: numbers = [7, 13] (length: 2)

       factorial(4);

       return (0);
   }

The output is.

.. code-block:: text

   $ ./main
   main.c:15: message = "hello"
   main.c:18: 3 * a = 6
   main.c:21: numbers = [7, 13] (length: 2)
   main.c:5: n <= 1 = false
   main.c:5: n <= 1 = false
   main.c:5: n <= 1 = false
   main.c:5: n <= 1 = true
   main.c:6: 1 = 1
   main.c:8: n * factorial(n - 1) = 2
   main.c:8: n * factorial(n - 1) = 6
   main.c:8: n * factorial(n - 1) = 24
   
Acknowledgement
===============

This project is inspired by Rusts `dbg!(…) macro`_ and its `C++
variant`_.

.. _dbg!(…) macro: https://doc.rust-lang.org/std/macro.dbg.html

.. _C++ variant: https://github.com/sharkdp/dbg-macro
