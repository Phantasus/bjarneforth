#include <bf_stack.h>
#include <stdio.h>

int main()
{
	cell i;
	bf_stack stack;
	bf_init_stack(&stack);

	for(i=0;i<=BF_STACK_ITEMS+2;i++){
	printf("%d IN: %d tos: %d\n", i, i, stack.tos);
	bf_push(&stack, i);
	}
	
	for(i=0;i<=BF_STACK_ITEMS+2;i++){
	printf("%d OUT: %d tos: %d\n",i, bf_pop(&stack), stack.tos);
	}


	return 0;
}
