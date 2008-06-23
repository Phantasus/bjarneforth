/*  Copyright 2007, 2008 Josef Philip Bernhart

    This file is part of BootForth.

    BootForth is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    BootForth is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BootForth.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <bf_prim.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


/* DOC: creates a word stub in memory and returns the address to it */
cell *bf_def_stub(bf_state *state, cell *prev, char *name, bf_prim dofield, cell argfield)
{
	cell *last, *here;

	last=(cell *)state->vars.dhere;
	here=state->vars.here;
	state->vars.here=state->vars.dhere;
        bf_inlinecell(state, (cell)prev);
        bf_inlinecell(state, (cell)name);

	bf_inlinecell(state, (cell)dofield);
        bf_inlinecell(state, (cell)argfield);
        state->vars.last=last;
	state->vars.dhere=state->vars.here;
	state->vars.here=here;
	
	#ifdef DEBUG
	printf("def name: %s do: %d arg: %d\n", name,(int)dofield,(int)argfield);
	if(dofield==0 || argfield==0) printf("ZERO REF\n");
	#endif
	return last;
}

/* DOC: defines a word with the given name, dofield value and argfield value */
cell *bf_def_word(bf_state *state, const char *name, unsigned char flags, bf_prim dofield, cell argfield)
{	
        unsigned char count=strlen(name);
	char *string=(char *)state->vars.here;
	cell i;
	
	/* max word name length = 31 characters, that's for example
	 * eg. MrDishWasherWhoIsAGreatMoronPIG, to make room for the flags */
	count=count&BF_WORD_LENMASK;
	count=count|flags;

	bf_inlinebyte(state, (byte)count);
	count=count&BF_WORD_LENMASK;
	for(i=0;i<count;i++)
	bf_inlinebyte(state, name[i]);

	/* alignment */
	while((cell)(state->vars.here)%(sizeof(cell))>0) 
	bf_inlinebyte(state, (byte)0);
	

	return bf_def_stub(state, state->vars.last, string, dofield, argfield);
}

/* DOC: defines a normal primitive */
cell *bf_def_prim(bf_state *state, const char *name, bf_prim primitive)
{
	return bf_def_word(state, name, BF_WORD_NORMAL, &prim_doprim, (cell)primitive);
}

/* DOC: defines a normal literal */
cell *bf_def_literal(bf_state *state, const char *name, cell value)
{
	return bf_def_word(state, name, BF_WORD_NORMAL, &prim_doliteral, value);
}

/* DOC: defines an imediate primitive */
cell *bf_def_iprim(bf_state *state, const char *name, bf_prim primitive)
{
	return bf_def_word(state, name, BF_WORD_ALLTIME, &prim_doprim, (cell)primitive);
}

/* DOC: defines an imediate literal */
cell *bf_def_iliteral(bf_state *state, const char *name, cell value)
{
	return bf_def_word(state, name, BF_WORD_NORMAL, &prim_doliteral, value);
}

/* DOC: evaluates the given Forth source string, with cool printf substitutions */
void bf_eval(bf_state *state, char *string, ...)
{
	bf_stream buf;
	char *out=state->vars.tib;
	va_list ap; 

	#ifdef DEBUG_EVAL
	printf("eval<# \"%s\" adr: %d<>", string, string);
	#endif

	va_start(ap, string);
	vsprintf(out, string, ap);
	va_end(ap);

	memcpy((void *)&buf, (void *)&(state->input), sizeof(bf_stream));
	cell len=(cell)strlen(out);
	bf_memstream(&(state->input), (char *)out, len);

	while(state->input.pos<len)
	{
		prim_wsparse(state);
		prim_eval(state);
	}

	memcpy((void *)&(state->input), (void *)&buf, sizeof(bf_stream));

	#ifdef DEBUG_EVAL
	printf("#> len: %d\n", len);
	#endif
}

/* DOC: initializes the VM related and the internal primitives */
void bf_init_vm(bf_state *state)
{
	state->vmprims=bf_def_iprim(state, "pushliteral", &prim_pushliteral);
	bf_def_iprim(state, "pushsliteral", &prim_pushsliteral);
	bf_def_iprim(state, "jmp", &prim_jmp);
	bf_def_iprim(state, "jmpiftrue", &prim_jmpiftrue);
	bf_def_iprim(state, "jmpiffalse", &prim_jmpiffalse);
	bf_def_iprim(state, "eachword", &prim_eachword_classic);
	bf_def_iprim(state, "(does)", &prim_does);

	state->vars.eachword=(cell)BF_VM_PRIM(state, BF_VM_EACHWORD);
	state->vars.last=0; /* put it into their own vocabulary */
}

