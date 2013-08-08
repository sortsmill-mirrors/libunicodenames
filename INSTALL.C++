Although this method is not `officially' supported, LibUnicodeNames
can be built with a C++ compiler. First run configure; then, assuming
GCC and GNU Make, first build the Gnulib subdirectory with the C
compiler (which need not support C99):

   make -C lib

Then build LibUnicodeNames itself with the C++ compiler:

   make CC=g++

You may get some warning messages about GCC options not being
supported by GNU C++.
