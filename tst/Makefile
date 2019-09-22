CFLAGS ?= \
	-fprofile-arcs \
	-ftest-coverage \
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
	$(MAKE) test-color

test:
	gcc -DNDBGCOLOR $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -fprofile-arcs -ftest-coverage \
	    -I../include dbg.o narwhal.c main.c -o main
	./main

test-color:
	gcc $(CFLAGS) -I../include -c ../src/dbg.c
	gcc -fprofile-arcs -ftest-coverage \
	    -I../include dbg.o narwhal.c main_color.c -o main_color
	./main_color