/* DOC: add the two numbers A and B together */
void prim_add(bf_state *state) /* ( A B -- A+B ) */
{
        int b=bf_pop(&(state->dstack));
        int a=bf_pop(&(state->dstack));
        int result=a+b;
 
        if(result<0) prim_setnegative(state);
        bf_push(&(state->dstack), (cell)result);	
}

/* DOC: subtract B from A */
void prim_sub(bf_state *state) /* ( A B -- A-B ) */
{
	int b=bf_pop(&(state->dstack));
	int a=bf_pop(&(state->dstack));
	int result=a-b;

	if(result<0) prim_setnegative(state);
	bf_push(&(state->dstack), (cell)result);
}

/* DOC: multiply A and B */
void prim_mul(bf_state *state) /* ( A B -- A*B) */
{
        int b=bf_pop(&(state->dstack));
        int a=bf_pop(&(state->dstack));
        int result=a*b;
 
        if(result<0) prim_setnegative(state);
        bf_push(&(state->dstack), (cell)result);
}

/* DOC: divide A through B */
void prim_div(bf_state *state) /* ( A B -- A/B ) */
{
	int b=bf_pop(&(state->dstack));
	int a=bf_pop(&(state->dstack));
	int result=a/b;
	
	if(result<0) prim_setnegative(state);
	bf_push(&(state->dstack), (cell)result);
}

/* DOC: push the result of A modulo B on the stack */
void prim_mod(bf_state *state) /* ( A B -- A%B )*/
{
        cell b=bf_pop(&(state->dstack));
        cell a=bf_pop(&(state->dstack));
        cell result=a%b;
 
        bf_push(&(state->dstack), (cell)result);
}

/* DOC: do a binary logic AND operation on A using B as bitmask */
void prim_and(bf_state *state) /* ( A B -- A&B ) */
{
	cell b=bf_pop(&(state->dstack));
	cell a=bf_pop(&(state->dstack));

	bf_push(&(state->dstack), a&b);
}

/* DOC: a binary logic OR operation on A using B as bitmask */
void prim_or(bf_state *state) /* ( A B -- A|B ) */
{
        cell b=bf_pop(&(state->dstack));
        cell a=bf_pop(&(state->dstack));

        bf_push(&(state->dstack), a|b);
}

/* DOC: A is XORed using B as a bitmask */
void prim_xor(bf_state *state) /* ( A B -- A^B ) */
{
	cell b=bf_pop(&(state->dstack));
	cell a=bf_pop(&(state->dstack));

	bf_push(&(state->dstack), a^b);
}

/* DOC: binary negate the TOS */
void prim_not(bf_state *state) /* ( A -- ~A ) */
{
        bf_push(&(state->dstack), ~bf_pop(&(state->dstack)));
}

/* DOC: shifts the second element of stack by TOS left */
void prim_lshift(bf_state *state) /* ( A B -- A<<B ) */
{
	cell b=bf_pop(&(state->dstack));
	cell a=bf_pop(&(state->dstack));
	bf_push(&(state->dstack), a<<b);
}

/* DOC: shifts the second element of stack by TOS right */
void prim_rshift(bf_state *state) /* ( A B -- A>>B ) */
{
	cell b=bf_pop(&(state->dstack));
	cell a=bf_pop(&(state->dstack));
	bf_push(&(state->dstack), a>>b);
}

#define BF_TEST_TWO_ITEMS(state, arg) \
cell b=bf_pop(&(state->dstack)); \
cell a=bf_pop(&(state->dstack)); \
if(arg) prim_settrue(state); \
else prim_setfalse(state);

/* fname: < */
/* DOC: tests if A is lower than B */
void prim_lower(bf_state *state) /* ( a b  --  ) */
{
	BF_TEST_TWO_ITEMS(state, a<b)
}

/* fname: > */
/* DOC: tests if B is greater than A */
void prim_greater(bf_state *state) /* ( a b --  ) */
{
	BF_TEST_TWO_ITEMS(state, a>b)
}

/* fname: = */
/* DOC: tests if A and B are equal */
void prim_equal(bf_state *state) /* ( a b -- ) */
{
	BF_TEST_TWO_ITEMS(state, a==b)
}

/* fname: <= */
/* DOC: tests if B is lower or equal to A */
void prim_loweq(bf_state *state) /* ( a b -- ) */
{
	BF_TEST_TWO_ITEMS(state, a<=b)
}

/* fname: >= */
/* DOC: tests if A is greater or equal to B */
void prim_greeq(bf_state *state) /* ( a b -- ) */
{
	BF_TEST_TWO_ITEMS(state, a>=b)
}

/* DOC: tests if A and B are not equal */
void prim_notequal(bf_state *state) /* ( a b -- ) */
{
	BF_TEST_TWO_ITEMS(state, a!=b)
}

/* DOC: negates the result of a true/false operation */
void prim_opposite(bf_state *state) /* ( a b -- ) */
{
	state->flags^=BF_FLAG_TRUE;
}

