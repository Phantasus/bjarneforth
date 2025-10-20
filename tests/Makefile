.PHONY: all

CC=g++ # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS= -I../src -pedantic -std=c++23 -Wall -Wextra -Werror
PRE=bf_

VPATH=../src:.

all: unittest_test stack_test memory_test stream_test dict_test \
	prim_stack_test prim_io_test prim_math_test compiler_test parsing_test

check: all
	./unittest_test
	./memory_test
	./stack_test
	./stream_test
	./prim_stack_test
	./prim_io_test
	./prim_math_test
	./dict_test
	./parsing_test
	./compiler_test

unittest_test: unittest_test.cpp unittest.cpp 
	$(CC) $^ $(CFLAGS) -o $@

stack_test: stack_test.cpp unittest.cpp bf_stack.cpp bf_memory.cpp
	$(CC) $^ $(CFLAGS) -o $@

stream_test: stream_test.cpp unittest.cpp bf_state.cpp bf_stream.cpp bf_stack.cpp bf_memory.cpp
	$(CC) $^ $(CFLAGS) -o $@

memory_test: memory_test.cpp unittest.cpp bf_state.cpp bf_stream.cpp bf_stack.cpp bf_memory.cpp
	$(CC) $^ $(CFLAGS) -o $@

dict_test: dict_test.cpp unittest.cpp bf_state.cpp bf_stream.cpp bf_stack.cpp bf_memory.cpp bf_dict.cpp \
	bf_stack_prim.cpp bf_compiler_prim.cpp bf_vm_prim.cpp \
	bf_strings_prim.cpp bf_compiler_prim.cpp bf_io_prim.cpp bf_interp_prim.cpp bf_dict_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@

prim_dict_test: prim_dict_test.cpp unittest.cpp bf_dict.cpp bf_stack.cpp bf_state.cpp bf_memory.cpp bf_stream.cpp bf_io_prim.cpp bf_stack_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@

prim_stack_test: prim_stack_test.cpp unittest.cpp bf_stack.cpp bf_state.cpp bf_memory.cpp bf_stream.cpp bf_io_prim.cpp bf_stack_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@

prim_io_test: prim_io_test.cpp unittest.cpp bf_stack.cpp bf_state.cpp bf_memory.cpp bf_stream.cpp bf_io_prim.cpp bf_stack_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@

prim_math_test: prim_math_test.cpp unittest.cpp bf_stack.cpp bf_state.cpp bf_memory.cpp bf_stream.cpp bf_math_prim.cpp bf_io_prim.cpp bf_stack_prim.cpp 
	$(CC) $^ $(CFLAGS) -o $@

parsing_test: parsing_test.cpp unittest.cpp bf_state.cpp bf_stream.cpp bf_stack.cpp bf_memory.cpp bf_dict.cpp \
	bf_stack_prim.cpp bf_compiler_prim.cpp bf_vm_prim.cpp \
	bf_strings_prim.cpp bf_compiler_prim.cpp bf_io_prim.cpp bf_interp_prim.cpp bf_dict_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@

compiler_test: compiler_test.cpp unittest.cpp bf_state.cpp bf_stream.cpp bf_stack.cpp bf_memory.cpp bf_dict.cpp \
	bf_stack_prim.cpp bf_compiler_prim.cpp bf_vm_prim.cpp \
	bf_strings_prim.cpp bf_compiler_prim.cpp bf_io_prim.cpp bf_interp_prim.cpp bf_dict_prim.cpp
	$(CC) $^ $(CFLAGS) -o $@
