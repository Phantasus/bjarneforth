.PHONY: all prim_tests

CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS=-I.. 
PRE=bf_
#CFLAGS=-I..

VPATH=..:.

all: unittest_selftest stacktest prim_tests

check: all
	./unittest_selftest
	./stacktest
	./prim_stack_test

lib.o : ../*.c
	$(CC) -c $^ $(CFLAGS) -o $@

unittest_selftest: unittest_selftest.c unittest.c 
	$(CC) $^ $(CFLAGS) -o $@

stacktest: stacktest.c unittest.c bf_stack.c lib.o
	$(CC) $^ $(CFLAGS) -o $@

prim_tests: prim_stack_test
	./prim_stack_test

prim_stack_test: prim_stack_test.c lib.o
	$(CC) $^ $(CFLAGS) -o $@
