/*
 * This is the small classic interpreter 
 * it's only a template for your own forth system
 * */


#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>
#ifdef DEBUG
#include <bf_debug.h>
#endif

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

	bf_def_prim(&state, "parse", &prim_parse);
	bf_def_prim(&state, "wsparse", &prim_wsparse);
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

	bf_def_prim(&state, "<", &prim_lower);
	bf_def_prim(&state, ">", &prim_greater);
	bf_def_prim(&state, "=", &prim_equal);
	bf_def_prim(&state, "<=", &prim_loweq);
	bf_def_prim(&state, ">=", &prim_greeq);

	bf_def_prim(&state, ",", &prim_inlinecell);
	bf_def_prim(&state, "c,", &prim_inlinebyte);
	bf_def_prim(&state, "s,", &prim_inlinestring);
	
	bf_def_prim(&state, "r>", &prim_fromr);
	bf_def_prim(&state, ">r", &prim_tor);
	bf_def_prim(&state, "newword", &prim_newword);
	
	/* variables, ok they are literals which return the adr */
	bf_def_literal(&state, "here", (cell)&state.vars.here);
	bf_def_literal(&state, "last", (cell)&state.vars.last);
	bf_def_literal(&state, "cell", (cell)sizeof(cell));
	bf_def_literal(&state, "doliteral", (cell)&prim_doliteralcomp);
	bf_def_literal(&state, "doprim", (cell)&prim_doprimcomp);
	bf_def_literal(&state, "doiliteral", (cell)&prim_doliteral);
	bf_def_literal(&state, "doiprim", (cell)&prim_doprim);
	bf_def_literal(&state, "lastwt", (cell)&state.vars.lastwt);

	/* imediates */
	bf_def_iprim(&state, ";", &prim_endcompile);
	bf_def_iprim(&state, ";;", &prim_exitword);
	bf_def_iprim(&state, "if", &prim_if);
	bf_def_iprim(&state, "then", &prim_then);
	bf_def_iprim(&state, "repeat", &prim_repeat);
	bf_def_iprim(&state, "loop", &prim_loop);
	bf_def_iprim(&state, ":", &prim_compile);

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

	bf_eval(&state, ": @alltime %d last @ :dofield ! ;", (int)&prim_dolink);
	bf_eval(&state, ": @compiletime %d last @ :dofield ! ;", (int)&prim_doprim);
	bf_eval(&state, ": @runtime %d last @ :dofield ! ;", (int)&prim_doprim);

	bf_eval(&state, ": 2drop drop drop ;");

	bf_eval(&state, ": ( %d  parse 2drop ;", ')'); /* comments */
	bf_eval(&state, ": | %d  parse 2drop ;", '\n'); 
	
}

void classic_interpreter(bf_state *state, const char *prompt)
{
        while(state->vars.istate&BF_FLAG_RUN) {
        prim_wsparse(state);
	prim_eval(state);
        if(state->vars.istate&BF_FLAG_EOL) fputs(prompt, stdout);
	}	
}


int main(int argc, char **argv)
{
	bf_init_state(&(state)); 
	bf_allot(&state, 1024*64);

	state.vars.tib=(char *)&state.memory.content[1024];
	state.vars.tibsize=256;
	state.vars.dhere=&state.memory.content[2048];
	state.vars.here=&state.memory.content[5120];
	
	bf_init_vm(&state);
	
	init_dict();
	#ifdef DEBUG
	bf_dump_memory(&state, "memdump");
	#endif

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