/* memory protection macro */
#define BF_INMEMORY(state, adr) \
if(((adr>=(cell *)state) && (adr<=(cell *)&BF_STATE_END(state))) || \
((adr>=(cell *)state->memory.content) && (adr<=(cell *)state->memory.end)))


/* fname: ! */
void prim_store(bf_state *state) /* ( value adr -- ) */
{
	cell *adr=(cell *)bf_pop(&(state->dstack));
	cell value=bf_pop(&(state->dstack));

	BF_INMEMORY(state, (cell *)adr)
	*adr=value;
}

/* fname: @ */
void prim_fetch(bf_state *state) /* ( adr -- value ) */
{
	cell *adr=(cell *)bf_pop(&(state->dstack));
	
	BF_INMEMORY(state, adr)
	bf_push(&(state->dstack), *adr);
	else bf_push(&(state->dstack), (cell)0);
}

/* fname: c! */
void prim_bstore(bf_state *state) /* ( value adr -- ) */
{
        byte *adr=(byte *)bf_pop(&(state->dstack));
        byte value=(byte)bf_pop(&(state->dstack));

	BF_INMEMORY(state, (cell *)adr)
        *adr=value;
}

/* fname: c@ */
void prim_bfetch(bf_state *state) /* ( adr -- value ) */
{
        byte *adr=(byte *)bf_pop(&(state->dstack));

	BF_INMEMORY(state, (cell *)adr)
        bf_push(&(state->dstack), (cell)*adr);
	else bf_push(&(state->dstack), (cell)0);
}

/* fname: allot */
void prim_allot(bf_state *state) /* ( amount -- ) */
{
	cell amount=bf_pop(&(state->dstack));
	state->vars.here+=amount;
}

/* fname: align */
void prim_align(bf_state *state) /* ( adr -- aligned ) */
{
	char *adr=(char *)bf_pop(&(state->dstack));
	adr+=((cell)adr)%((cell)(sizeof(cell)));
	bf_push(&(state->dstack), (cell)adr);
}

void prim_astore(bf_state *state)
{
	cell a=bf_pop(&(state->dstack));
	state->memory.a_reg=a;
}

void prim_afetch(bf_state *state)
{
	bf_push(&(state->dstack), state->memory.a_reg);
}

void prim_ainc(bf_state *state) /* ( -- ) */
{
	state->memory.a_reg++;
}

void prim_adec(bf_state *state) /* ( -- ) */
{
	state->memory.a_reg--;
}

/* DOC: copies the bytes from to to using count as a length */
void prim_copy(bf_state *state) /* ( from count to -- ) */
{
	char *to=(char *)bf_pop(&(state->dstack));
	cell count=(cell)bf_pop(&(state->dstack));
	char *from=(char *)bf_pop(&(state->dstack));
	cell i;

	for(i=0;i<count;i++) to[i]=from[i];
}

/* DOC: executes the primitive */
void prim_doprim(bf_state *state ) /* ( -- ) */
{
	bf_prim prim=(bf_prim)state->W[1];
	prim(state);
}

/* DOC: execute the literal word */
void prim_doliteral(bf_state *state) /* ( -- ) */
{
	bf_push(&(state->dstack), (cell)state->W[1]);
} 

/* DOC: just execute the link word */
void prim_dolink(bf_state *state) /* ( -- ) */
{
	bf_push(&(state->rstack), (cell)state->IP);
	state->IP=(cell *)state->W[1];
	#ifdef DEBUG
	printf("link IP %d W %d :\n", (int)state->IP, (int)state->W);
	#endif
	while((state->IP[0])!=0)
	{
		state->W=(cell *)state->IP[0];
		state->IP=&state->IP[1];
	        #ifdef DEBUG
	        printf(" IP %d W %d\n", (int)state->IP, (int)state->W);
        	#endif
		bf_push(&(state->dstack), (cell)state->W);
		prim_execute(state);
	}
	state->IP=(cell *)bf_pop(&(state->rstack));
}

/* DOC: see stack comment */
void prim_dup(bf_state *state) /* ( a -- a a ) */
{
	cell value=bf_pop(&(state->dstack));
	bf_push(&(state->dstack), value);
	bf_push(&(state->dstack), value);
}

/* DOC: see stack comment */
void prim_swap(bf_state *state) /* ( a b -- b a ) */
{
	cell a=bf_pop(&(state->dstack));
	cell b=bf_pop(&(state->dstack));

	bf_push(&(state->dstack), a);
	bf_push(&(state->dstack), b);
}

/* DOC: see stack comment */
void prim_nip(bf_state *state) /* ( a b -- b a b ) */
{
	prim_swap(state);
	prim_drop(state);
}

/* DOC: see stack comment */
void prim_tuck(bf_state *state) /* ( a b -- b ) */
{
	prim_swap(state);
	prim_over(state);
}

