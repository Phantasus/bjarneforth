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
  bf_stack stack;
  bf_init_stack (&stack);

  for (i = 1; i < BF_STACK_ITEMS; i++)
    {
      bf_stack_push_int (&stack, i);
      ASSERT_EQUAL (i, stack.tos, "Stack pushing");
    }

  for (i = BF_STACK_ITEMS; i > 0; i--)
    {
      last = bf_stack_pop_int (&stack);
      ASSERT_EQUAL (last, (i - 1), "Stack popping");
    }
  return 0;
}
