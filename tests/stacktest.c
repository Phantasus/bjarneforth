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

#include <bf_stack.h>
#include <stdio.h>

int main()
{
	cell i;
	bf_stack stack;
	bf_init_stack (&stack);

	for (i=0; i<=BF_STACK_ITEMS+2; i++) {
    printf ("%d IN: %d tos: %d\n", i, i, stack.tos);
    bf_push (&stack, i);
	}
	
	for (i=0; i<=BF_STACK_ITEMS+2; i++)
    printf ("%d OUT: %d tos: %d\n",i, bf_pop(&stack), stack.tos);
	
	return 0;
}
