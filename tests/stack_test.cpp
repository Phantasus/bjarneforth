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
#include <bf_memory.h>
#include <stdio.h>
#include "unittest.h"

#define STACK_SIZE 64

void
test_stack_init ()
{
  bf_memory mymemory;
  bf_stack stack;

  BEGIN_TEST;

  bf_init_memory (&mymemory);
  bf_init_stack (&stack);

  ASSERT_EQUAL (stack.size, 0, "Should be zero");
  ASSERT_EQUAL (stack.tos, NULL, "Should be zero");
  ASSERT_EQUAL (stack.items, NULL, "Should be zero");

  ASSERT_EQUAL (bf_stack_size(&stack), 0, "Should be the expected stack size");
  ASSERT_EQUAL (bf_stack_depth(&stack), 0, "Should be zero depth");

  END_TEST;
}

void
test_stack_writing ()
{
  bf_memory mymemory;
  bf_stack stack;
  cell *here;

  size_t stack_size = 10;

  BEGIN_TEST;
  
  bf_init_memory (&mymemory);
  bf_allot_memory (&mymemory, 1024);

  here = mymemory.content;
  
  bf_init_stack (&stack);
  bf_allot_stack (&stack, &mymemory, &here, stack_size);

  ASSERT_EQUAL (bf_stack_size(&stack), stack_size, "Should be the expected stack size");
  ASSERT_EQUAL (bf_stack_depth(&stack), 0, "Should be zero depth");

  END_TEST;
}

void
test_stack_operations ()
{
  int i, last;
  int count_in = 0;
  int count_out = 0;
  cell *here    = NULL;
  
  bf_memory mymemory;
  bf_stack stack;

  
  BEGIN_TEST;
  
  bf_init_memory (&mymemory);
  bf_allot_memory (&mymemory, 1024);

  here = mymemory.content;

  bf_init_stack (&stack);
  bf_allot_stack (&stack, &mymemory, &here, STACK_SIZE);

  ASSERT_EQUAL (bf_stack_size(&stack), STACK_SIZE, "Empty stack has expected size");
  ASSERT_EQUAL (bf_stack_depth(&stack), 0, "Empty stack has depth of zero");
  bf_stack_push_int (&stack, 13);
  
  ASSERT_EQUAL (bf_stack_depth(&stack), 1, "Stack after first push has size one");
  ASSERT_EQUAL (bf_stack_pop_int (&stack), 13, "First element popped should be 13");
  ASSERT_EQUAL (0, bf_stack_depth(&stack), "Stack after first pop should be zero");

  for (i = 1; i < STACK_SIZE; i++)
    {
      bf_stack_push_int (&stack, i);
      if (i == bf_stack_depth(&stack))
        count_in++;
    }

  cell tos = bf_stack_tos (&stack);
  ASSERT_EQUAL (tos.unsigned_value, STACK_SIZE - 1, "TOS should work");
  ASSERT_EQUAL (count_in, STACK_SIZE - 1, "Stack pushing works");
  ASSERT_EQUAL (count_in, bf_stack_depth(&stack), "Getting stack size works");

  for (i = STACK_SIZE; i > 0; i--)
    {
      last = bf_stack_pop_int (&stack);
      if (last == (i - 1))
        count_out++;
    }
  ASSERT_EQUAL (count_out, STACK_SIZE, "Stack popping works");
  ASSERT_EQUAL (0, bf_stack_depth(&stack), "After everything was popped stack has size zero");

  bf_free_memory (&mymemory);

  END_TEST;
}

int
main ()
{
  test_stack_init ();
  test_stack_writing ();
  test_stack_operations ();
  
  return 0;
}
