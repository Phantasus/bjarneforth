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

/**
 * This unittest does check the stack primitives of bootforth
 */


#include <bf_stack.h>
#include <stdio.h>
#include "unittest.h"

int
main ()
{
  int i, last;
  int count_in = 0;
  int count_out = 0;
  
  bf_stack stack;
  bf_init_stack (&stack);

  ASSERT_EQUAL (0, bf_stack_size(&stack), "Empty stack has size zero");
  bf_stack_push_int (&stack, 13);

  ASSERT_EQUAL (1, bf_stack_size(&stack), "Stack after first push has size one");
  ASSERT_EQUAL (13, bf_stack_pop_int (&stack), "First element popped should be 13");
  ASSERT_EQUAL (0, bf_stack_size(&stack), "Stack after first pop should be zero");

  for (i = 1; i < BF_STACK_ITEMS; i++)
    {
      bf_stack_push_int (&stack, i);
      if (i == stack.tos)
        count_in++;
    }

  cell tos = bf_stack_tos (&stack);
  ASSERT_EQUAL (tos.unsigned_value, BF_STACK_ITEMS - 1, "TOS should work");
  ASSERT_EQUAL (count_in, BF_STACK_ITEMS - 1, "Stack pushing works");
  ASSERT_EQUAL (count_in, bf_stack_size(&stack), "Getting stack size works");

  for (i = BF_STACK_ITEMS; i > 0; i--)
    {
      last = bf_stack_pop_int (&stack);
      if (last == (i - 1))
        count_out++;
    }
  ASSERT_EQUAL (count_out, BF_STACK_ITEMS, "Stack popping works");
  ASSERT_EQUAL (0, bf_stack_size(&stack), "After everything was popped stack has size zero");

  return 0;
}
