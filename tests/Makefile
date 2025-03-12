.PHONY: all

CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS=-I.. 
PRE=bf_
#CFLAGS=-I..

all: unittest_selftest stacktest primtest parsetest inlinetest interp

check: all
	./unittest_selftest
	./stacktest
	./primtest
	./parsetest
	./inlinetest

unittest_selftest: unittest_selftest.c unittest.c
	$(CC) unittest.c unittest_selftest.c -o unittest_selftest

stacktest: stacktest.c unittest.c
	$(CC) unittest.c stacktest.c ../$(PRE)stack.c $(CFLAGS) -o stacktest

primtest: primtest.c unittest.c ../*.c
	$(CC) unittest.c primtest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o primtest

parsetest: parsetest.c unittest.c ../*.c
	$(CC) unittest.c parsetest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o parsetest

inlinetest: inlinetest.c unittest.c ../*.c
	$(CC) inlinetest.c unittest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o inlinetest

deftest: deftest.c unittest.c ../*.c
	$(CC) deftest.c unittest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o deftest

interp: interp.c unittest.c ../*.c
	$(CC) interp.c unittest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o interp