/* DOC: see stack comment */
void prim_drop(bf_state *state) /* ( a -- ) */
{
	bf_pop(&(state->dstack));
}

/* DOC: see stack comment */
void prim_over(bf_state *state) /* ( a b -- a b a ) */
{
	cell a=bf_pop(&(state->dstack));
	cell b=bf_pop(&(state->dstack));

	bf_push(&(state->dstack), b);
	bf_push(&(state->dstack), a);
	bf_push(&(state->dstack), b);
}

/* fname: >r */
/* DOC: pushes the TOS of dstack on the rstack */
void prim_tor(bf_state *state) /* ( value -- Rstack:value ) */
{
	bf_push(&(state->rstack), bf_pop(&(state->dstack)));
}

/* fname: r> */
/* DOC: pushes TOS from rstack to dstack */
void prim_fromr(bf_state *state) /* ( Rstack:value -- value ) */
{
	bf_push(&(state->dstack), bf_pop(&(state->rstack)));
}

/* fname: r r@ */
/* DOC: pushes TOS of the rstack on the data stack, without
 * changing the rstack */
void prim_tosr(bf_state *state) /* ( -- Rtos) */
{
	bf_push(&(state->dstack), bf_tos(&(state->rstack)));
}

/* fname: space */
/* DOC: prints a space */
void prim_space(bf_state *state) /* ( -- ) */
{
	bf_push(&(state->dstack), BF_CHAR_SPACE);
	prim_emit(state);
}

/* fname: . */
/* DOC: prints TOS as a number with a following space */
void prim_dot(bf_state *state) /* ( number -- ) */
{
	cell value=bf_pop(&(state->dstack));
	printf("%d ", (int)value);
}

/* DOC: prints TOS as a number without a following space */
void prim_printtos(bf_state *state ) /* ( number -- ) */
{
	cell value=bf_pop(&(state->dstack));
	printf("%d", (int)value);
}

/* DOC: prints the character which is matching to value */
void prim_emit(bf_state *state) /* ( value -- ) */
{
	cell value=bf_pop(&(state->dstack));
	bf_putc(&(state->output), value);
}

/* DOC: prints a newline */
void prim_newline(bf_state *state) /* ( -- ) */
{
	bf_push(&(state->dstack), BF_CHAR_NEWLINE);
	prim_emit(state);
}

/* DOC: reads a string from input to first occurence of delimiter */
void prim_parse(bf_state *state) /* ( delimiter -- str strlen ) */
{
	cell end=bf_pop(&(state->dstack));
	cell i=0,buf;

	bf_push(&(state->dstack), (cell)state->vars.tib);

	if(state->vars.istate&BF_FLAG_EOL) 
	state->vars.istate=state->vars.istate&(~BF_FLAG_EOL);
	
	buf=bf_getc(&(state->input));
	while((buf!=end) && (i<state->vars.tibsize) && (buf!=EOF))
	{
		state->vars.tib[i]=(char)buf;
		i++;
		buf=bf_getc(&(state->input));
	}
	if(buf=='\n') state->vars.istate|=BF_FLAG_EOL;
	bf_push(&(state->dstack), i);
}

int bf_isnoitem(char *list, cell n, char value)
{
	cell i=0;
	for(i=0;i<n;i++)
	{
		if(list[i]==value)
		return 0;
	}
	return 1;
}

/* DOC: reads a string from input until a character in string matches
 *      matches one input character */
void prim_sparse(bf_state *state) /* ( str strlen -- str strlen ) */
{
	cell i=0, buf;

        cell count=bf_pop(&(state->dstack));
	char *adr=(char *)bf_pop(&(state->dstack));

        bf_push(&(state->dstack), (cell)state->vars.tib);
	
	if(state->vars.istate&BF_FLAG_EOL) 
	state->vars.istate=state->vars.istate&(~BF_FLAG_EOL);

	buf=bf_getc(&(state->input)); 
        while((bf_isnoitem(adr,count, buf)) && (i<state->vars.tibsize) 
	&& (buf!=EOF)) {
		state->vars.tib[i]=(char)buf;
		i++;
		buf=bf_getc(&(state->input)); 
	} 
	if(buf=='\n') state->vars.istate|=BF_FLAG_EOL;
	bf_push(&(state->dstack), i);
}

/* DOC: reads a string from input until it finds a whitespace character */
void prim_wsparse(bf_state *state) /* ( -- ) */
{
	bf_push(&(state->dstack), (cell)&state->vars.ws[1]);
	bf_push(&(state->dstack), (cell)state->vars.ws[0]);
	prim_sparse(state);
}

/* DOC: prints the given string */
void prim_type(bf_state *state) /* ( str strlen -- ) */
{
	cell count=bf_pop(&(state->dstack));
	cell i=0;
	char *text=(char *)bf_pop(&(state->dstack));

	for(i=0; i<count; i++)
	{
		bf_putc(&(state->output), (cell)text[i]);
	}
}

