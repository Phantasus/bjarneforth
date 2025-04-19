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

/*
 * This is the small classic interpreter 
 * it's only a template for your own forth system
 * */


#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>
#ifdefine DEBUG
#include <bf_debug.h>
#endif

bf_state state;

void init_dict()
{
  /* primitives */
  bf_define_prim(&state, ".s", &prim_dots);
  bf_define_prim(&state, ".", &prim_dot);
  bf_define_prim(&state, "emit", &prim_emit);
  bf_define_prim(&state, "type", &prim_type);

  bf_define_prim(&state, "@", &prim_fetch);
  bf_define_prim(&state, "!", &prim_store);
  bf_define_prim(&state, "c@", &prim_bfetch);
  bf_define_prim(&state, "c!", &prim_bstore);

  bf_define_prim(&state, "parse", &prim_parse);
  bf_define_prim(&state, "wsparse", &prim_wsparse);
  bf_define_prim(&state, "bye", &prim_bye);

  bf_define_prim(&state, "dup", &prim_dup);
  bf_define_prim(&state, "swap", &prim_swap);
  bf_define_prim(&state, "drop", &prim_drop);
  bf_define_prim(&state, "over", &prim_over);
  bf_define_prim(&state, "nip", &prim_nip);
  bf_define_prim(&state, "tuck", &prim_tuck);

  bf_define_prim(&state, "+", &prim_add);
  bf_define_prim(&state, "-", &prim_sub);
  bf_define_prim(&state, "*", &prim_mul);
  bf_define_prim(&state, "/", &prim_div);

  bf_define_prim(&state, "<", &prim_lower);
  bf_define_prim(&state, ">", &prim_greater);
  bf_define_prim(&state, "=", &prim_equal);
  bf_define_prim(&state, "<=", &prim_loweq);
  bf_define_prim(&state, ">=", &prim_greeq);

  bf_define_prim(&state, ",", &prim_inlinecell);
  bf_define_prim(&state, "c,", &prim_inlinebyte);
  bf_define_prim(&state, "s,", &prim_inlinestring);

  bf_define_prim(&state, "r>", &prim_fromr);
  bf_define_prim(&state, ">r", &prim_tor);
  bf_define_prim(&state, "newword", &prim_newword);

  /* variables, ok they are literals which return the adr */
  bf_define_literal(&state, "here", (cell)&state.vars.here);
  bf_define_literal(&state, "last", (cell)&state.vars.last);
  bf_define_literal(&state, "cell", (cell)sizeof(cell));

  /* imediates */
  bf_define_iprim(&state, ";", &prim_endcompile);
  bf_define_iprim(&state, ";;", &prim_exitword);
  bf_define_iprim(&state, "if", &prim_if);
  bf_define_iprim(&state, "then", &prim_then);
  bf_define_iprim(&state, "repeat", &prim_repeat);
  bf_define_iprim(&state, "loop", &prim_loop);
  bf_define_iprim(&state, ":", &prim_compile);

  bf_eval(&state, ": .\" 34 parse type ;");
  bf_eval(&state, ": space %d emit ;", ' ');
  bf_eval(&state, ": cr %d emit ;", '\n');
  bf_eval(&state, ": 1+ 1 + ;");
  bf_eval(&state, ": 1- 1 - ;");
  bf_eval(&state, ": cells cell * ;");

  bf_eval(&state, ": create here @ wsparse s, newword ;");
  bf_eval(&state, ": :prev %d cells + ;", BF_WORD_PREV);
  bf_eval(&state, ": :name %d cells + ;", BF_WORD_NAME);
  bf_eval(&state, ": :dofield %d cells +  ;", BF_WORD_DOF);
  bf_eval(&state, ": :argfield %d cells +  ;", BF_WORD_ARGF);

  bf_eval(&state, ": constant create last @ :argfield ! ;");
  bf_eval(&state, ": variable create 0 , ;");

  bf_eval(&state, ": 2drop drop drop ;");

  bf_eval(&state, ": ( %d  parse 2drop ;", ')'); /* comments */
  bf_eval(&state, ": | %d  parse 2drop ;", '\n'); 
}

void classic_interpreter(bf_state *state, const char *prompt)
{
  while(state->vars.istate&BF_FLAG_RUN) {
    prim_wsparse(state);
    prim_eval(state);

    if(state->vars.istate&BF_FLAG_EOL)
      fputs(prompt, stdout);
  }	
}


int main(int argc, char **argv)
{
  const int kB=1024;

  bf_init_state(&(state));
  bf_allot(&state, (64*kB)/sizeof(cell));
  
  state.vars.tib=(char *)&state.memory.heap[0]; 
  state.vars.tibsize=kB;
  state.vars.dhere=&state.memory.heap[512];
  state.vars.strs=&state.memory.heap[2048];
  state.vars.here=&state.memory.heap[8192];
  
  bf_init_vm(&state);
  
  init_dict();

  if(argc>1) {
    bf_eval(&state, argv[1]);
  }
  else {
    printf("Bootforth\n");
    classic_interpreter(&state, "ok ");
  }
  bf_free_state(&state);

  return 0;
}
