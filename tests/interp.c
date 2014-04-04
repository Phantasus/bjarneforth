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
#include <bf_prim.h>
#include <stdio.h>

bf_state state;

void init_dict()
{
	/* primitives */
	bf_def_prim(&state, ".s", &prim_dots);
	bf_def_prim(&state, ".", &prim_dot);
	bf_def_prim(&state, "emit", &prim_emit);
	bf_def_prim(&state, "type", &prim_type);

	bf_def_prim(&state, "@", &prim_fetch);
	bf_def_prim(&state, "!", &prim_store);
	bf_def_prim(&state, "c@", &prim_bfetch);
	bf_def_prim(&state, "c!", &prim_bstore);

	bf_def_prim(&state, "cr", &prim_newline);
	bf_def_prim(&state, "space", &prim_space);
	bf_def_prim(&state, "parse", &prim_parse);
	bf_def_prim(&state, "type", &prim_type);
	bf_def_prim(&state, "bye", &prim_bye);
	
	bf_def_prim(&state, "dup", &prim_dup);
	bf_def_prim(&state, "swap", &prim_swap);
	bf_def_prim(&state, "drop", &prim_drop);
	bf_def_prim(&state, "over", &prim_over);
	bf_def_prim(&state, "nip", &prim_nip);
	bf_def_prim(&state, "tuck", &prim_tuck);
	
	bf_def_prim(&state, "+", &prim_add);
	bf_def_prim(&state, "-", &prim_sub);
	bf_def_prim(&state, "*", &prim_mul);
	bf_def_prim(&state, "/", &prim_div);

	bf_def_prim(&state, ">", &prim_lower);
	bf_def_prim(&state, "<", &prim_greater);
	bf_def_prim(&state, "=", &prim_equal);
	bf_def_prim(&state, ">=", &prim_loweq);
	bf_def_prim(&state, "<=", &prim_greeq);

	bf_def_prim(&state, ",", &prim_inlinecell);
	bf_def_prim(&state, "c,", &prim_inlinebyte);
	bf_def_prim(&state, "s,", &prim_inlinestring);
	
	/* variables, ok they are literals which return the adr */
	bf_def_literal(&state, "here", (cell)&state.vars.here);
	bf_def_literal(&state, "last", (cell)&state.vars.last);
	bf_def_literal(&state, "cell", (cell)sizeof(cell));

	/* imediates */
	bf_def_iprim(&state, ":", &prim_compile);
	bf_def_iprim(&state, ";", &prim_endcompile);
	bf_def_iprim(&state, ";;", &prim_exitword);
	bf_def_iprim(&state, "if", &prim_if);
	bf_def_iprim(&state, "then", &prim_then);
	bf_def_iprim(&state, "repeat", &prim_repeat);
	bf_def_iprim(&state, "loop", &prim_loop);
}

int main()
{
	bf_init_state(&(state)); 
	bf_allot(&state, 1024*4);

	state.vars.tib=(char *)&state.memory.content[1024];
	state.vars.tibsize=256;
	state.vars.dhere=&state.memory.content[2048];
	state.vars.here=&state.memory.content[3072];
	
	bf_init_vm(&state);
	printf("Bootforth\n");
	
	init_dict();

	while(state.vars.istate&BF_FLAG_RUN) {
	prim_wsparse(&state);
	prim_eval(&state);
	if(state.vars.istate&BF_FLAG_EOL) printf("ok ");
	}

	bf_free_state(&state);

	return 0;
}