/* fname: key */
/* DOC: reads one character value from the input, the 
 *      character value is a character value of an official
 *      charset. It reads the character with blocking  */
void prim_getkey(bf_state *state) /* ( -- keyvalue ) */
{
	cell key=bf_getc(&(state->input));
	bf_push(&(state->dstack), key);
}

/* fname: .s */
/* DOC: prints the first 6 elements on the stack,
 *      without removing them from the stack */
void prim_dots(bf_state *state) /* ( -- ) */ 
{
	cell elements[6];
	int i;

	for(i=0; i<6; i++) elements[i]=0;

	for(i=0; i<6; i++)
	{
		elements[i]=bf_pop(&(state->dstack));
	}
	
	for(i=5; i>=0; i--)
	{
		bf_push(&(state->dstack), elements[i]);
		prim_dot(state);
	}

	for(i=5; i>=0; i--)
	{
		bf_push(&(state->dstack), elements[i]);
	}
	fflush(stdout);

	#ifdef DEBUG
	printf("\n");
	#endif
}

/* DOC: executes a xt */
void prim_execute(bf_state *state) /* ( xt -- ) */
{
	bf_prim *xts;
	xts=(bf_prim *)bf_pop(&(state->dstack));

	if(xts!=0) {
	state->W=(cell *)xts;
	#ifdef DEBUG	
	printf("XT: %d do %d arg %d W %d ", (int)xts, (int)xts[0], (int)xts[1],(int)state->W);
	#endif

	BF_INMEMORY(state, (cell *)xts[0]) {
	#ifdef DEBUG
	printf("Inmemory - word\n");
	#endif
	bf_push(&(state->dstack), (cell)xts[1]);
	bf_push(&(state->dstack), (cell)xts[0]);
	prim_execute(state);
	}
	else { 
	#ifdef DEBUG
	printf("Notinmemory - C prim\n");
	#endif
	xts[0](state); 
	}
	}
	#ifdef DEBUG
	prim_dots(state);
	#endif
}

/* DOC: lookups a word */
void prim_lookup(bf_state *state) /* ( sadr sc -- xt ) */
{
	cell *word=state->vars.last;
	cell strlength;
	cell i=0;
	
	char *str; 
	char *sstr;

	strlength=bf_pop(&(state->dstack));
	str=(char *)bf_pop(&(state->dstack));

	if((str!=0) && (strlength!=0))
	{
		#ifdef DEBUG
		printf("\"");
                for(i=0;i<strlength;i++)
                printf("%c", str[i]);
                printf("\": ");
		#endif

		while(word!=0) 
		{
			sstr=(char *)word[BF_WORD_NAME]; /* name ptr */

			if(!(sstr[0]&BF_WORD_HIDDEN))
			{
				if((sstr[0]&BF_WORD_LENMASK)==strlength)
				{ 
					sstr=&sstr[1];
					for(i=0;i<strlength;i++)
					{
						if(str[i]!=sstr[i]) 
						break;
					}
					if(i==strlength) {
					state->vars.lastwt=(cell *)BF_WORD_WT(word);
					bf_push(&(state->dstack), (cell)BF_WORD_XT(word));
					#ifdef DEBUG
					printf("XT: %d\n", (int)BF_WORD_XT(word));
					#endif
					return;
					}
				}
			}
			word=(cell *)(word[BF_WORD_PREV]);   /* link ptr */
		}
	}
	/* when word wasn't found*/
	for(i=0;i<strlength;i++) {
	bf_putc(&(state->output), (cell)str[i]);
	}
	bf_putc(&(state->output), '?');
	bf_push(&(state->dstack), (cell)0);
}

/* DOC: include the given file and evaluate it */
void prim_include(bf_state *state) /* ( str strlen -- ) */
{
	bf_stream buf;

	cell len=bf_pop(&(state->dstack));
	char *str=(char *)bf_pop(&(state->dstack));
	char *filen=(char *)malloc(len+1);
	FILE *file=0;

	if((str!=0) && (len!=0)) {
	memcpy((void *)filen, (void *)str, len);
	filen[len]='\0';
	file=fopen(filen, "r");
	}

	if(file!=0)
	{
		memcpy((void *)&buf, (void *)&(state->input), sizeof(bf_stream));
		bf_filestream(&(state->input), file);

		while(!feof((FILE *)state->input.stream))
		{
			prim_wsparse(state);
			prim_eval(state);
		}
		memcpy((void *)&(state->input), (void *)&buf, sizeof(bf_stream));
		fclose(file);
	}
	free((void *)filen);
}

