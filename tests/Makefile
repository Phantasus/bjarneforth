.PHONY: all prim_tests

CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS=-I../src 
PRE=bf_
#CFLAGS=-I..

VPATH=../src:.

all: unittest_selftest stacktest memorytest streamtest prim_stack_test

check: all
	./unittest_selftest
	./stacktest
	./memorytest
	./streamtest
	./prim_stack_test

#libtest.a : ../*.c
#	$(CC) -c $^ $(CFLAGS)
#	ar rcs libtest.a ../*.o
#	rm ../*.o

unittest_selftest: unittest_selftest.c unittest.c 
	$(CC) $^ $(CFLAGS) -o $@

stacktest: stacktest.c unittest.c bf_stack.c
	$(CC) $^ $(CFLAGS) -o $@

streamtest: streamtest.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c
	$(CC) $^ $(CFLAGS) -o $@

memorytest: memorytest.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c
	$(CC) $^ $(CFLAGS) -o $@

prim_tests: prim_stack_test
	./prim_stack_test

prim_stack_test: prim_stack_test.c bf_stack.c bf_state.c bf_memory.c bf_stream.c bf_io_prim.c bf_stack_prim.c
	$(CC) $^ $(CFLAGS) -o $@
