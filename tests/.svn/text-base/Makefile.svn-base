CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


CFLAGS=-I.. 
PRE=bf_
#CFLAGS=-I..

help: 

stacktest: stacktest.c
	$(CC) stacktest.c ../$(PRE)stack.c $(CFLAGS) -o stacktest

primtest: primtest.c ../*.c
	$(CC) primtest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o primtest

parsetest: parsetest.c ../*.c
	$(CC) parsetest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o parsetest

inlinetest: inlinetest.c ../*.c
	$(CC) inlinetest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o inlinetest

deftest: deftest.c ../*.c
	$(CC) deftest.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o deftest

interp: interp.c ../*.c
	$(CC) interp.c ../$(PRE)stack.c ../$(PRE)state.c ../$(PRE)stream.c ../$(PRE)memory.c ../$(PRE)prim.c ../$(PRE)variables.c $(CFLAGS) -o interp