/* DOC: converts a xt to a word token (wt) */
void prim_towordtoken(bf_state *state) /* ( xt -- wt ) */
{
	cell top=bf_pop(&(state->dstack));
	bf_push(&(state->dstack), top-(2*sizeof(cell)));
}

/* DOC: evals a string */
void prim_eval(bf_state *state) /* ( str strlen -- ) */
{
	cell count=bf_pop(&(state->dstack));
	cell i=0;
	cell strc=0;
	char *str=(char *)bf_pop(&(state->dstack));

	#ifdef DEBUG_EVAL
	printf("EVAL@%d: ", count);
	for(i=0;i<count;i++) printf("%c", str[i]);
	printf("\n");
	i=0;
	#endif

	if((str!=0) && (count>0)) 
	{
		while(i<count)
		{
			if(bf_isnoitem(&state->vars.ws[1], 
			   state->vars.ws[0], str[i])) {
			
				if(strc==0) bf_push(&(state->dstack), (cell)&str[i]);
				strc++; 
			} 
			else 
			{ 
				if(strc>0) {
				bf_push(&(state->dstack), (cell)strc); 
				bf_push(&(state->dstack), (cell)state->vars.eachword);
				prim_execute(state);
				}
				strc=0;
			}
			i++;
		}
		if(strc>0) {
		bf_push(&(state->dstack), (cell)strc); 
                bf_push(&(state->dstack), (cell)state->vars.eachword);
                prim_execute(state);
		}
	}
}

/* DOC: classical Forth way of evaluating a word */
void prim_eachword_classic(bf_state *state) /* ( str strlen -- ) */
{
	cell *buf;
	char *data;

	prim_isnumber(state);
        if(state->flags&BF_FLAG_TRUE)
        {
        	prim_tonumber(state);
                if(state->vars.state) {
		#ifdef DEBUG 
		printf(",pshlit\n");
		#endif
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_PUSHLIT));
		prim_inlinecell(state);
                }
        }
        else {
	#ifdef DEBUG
	printf("STATE: %d\n", state->vars.state);
	#endif
	/* adding new word code */
        prim_lookup(state);
	prim_dup(state); 
	buf=(cell *)bf_pop(&(state->dstack));
	if(buf!=0)
	{
		buf--;
		data=(char *)*buf;

		if(data[0]&BF_WORD_ALLTIME)
        	prim_execute(state);
		else {
		if(state->vars.state) prim_inlinecell(state);
		else prim_execute(state);
		}
	}
        }
}

/* DOC: inline num as a cell to here */
void prim_inlinecell(bf_state *state) /* ( num  -- ) */
{
	bf_inlinecell(state, bf_pop(&(state->dstack)));
}

/* DOC: inline num as a byte/character to here */
void prim_inlinebyte(bf_state *state) /* ( num -- ) */
{
	cell buf=bf_pop(&(state->dstack));
	bf_inlinebyte(state, (byte)buf);
}

/* DOC: inline the string on TOS to there */
void prim_inlinestring(bf_state *state) /* ( str strlen -- ) */
{
	char *adr;
	cell count=bf_pop(&(state->dstack)),i;
	adr=(char *)bf_pop(&(state->dstack));

	#ifdef BF_USE_STRS
	cell *here=state->vars.here;
	state->vars.here=state->vars.strs;
	#endif

	bf_inlinebyte(state, count);
	for(i=0;i<count;i++)
	bf_inlinebyte(state, (cell)adr[i]);

	#ifdef BF_USE_STRS
	state->vars.strs=state->vars.here;
	state->vars.here=here;
	#endif
}

/* fnames: literal, lit, */
/* DOC: inlines a literal */
void prim_inlineliteral(bf_state *state) /* ( value -- ) */
{
	bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_PUSHLIT));
	prim_inlinecell(state);
}

/* DOC: inlines a string literal */
void prim_inlinesliteral(bf_state *state) /* ( cstr --  ) */
{
	bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_PUSHSLIT));
	prim_inlinecell(state);
}

/* DOC: create a link word and start compilation */
void prim_compile(bf_state *state) /* ( -- ) */
{
	char *name;

	prim_wsparse(state);
	state->vars.state=1;

	#ifdef BF_USE_STRS
	name=(char *)state->vars.strs;
	#endif

	#ifndef BF_USE_STRS
	name=(char *)state->vars.here;
	#endif

	prim_inlinestring(state);
	name[0]=name[0]&BF_WORD_LENMASK;
	name[0]|=(BF_WORD_NORMAL|BF_WORD_HIDDEN);

	bf_def_stub(state, state->vars.last, name, &prim_dolink, (cell)state->vars.here);
}

/* DOC: new empty word with the given name */
void prim_newword(bf_state *state) /* ( str-adr -- ) */
{
	char *name=(char *)bf_pop(&(state->dstack));
	bf_def_stub(state, state->vars.last, name, &prim_doliteral, (cell)state->vars.here);
}

