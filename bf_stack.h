/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2014, 2024, 2025 Josef Philip Bernhart
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
 * along with BootForth.  If not, see <http://www.gnu.org/licenses/>.        */
/* ------------------------------------------------------------------------- */

/*
 * bootforth data stack implementation
 * */

#ifndef BF_STACKH
#include <bf_types.h>


struct bf_stack
{
  cell items[BF_STACK_ITEMS];
  int  tos;			/* index for current tos */
};
typedef struct bf_stack bf_stack;


/* atom stack operators */
void bf_init_stack (bf_stack *stack);

cell bf_stack_tos (bf_stack *stack);
cell bf_stack_pop (bf_stack *stack);
void bf_stack_push (bf_stack *stack, cell value);

void bf_stack_push_int(bf_stack *stack, int value);
void bf_stack_push_uint(bf_stack *stack, unsigned int value);
void bf_stack_push_char_ptr(bf_stack *stack, char *ptr);

size_t       bf_stack_size(bf_stack *stack);
cell         bf_stack_get_at(bf_stack *stack, size_t index);

int          bf_stack_pop_int(bf_stack *stack);
unsigned int bf_stack_pop_uint(bf_stack *stack);
char        *bf_stack_pop_char_ptr(bf_stack *stack);

#define BF_STACKH
#endif
