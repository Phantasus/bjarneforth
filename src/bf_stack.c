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
#include <bf_memory.h>

void
bf_init_stack (bf_stack *stack)
{
  stack->tos   = NULL;
  stack->items = NULL;
  stack->size  = NULL;
}

void
bf_allot_stack (bf_stack *stack, bf_memory *mem, cell **here_ptr, size_t size)
{
  stack->size = *here_ptr;
  bf_memory_inlineuint (mem, here_ptr, size);

  stack->tos = *here_ptr;
  bf_memory_inlineint (mem, here_ptr, 0);

  stack->items = *here_ptr;
  for (size_t i = 0; i < size; i++)
    bf_memory_inlineint (mem, here_ptr, 0);
}

bf_offset
bf_stack_depth (bf_stack *stack)
{
  if (stack->tos)
    {
      cell value = *stack->tos;

      return value.signed_value;
    }

  return 0;
}

cell
bf_stack_tos (bf_stack *stack)
{
  bf_offset tos = bf_stack_depth (stack);
  
  return stack->items[tos];
}

cell
bf_stack_pop (bf_stack *stack)
{
  /* thanks to gargaj, for his code snippet, modulo
   * is really really useful. and I didn't found it myself.
   * BIG Thanks for your little code snippet, you are 
   * my hero of the day */
  cell *tos        = stack->tos; 
  size_t size      = bf_stack_size (stack);
  
  cell tos_value;
  cell old;

  old.signed_value = 0;
  
  if (tos && size > 0)
    {
      tos_value = *tos;
      old = stack->items[tos_value.signed_value];
      stack->items[tos_value.signed_value].signed_value = 0;

      if (tos_value.signed_value > 0)
        {
          tos_value.signed_value = (tos_value.signed_value - 1) % size;
          *tos = tos_value;
        }
    }

  return old;
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
  size_t   size = bf_stack_size (stack);
  
  cell tos_value;

  if (size > 0)
    {
      tos_value = *(stack->tos);
      tos_value.signed_value = (tos_value.signed_value + 1) % size;

      *(stack->tos) = tos_value;
      stack->items[tos_value.signed_value] = value;
    }
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
  if (stack && stack->size)
    {
      cell value = *stack->size;
      return (size_t)value.unsigned_value;
    }
  
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

void
bf_stack_print (bf_stack *stack)
{
  bf_offset tos = bf_stack_depth (stack);
  
  for (size_t i = 0; i <= tos; i++)
    printf ("%u ", stack->items[i]);

  printf ("(%d) \n", tos);
}
