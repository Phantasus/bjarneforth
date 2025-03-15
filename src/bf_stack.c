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


#include <bf_stack.h>

void
bf_init_stack (bf_stack *stack)
{
  int i;

  stack->tos = 0;
  for (i = 0; i < BF_STACK_ITEMS; i++)
    stack->items[i].unsigned_value = 0;
}

cell
bf_stack_tos (bf_stack *stack)
{
  return (stack->items[stack->tos]);
}

cell
bf_stack_pop (bf_stack *stack)
{
  /* thanks to gargaj, for his code snippet, modulo
   * is really really useful. and I didn't found it myself.
   * BIG Thanks for your little code snippet, you are 
   * my hero of the day */
  cell back = stack->items[stack->tos];
  stack->items[stack->tos].unsigned_value = 0;

  stack->tos = (stack->tos - 1) % BF_STACK_ITEMS;

  return back;
}

int
bf_stack_pop_int (bf_stack *stack)
{
  cell tos = bf_stack_pop(stack);

  return tos.signed_value;
}

unsigned int
bf_stack_pop_uint (bf_stack *stack)
{
  cell tos = bf_stack_pop(stack);

  return tos.unsigned_value;
}

char *
bf_stack_pop_char_ptr (bf_stack *stack)
{
  cell tos = bf_stack_pop(stack);

  return tos.char_ptr;
}

void
bf_stack_push (bf_stack *stack, cell value)
{
  stack->tos = (stack->tos + 1) % BF_STACK_ITEMS;
  stack->items[stack->tos] = value;
}

void
bf_stack_push_int (bf_stack *stack, signed int value)
{
  cell stack_value ;
  stack_value.signed_value = value;
  
  bf_stack_push(stack, stack_value);
}

void
bf_stack_push_uint (bf_stack *stack, unsigned int value)
{
  cell stack_value ;
  stack_value.unsigned_value = value;
  
  bf_stack_push(stack, stack_value);
}

void
bf_stack_push_char_ptr (bf_stack *stack, char *value)
{
  cell stack_value ;
  stack_value.char_ptr = value;
  
  bf_stack_push(stack, stack_value);
}

size_t
bf_stack_size (bf_stack *stack)
{
  if (stack->tos > 0)
    return (size_t)stack->tos;
  
  return 0;
}

cell
bf_stack_get_at(bf_stack *stack, size_t index)
{
  cell empty_value;

  BF_CLEAR_CELL(empty_value);

  if (bf_stack_size(stack) > index)
    return stack->items[index];
  else
    return empty_value;
}
