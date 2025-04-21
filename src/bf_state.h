/*  Copyright 2007, 2008 Josef Philip Bernhart
 *
 * This file is part of BootForth.
 *
 * BootForth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * BootForth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BootForth.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef BF_STATEH

#include "bf_types.h"
#include "bf_stack.h"
#include "bf_memory.h"
#include "bf_stream.h"

struct bf_state
{
  bf_memory memory;		/* the memory */

  bf_stack dstack;		/* data stack */
  bf_stack rstack;		/* return stack */

  /* -- used by words/primitives -- */
  size_t base;			/* current number base */

  /* memory areas */
  cell *last;			/* address of last defined word */
  cell *here;			/* address of current free heap cell */

  cell *source_buffer;   	/* text input buffer address */
  char *whitespaces;     	/* current whitespace string */
  cell *lastwt;			/* word token of last looked up word */

  enum bf_vm_flag flags;	/* flags register */

  bf_word *vmprims;		/* vm primitives */
  cell *IP;			/* interpreter pointer */
  cell *W;			/* work pointer */

  bf_stream input;
  bf_stream output;
};

typedef struct bf_state bf_state;
typedef void (*bf_prim) (bf_state * state);	/* pointer to primitives */

void bf_init_state (bf_state * state);
void bf_free_state (bf_state * state);
void bf_allot_dstack (bf_state *state, size_t size);
void bf_allot_rstack (bf_state *state, size_t size);

/* convenient functions */
void bf_inlinecell (bf_state * state, cell value);
void bf_inlineint (bf_state * state, int value);
void bf_inlineuint (bf_state * state, unsigned int value);
void bf_inlinebyte (bf_state * state, char value);
void bf_inlinestring (bf_state *state, const char *str);

void bf_allot (bf_state * state, size_t size);
void bf_align (bf_state * state);

/* data stack manipulator functions */
void bf_push_dstack(bf_state *state, cell value);
void bf_push_dstack_int(bf_state *state, signed int value);
void bf_push_dstack_uint(bf_state *state, unsigned int value);
void bf_push_dstack_char_ptr(bf_state *state, char *value);

cell          bf_pop_dstack(bf_state *state);
int           bf_pop_dstack_int(bf_state *state);
char         *bf_pop_dstack_char_ptr(bf_state *state);
unsigned int  bf_pop_dstack_uint(bf_state *state);
size_t        bf_size_dstack(bf_state *state);

cell          bf_tos_dstack(bf_state *state);
int           bf_tos_dstack_int(bf_state *state);
unsigned int  bf_tos_dstack_uint(bf_state *state);

/* return stack manipulator functions */
void    bf_push_rstack(bf_state *state, cell value);
void    bf_push_rstack_int(bf_state *state, signed int value);
void    bf_push_rstack_uint(bf_state *state, unsigned int value);
void    bf_push_rstack_char_ptr(bf_state *state, char *value);

cell             bf_pop_rstack(bf_state *state);
int              bf_pop_rstack_int(bf_state *state);
unsigned int     bf_pop_rstack_uint(bf_state *state);
char            *bf_pop_rstack_char_ptr(bf_state *state);

cell          bf_tos_rstack(bf_state *state);
int           bf_tos_rstack_int(bf_state *state);
unsigned int  bf_tos_rstack_uint(bf_state *state);

size_t  bf_size_rstack(bf_state *state);

/* flag setters */
void bf_set_negative (bf_state *state);
void bf_set_positive (bf_state *state);

void bf_print_dstack (bf_state *state);
void bf_print_rstack (bf_state *state);

cell* bf_allot_area (bf_state *state, size_t size);

size_t bf_size_source_buffer (bf_state *state);
char *bf_get_source_buffer (bf_state *state);
void bf_allot_source_buffer (bf_state *state);


#define BF_STATEH
#endif
