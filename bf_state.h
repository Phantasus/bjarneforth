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

#include "bf_config.h"
#include "bf_types.h"
#include "bf_stack.h"
#include "bf_memory.h"
#include "bf_variables.h"
#include "bf_stream.h"

struct bf_state
{
  bf_memory memory;		/* the memory */

  bf_stack dstack;		/* data stack */
  bf_stack rstack;		/* return stack */

  bf_variables vars;		/* variables */

  cell flags;			/* flags register */
  cell *vmprims;		/* vm primitives */
  cell *IP;			/* interpreter pointer */
  cell *W;			/* work pointer */

  bf_stream input;
  bf_stream output;
};

typedef struct bf_state bf_state;

void bf_init_state (bf_state * state);
void bf_free_state (bf_state * state);

/* convenient functions */
void bf_inlinecell (bf_state * state, cell value);
void bf_inlinebyte (bf_state * state, char value);
void bf_allot (bf_state * state, size_t size);

/* data stack manipulator functions */
void bf_push_dstack(bf_state *state, cell value);
void bf_push_dstack_int(bf_state *state, signed int value);
void bf_push_dstack_uint(bf_state *state, unsigned int value);
void bf_push_dstack_char_ptr(bf_state *state, char *value);

cell          bf_pop_dstack(bf_state *state);
int           bf_pop_dstack_int(bf_state *state);
char         *bf_pop_dstack_char_ptr(bf_state *state);
unsigned int  bf_pop_dstack_uint(bf_state *state);

cell          bf_tos_dstack(bf_state *state);
int           bf_tos_dstack_int(bf_state *state);
unsigned int  bf_tos_dstack_uint(bf_state *state);

/* return stack manipulator functions */
void bf_push_rstack(bf_state *state, cell value);
cell bf_pop_rstack(bf_state *state);
cell bf_tos_rstack(bf_state *state);

/* memory protection */
#define BF_STATE_END(state) state->output

#define BF_STATEH
#endif
