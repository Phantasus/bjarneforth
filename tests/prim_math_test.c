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

#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>
#include <string.h>
#include "unittest.h"

void
test_prim_add ()
{
  bf_state state;
  
  BEGIN_TEST;

  bf_init_state (&state);

  bf_push_dstack_int(&state, 1);
  bf_push_dstack_int(&state, 1);

  bf_prim_add (&state);
  
  ASSERT_EQUAL (bf_size_dstack (&state), 1, "Only one item should be on the stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 2, "Should be 1 + 1 = 2");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_prim_sub ()
{
  bf_state state;
  
  BEGIN_TEST;

  bf_init_state (&state);

  bf_push_dstack_int(&state, 10);
  bf_push_dstack_int(&state, 1);

  bf_prim_sub (&state);
  
  ASSERT_EQUAL (bf_size_dstack (&state), 1, "Only one item should be on the stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 9, "Should be 10 - 1 = 9");

  bf_push_dstack_int(&state, 5);
  bf_push_dstack_int(&state, 10);

  bf_prim_sub (&state);
  ASSERT_EQUAL (bf_pop_dstack_int (&state), -5, "Should be 5 - 10 = -5");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_prim_mul ()
{
  bf_state state;
  
  BEGIN_TEST;

  bf_init_state (&state);

  bf_push_dstack_int(&state, 2);
  bf_push_dstack_int(&state, 3);

  bf_prim_mul (&state);
  
  ASSERT_EQUAL (bf_size_dstack (&state), 1, "Only one item should be on the stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 6, "Should be 2 * 3 = 6");

  bf_push_dstack_int(&state, -5);
  bf_push_dstack_int(&state, 10);

  bf_prim_mul (&state);
  ASSERT_EQUAL (bf_pop_dstack_int (&state), -50, "Should be -5 * 10 = -50");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_prim_div ()
{
  bf_state state;
  
  BEGIN_TEST;

  bf_init_state (&state);

  bf_push_dstack_int(&state, 12);
  bf_push_dstack_int(&state, 3);

  bf_prim_div (&state);
  
  ASSERT_EQUAL (bf_size_dstack (&state), 1, "Only one item should be on the stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 4, "Should be 12 / 3 = 4");

  bf_free_state (&state);
  
  END_TEST;
}

int
main ()
{
  test_prim_add ();
  test_prim_sub ();
  test_prim_mul ();
  test_prim_div ();
  
  return 0;
}
