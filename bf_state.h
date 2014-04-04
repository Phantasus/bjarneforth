/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2014 Josef Philip Bernhart
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
 *                                                                           
 * ------------------------------------------------------------------------- */

#ifndef BF_STATEH

#include <bf_config.h>
#include <bf_types.h>
#include <bf_stack.h>
#include <bf_memory.h>
#include <bf_variables.h>
#include <bf_stream.h>

struct bf_state
{
	bf_memory memory;  /* the memory */

	bf_stack dstack; /* data stack */
	bf_stack rstack; /* return stack */

	bf_variables vars; /* variables */

	cell flags;    /* flags register */
	cell *vmprims; /* vm primitives */
	cell *IP;      /* interpreter pointer */
	cell *W;       /* work pointer */

	bf_stream input; 
	bf_stream output; 
};

typedef struct bf_state bf_state;

void bf_init_state(bf_state *state);
void bf_free_state(bf_state *state);

/* convenient functions */
void bf_inlinecell(bf_state *state, cell value);
void bf_inlinebyte(bf_state *state, byte value);
void bf_allot(bf_state *state, cell size);

/* memory protection */
#define BF_STATE_END(state) state->output

#define BF_STATEH
#endif
