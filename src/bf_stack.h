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
 * author: 
 *
 * bootforth data stack implementation
 * */

#ifndef BF_STACKH
#include <bf_types.h>
#include <bf_defines.h>


struct bf_stack
{
	cell items[BF_STACK_ITEMS];
	cell tos;  /* index for current tos */
};
typedef struct bf_stack bf_stack;


/* atom stack operators */
void bf_init_stack(bf_stack *stack);

cell bf_tos(bf_stack *stack);
cell bf_pop(bf_stack *stack);
void bf_push(bf_stack *stack, cell value);

#define BF_STACKH
#endif 