/* DOC: end the the word and stop compilation, at runtime it does nothing */
void prim_endcompile(bf_state *state) /* ( -- ) */
{
	char *data=(char *)state->vars.last[BF_WORD_NAME];

	if(state->vars.state) {
	state->vars.state=0;
	bf_inlinecell(state, (cell)0);
		
	data[0]&=~BF_WORD_HIDDEN;

	#ifdef DEBUG
	printf("END");
	#endif
	}
}

/* DOC: begin at compiletime an if statement */
void prim_if(bf_state *state) /* ( -- adr ) */
{
	if(state->vars.state)
	{
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_JMPIFFALSE));
		bf_push(&(state->dstack), (cell)state->vars.here);
		bf_inlinecell(state, (cell)0);
	}
}

/* DOC: compiles an else at compiletime */
void prim_else(bf_state *state) /* ( adr -- ) */
{
	cell *adr;

	if(state->vars.state)
	{
		adr=(cell *)bf_pop(&(state->dstack));
		
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_JMP));
		bf_push(&(state->dstack), (cell)state->vars.here);
		bf_inlinecell(state, (cell)0);

		adr[0]=(cell)(state->vars.here-adr);
	}
}

/* DOC: end at compiletime an if statement */
void prim_then(bf_state *state) /* ( adr -- ) */
{
	cell *adr;

	if(state->vars.state)
	{
		adr=(cell *)bf_pop(&(state->dstack));
		adr[0]=(cell)(state->vars.here-adr);
	}
}

/* DOC: start an endless loop */
void prim_repeat(bf_state *state) /* ( -- adr )*/
{
	if(state->vars.state) 
	bf_push(&(state->dstack), (cell)state->vars.here);
}

/* DOC: end an endless loop */
void prim_loop(bf_state *state) /* ( adr -- ) */
{
	cell *adr;

	if(state->vars.state)
	{
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_JMP));
		adr=(cell *)bf_pop(&(state->dstack));
		bf_inlinecell(state, (cell)(adr-(state->vars.here)));
	}
}

/* DOC: compile at compiletime into the current defintion a word exit */
void prim_exitword(bf_state *state) /* ( -- ) */
{
	if(state->vars.state)
	bf_inlinecell(state, (cell)0);
}

/* fname: does> */
/* DOC: compiles a dodoes */
void prim_compdoes(bf_state *state) /* ( -- ) */
{
	if(state->vars.state)
	{
		#ifdef DEBUG
		printf("does>\n");
		#endif
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_PUSHLIT));
		bf_inlinecell(state, (cell)&state->vars.here[3]);
		bf_inlinecell(state, (cell)BF_VM_PRIM(state, BF_VM_DOES));
		prim_exitword(state);
	}
}

/* fname: (does) */
/* DOC: turns the latest defined word into a 'does' */
void prim_does(bf_state *state) /* ( lasthere -- ) */
{
	/* not the elegant version (more a dirty hack), sorry */

	#ifdef DEBUG
	printf("(does)\n");
	#endif
	cell *lasthere=(cell *)bf_pop(&(state->dstack));
	cell *last=(cell *)state->vars.last;
	cell *here=state->vars.here;
	char *data=(char *)last[BF_WORD_ARGF];

	cell size=((char *)here-data), i;
	
	/* inline data location */
	if(size>0)
	bf_inlinecell(state, (cell)&here[2]);
	else bf_inlinecell(state, (cell)data); 

	/* inline code location */
	bf_inlinecell(state, (cell)lasthere);
	last[BF_WORD_DOF]=(cell)&prim_dodoes;
	last[BF_WORD_ARGF]=(cell)here;

	/* copy old content to new location */
	if(size>0) {
	for(i=0;i<size;i++)
	bf_inlinebyte(state, data[i]);
	}

	/* TODO: overwriting & realigning old content */
}

/* fname: ] */
/* DOC: turns compilation on */
void prim_setstate(bf_state *state)
{
	state->vars.state=1;
}

/* fname: [ */
/* DOC: turns compilation mode off */
void prim_unsetstate(bf_state *state)
{
	state->vars.state=0;
}

/* DOC: (internal) pushes a literal value to dstack */
void prim_pushliteral(bf_state *state) /* ( -- literal ) */
{
	bf_push(&state->dstack, (cell)*(state->IP));
	state->IP++;
}

/* DOC: (internal) pushes a string literal to dstack */
void prim_pushsliteral(bf_state *state) /* ( -- str strlen ) */
{
	char *str=(char *)*(state->IP);
	bf_push(&state->dstack, (cell)&str[1]);
	bf_push(&state->dstack, (cell)str[0]);

	state->IP++;
}

