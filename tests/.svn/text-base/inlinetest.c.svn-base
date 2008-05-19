#include <bf_state.h>

int main()
{
	bf_state state;
	cell i;

	printf("init state\n");
	bf_init_state(&state);
	printf("allocate memory\n");
	bf_allot(&state.memory, 512);

	printf("cell inline\n");
	for(i=1;i<20;i++){
	bf_inlinecell(&state, i);
	}

	printf("byte inline\n");
	for(i=1;i<20;i++){
	bf_inlinebyte(&state, (char)i);
	}
	bf_push(&state.dstack, (cell)state.vars.here);
	dots(&state);
	align(&state);
	dots(&state);

	return 0;
}
