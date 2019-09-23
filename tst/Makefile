CFLAGS ?= \
	-Wjump-misses-init \
	-Wlogical-op \
	-Wfloat-equal \
	-Wformat=2 \
	-Wshadow \
	-Werror \
	-O3 \
	-g \
	-Wconversion \
	-Wall \
	-Wextra \
	-Wpedantic

all:
	$(MAKE) test
	$(MAKE) test-dbgcolor
	$(MAKE) test-ndbg

test:
	gcc -DNDBGCOLOR -fprofile-arcs -ftest-coverage \
	    $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -fprofile-arcs -ftest-coverage \
	    -I../include dbg.o narwhal.c main.c -o main
	./main

test-dbgcolor:
	gcc $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -I../include dbg.o narwhal.c main_dbgcolor.c -o main_dbgcolor
	./main_dbgcolor

test-ndbg:
	gcc -DNDBG $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -DNDBG -I../include dbg.o narwhal.c main_ndbg.c -o main_ndbg
	./main_ndbg
