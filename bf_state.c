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

#include <bf_state.h>

void bf_init_state(bf_state *state)
{
	bf_init_memory(&(state->memory));

	bf_init_stack(&(state->dstack));
	bf_init_stack(&(state->rstack));
	bf_init_stream(&(state->input));
	bf_init_stream(&(state->output));

	bf_stdstream(&(state->input), stdin);
	bf_stdstream(&(state->output), stdout);

	bf_init_variables(&(state->vars));

	state->flags=0;
}

void bf_free_state(bf_state *state)
{
	bf_free_memory(&(state->memory));
	bf_free_stream(&(state->input));
	bf_free_stream(&(state->output));
	bf_free_variables(&(state->vars));
}

void bf_inlinecell(bf_state *state, cell value)
{
        state->vars.here[0]=value;
	#ifdef DEBUG
	printf("inlined: %d@%d\n", (int)state->vars.here[0],(int)state->vars.here);
	if((cell)state->vars.here%(sizeof(cell))>0) 
	printf("%d NOT ALIGNED\n", (int)state->vars.here);
	#endif
        if(state->vars.here<state->memory.end)
        state->vars.here=(cell *)&state->vars.here[1];
}

void bf_inlinebyte(bf_state *state, byte value)
{
	byte *adr=(byte *)state->vars.here;
        adr[0]=value;

        if(state->vars.here<state->memory.end)
        state->vars.here=(cell *)&adr[1];
}

void bf_allot(bf_state *state, cell size)
{
	bf_allot_memory(&state->memory, size);

	/* for bf_eval */
	state->vars.intern.evaltib=(char *)state->memory.content;
	state->memory.heap=&state->memory.content[256];
	/* end */

	state->vars.here=state->memory.heap;
	state->vars.dhere=state->memory.heap;
}

