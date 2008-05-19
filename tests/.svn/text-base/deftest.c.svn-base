#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>

void helloprim(bf_state *state)
{
	printf("\nI'm a primitive, beware of me!\n");
}

int main()
{

	printf("deftest\n");
	bf_state state;

	bf_init_state(&(state)); 
	bf_allot(&(state.memory), 1024);
	state.vars.tib=(char *)&state.memory.content[512];
	bf_init_stack(&state.dstack);

	bf_def_prim(&state, "barbie", &helloprim);
	bf_def_literal(&state, "theonlytruth", 42);

	printf("prompt>");
	bf_push(&state.dstack, '\n'); 
	parse(&state);
	dots(&state); newline(&state);
	eval(&state);
	dots(&state);
	newline(&state);

	return 0;
}
