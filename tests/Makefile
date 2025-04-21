.PHONY: all

CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS=-I../src 
PRE=bf_
#CFLAGS=-I..

VPATH=../src:.

all: unittest_selftest stacktest memorytest streamtest dict_test \
	prim_stack_test prim_io_test prim_math_test compiler_test parsing_test

check: all
	./unittest_selftest
	./memorytest
	./stacktest
	./streamtest
	./prim_stack_test
	./prim_io_test
	./prim_math_test
	./dict_test
	./parsing_test
	./compiler_test

#libtest.a : ../*.c
#	$(CC) -c $^ $(CFLAGS)
#	ar rcs libtest.a ../*.o
#	rm ../*.o

unittest_selftest: unittest_selftest.c unittest.c 
	$(CC) $^ $(CFLAGS) -o $@

stacktest: stacktest.c unittest.c bf_stack.c bf_memory.c
	$(CC) $^ $(CFLAGS) -o $@

streamtest: streamtest.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c
	$(CC) $^ $(CFLAGS) -o $@

memorytest: memorytest.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c
	$(CC) $^ $(CFLAGS) -o $@

dict_test: dict_test.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c bf_dict.c \
	bf_stack_prim.c bf_compiler_prim.c bf_vm_prim.c \
	bf_strings_prim.c bf_compiler_prim.c bf_io_prim.c bf_interp_prim.c bf_dict_prim.c
	$(CC) $^ $(CFLAGS) -o $@

prim_dict_test: prim_dict_test.c unittest.c bf_dict.c bf_stack.c bf_state.c bf_memory.c bf_stream.c bf_io_prim.c bf_stack_prim.c
	$(CC) $^ $(CFLAGS) -o $@

prim_stack_test: prim_stack_test.c unittest.c bf_stack.c bf_state.c bf_memory.c bf_stream.c bf_io_prim.c bf_stack_prim.c
	$(CC) $^ $(CFLAGS) -o $@

prim_io_test: prim_io_test.c unittest.c bf_stack.c bf_state.c bf_memory.c bf_stream.c bf_io_prim.c bf_stack_prim.c
	$(CC) $^ $(CFLAGS) -o $@

prim_math_test: prim_math_test.c unittest.c bf_stack.c bf_state.c bf_memory.c bf_stream.c bf_math_prim.c bf_io_prim.c bf_stack_prim.c 
	$(CC) $^ $(CFLAGS) -o $@

parsing_test: parsing_test.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c bf_dict.c \
	bf_stack_prim.c bf_compiler_prim.c bf_vm_prim.c \
	bf_strings_prim.c bf_compiler_prim.c bf_io_prim.c bf_interp_prim.c bf_dict_prim.c
	$(CC) $^ $(CFLAGS) -o $@

compiler_test: compiler_test.c unittest.c bf_state.c bf_stream.c bf_stack.c bf_memory.c bf_dict.c \
	bf_stack_prim.c bf_compiler_prim.c bf_vm_prim.c \
	bf_strings_prim.c bf_compiler_prim.c bf_io_prim.c bf_interp_prim.c bf_dict_prim.c
	$(CC) $^ $(CFLAGS) -o $@
