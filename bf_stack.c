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

void bf_init_stack(bf_stack *stack)
{
	cell i;

	stack->tos=0;
	for(i=0;i<BF_STACK_ITEMS;i++)
	stack->items[i]=0;
}

cell bf_tos(bf_stack *stack)
{
	return (stack->items[stack->tos]);
}

cell bf_pop(bf_stack *stack)
{
	/* thanks to gargaj, for his code snippet, modulo
	 * is really really useful. and I didn't found it myself.
	 * BIG Thanks for your little code snippet, you are 
	 * my hero of the day */
	cell back=stack->items[stack->tos];
	stack->items[stack->tos]=0;
	stack->tos=(stack->tos-1)%BF_STACK_ITEMS;

	return back;
}

void bf_push(bf_stack *stack, cell value)
{
	stack->tos=(stack->tos+1)%BF_STACK_ITEMS;
	stack->items[stack->tos]=value;
}
