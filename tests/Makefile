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

unittest_selftest: unittest_selftest.c unittest.c
	$(CC) $^ $(CFLAGS) -o $@

stacktest: stacktest.c unittest.c bf_stack.c
	$(CC) $^ $(CFLAGS) -o $@

prim_tests: prim_stack_test
	./prim_stack_test

prim_stack_test: prim_stack_test.c ../bf_stack_prim.c
	$(CC) $^ $(CFLAGS) -o $@
