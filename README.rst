|buildstatus|_
|codecov|_
|nala|_

About
=====

A few macros that prints and returns the value of a given expression
for quick and dirty debugging, inspired by Rusts `dbg!(…) macro`_ and
its `C++ variant`_.

``dbg(expr)`` for primitive data types (int, float, etc.), strings and
pointers.

``dbgb(expr)`` to force boolean true/false output.

``dbga(expr, length)`` for array of primitive data types.

``dbgh(expr, size)`` for hexdump output.

``dbge(expr)`` for negative error codes.

``dbgbt()`` for a backtrace.

Just include `dbg.h`_ in your project to use it.

Example
=======

|tryit|_

See `examples`_ for the files used in this example.

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
       dbgh(message, sizeof(message));

       const int a = 2;
       const int b = dbg(3 * a) + 1;  // main.c:19: 3 * a = 6 (0x6)

       int numbers[2] = { b, 13 };
       dbga(numbers, 2);  // main.c:22: numbers = [7, 13] (length: 2)

       dbg(factorial(4));
       dbge(-EINVAL);
       dbgbt();

       return (0);
   }

Build and run:

.. image:: https://github.com/eerimoq/dbg-macro/raw/master/docs/example-build-and-run.png

Compile time configuration
==========================

Define ``NDBG`` to make the macros a no-op.

Define ``DBG_NCOLOR`` for colorless output.

Define ``DBG_OSTREAM=<my-ostream>`` for custom output stream (stderr
by default).

.. |buildstatus| image:: https://travis-ci.org/eerimoq/dbg-macro.svg?branch=master
.. _buildstatus: https://travis-ci.org/eerimoq/dbg-macro

.. |codecov| image:: https://codecov.io/gh/eerimoq/dbg-macro/branch/master/graph/badge.svg
.. _codecov: https://codecov.io/gh/eerimoq/dbg-macro

.. |tryit| image:: https://img.shields.io/badge/try-online-f34b7d.svg
.. _tryit: https://repl.it/@eerimoq/dbg-macro

.. |nala| image:: https://img.shields.io/badge/nala-test-blue.svg
.. _nala: https://github.com/eerimoq/nala

.. _dbg!(…) macro: https://doc.rust-lang.org/std/macro.dbg.html

.. _C++ variant: https://github.com/sharkdp/dbg-macro

.. _dbg.h: https://github.com/eerimoq/dbg-macro/blob/master/include/dbg.h

.. _examples: https://github.com/eerimoq/dbg-macro/tree/master/examples
