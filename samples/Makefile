#Bootforth Makefile template
#---------------------------

#Compilers
CC=gcc # gcc compilation
#CC=mips-linux-gcc
#CC=arm-open2x-linux-gcc
#CC=tcc # tcc compilation 


#Directory of bootforth
BFDIR=../
CFLAGS=-I$(BFDIR) --ansi -Wall

#General prefix
P=$(BFDIR)

bfsc: bfsc.c $Pbf_stack.c $Pbf_state.c $Pbf_memory.c $Pbf_prim.c $Pbf_variables.c $Pbf_stream.c
	$(CC) bfsc.c $Pbf_debug.c $Pbf_stack.c $Pbf_state.c $Pbf_memory.c $Pbf_stream.c $Pbf_prim.c $Pbf_variables.c $(CFLAGS) -o bfsc
