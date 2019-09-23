CFLAGS ?= \
	-Werror \
	-O3 \
	-g \
	-Wall

all:
	$(MAKE) test
	$(MAKE) test-dbg-color
	$(MAKE) test-ndbg
	$(MAKE) test-dbg-ostream

test:
	gcc $(CFLAGS) -DDBG_NCOLOR -fprofile-arcs -ftest-coverage \
	    -I../include narwhal.c main.c -o main
	./main

test-dbg-color:
	gcc $(CFLAGS) -I../include narwhal.c main_dbg_color.c -o main_dbg_color
	./main_dbg_color

test-ndbg:
	gcc $(CFLAGS) -DNDBG -I../include narwhal.c main_ndbg.c -o main_ndbg
	./main_ndbg

test-dbg-ostream:
	gcc -DDBG_OSTREAM=my_ostream_p \
	    -I../include narwhal.c main_dbg_ostream.c -o main_dbg_ostream
	./main_dbg_ostream
