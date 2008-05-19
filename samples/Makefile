#Bootforth Makefile template
#---------------------------

#Compilers
CC=gcc # gcc compilation
#CC=tcc # tcc compilation 


#Directory of bootforth
BFDIR=../
CFLAGS=-I$(BFDIR) --ansi -Wall 

#General prefix
P=$(BFDIR)bf_


bfsc: bfsc.c $Pstack.c $Pstate.c $Pmemory.c $Pprim.c $Pvariables.c $Pstream.c
	$(CC) bfsc.c $Pdebug.c $Pstack.c $Pstate.c $Pmemory.c $Pstream.c $Pprim.c $Pvariables.c $(CFLAGS) -o bfsc