/* DOC: (internal) handles a does word */
void prim_dodoes(bf_state *state)
{ 
	#ifdef DEBUG
	printf("DODOES\n");
	#endif
	cell *arg=(cell *)state->W[1];
	bf_push(&(state->dstack), (cell)arg[0]);
	state->W=arg;
	prim_dolink(state);
}

/* DOC: (internal) a relative jump emulation */
void prim_jmp(bf_state *state) /* ( -- ) */ 
{
	int* adr=(int *)state->IP;
	int offset=(int)adr[0];
	adr+=offset;
	state->IP=(cell *)adr;

	#ifdef DEBUG
	printf("JMP to: %d\n", offset);
	#endif
}

/* DOC: sets the vm flag TRUE */
void prim_settrue(bf_state *state) /* ( -- ) */
{ 
	#ifdef DEBUG
	printf("->true\n");
	#endif
	state->flags=state->flags|BF_FLAG_TRUE;
}

/* DOC: unsets the vmflag TRUE */
void prim_setfalse(bf_state *state) /* ( -- ) */
{
	#ifdef DEBUG
	printf("->false\n");
	#endif
	state->flags=state->flags&(~BF_FLAG_TRUE);
}

/* DOC: sets the vm flag NEG */
void prim_setnegative(bf_state *state) /* ( -- ) */
{
	state->flags=state->flags|BF_FLAG_NEG; 
}

/* DOC: unsets the vm flag NEG */
void prim_setpositive(bf_state *state) /* ( -- ) */
{
	state->flags=state->flags&(~BF_FLAG_NEG);
}

/* DOC: (internal) perfrom a relative jmp if TRUE flag is set */
void prim_jmpiftrue(bf_state *state) /* ( -- ) */
{
	if(state->flags&BF_FLAG_TRUE)
	prim_jmp(state);
	else 
	state->IP++;
}

/* DOC: (internal) perform a relative jmp if TRUE flag isn't set */
void prim_jmpiffalse(bf_state *state) /* ( -- ) */
{
	if(!(state->flags&BF_FLAG_TRUE))
	prim_jmp(state);
	else
	state->IP++;
}

/* DOC: set the vm TRUE flag when the string is a number, without
 *      removing it from the dstack */
void prim_isnumber(bf_state *state) /* ( str strlen -- str strlen ) */
{
	cell i, count=bf_pop(&(state->dstack)), start=0;
	char *adr=(char *)bf_pop(&(state->dstack)), buf, bbuf=state->vars.base;

	bf_push(&(state->dstack), (cell)adr);
	bf_push(&(state->dstack), (cell)count);

	if(count>0)
	{
		buf=adr[start];
		if((buf=='#') || (buf=='%') || (buf=='$')) {
		if(buf=='$') bbuf=16;
		if(buf=='#') bbuf=10;
		if(buf=='%') bbuf=2;
		start++;
		}
		buf=adr[start];
		if((buf=='-') || (buf=='+')) start++;
		if(start==count) {
		prim_setfalse(state); return;
		}
		for(i=start;i<count;i++)
		{
			buf=adr[i];
			if(!((buf<58) && (buf>47))) 
			{
				if(bbuf==16)
				{
					if((buf>96) && (buf<103))
					buf=buf&0x4f;
					#ifdef DEBUG
					printf("N&%c", buf);
					#endif
					if(!((buf>64) && (buf<71))){
					prim_setfalse(state);
					return;
					}
				}else {
				prim_setfalse(state);
				return;
				}
			}
			
		}
		prim_settrue(state); 
		return;
	}
	prim_setfalse(state);
}

/* DOC: converts the given string to a number */
void prim_tonumber(bf_state *state) /* ( str strlen -- num ) */
{
	int number=0;
	char *adr, buf;
	cell count, i, start=0, base, sign=1;

	count=(cell)bf_pop(&(state->dstack));
	adr=(char *)bf_pop(&(state->dstack));

	base=state->vars.base;

        buf=adr[start];
	switch(adr[start]) 
	{
		case '#': base=10; start++; break;
		case '%': base=2;  start++; break;
		case '$': base=16; start++; break;
	};

        buf=adr[start];
        if(buf=='-') { start++; sign=-1; }
	for(i=start;i<count;i++) 
	{
		/* that's fucking disgusting code, 
		 * I mean there must be a much better
		 * way. Perhaps I get a better idea,
		 * which works. */
		number*=base;
		if((adr[i]<58) && (adr[i]>47))
		number+=(adr[i]-48);
		if((adr[i]<91) && (adr[i]>65)) 
		number+=(adr[i]-55);
		if((adr[i]<123) && (adr[i]>96))
		number+=(adr[i]-87);
		
	}
	bf_push(&(state->dstack),(cell)(number*sign));
}

/* DOC: exits the Forth System by unsetting the RUN Flag */
void prim_bye(bf_state *state) /* ( -- ) */
{
	state->vars.istate=state->vars.istate&(~BF_FLAG_RUN);
}
