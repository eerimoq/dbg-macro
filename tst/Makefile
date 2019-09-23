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
	$(MAKE) test-dbg-color
	$(MAKE) test-ndbg
	$(MAKE) test-dbg-ostream

test:
	gcc -DDBG_NCOLOR -fprofile-arcs -ftest-coverage \
	    $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -fprofile-arcs -ftest-coverage \
	    -I../include dbg.o narwhal.c main.c -o main
	./main

test-dbg-color:
	gcc $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -I../include dbg.o narwhal.c main_dbg_color.c -o main_dbg_color
	./main_dbg_color

test-ndbg:
	gcc -DNDBG $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -DNDBG -I../include dbg.o narwhal.c main_ndbg.c -o main_ndbg
	./main_ndbg

test-dbg-ostream:
	gcc -DDBG_OSTREAM=my_ostream_p $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -I../include dbg.o narwhal.c main_dbg_ostream.c -o main_dbg_ostream
	./main_dbg_ostream
