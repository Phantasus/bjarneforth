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
#include <bf_dict.h>
#include <bf_prim.h>
#include <stdio.h>
#include <string.h>

#include "unittest.h"

void
test_eval_putting_literals ()
{
  bf_state state;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 4048);
  bf_init_vm (&state);

  bf_eval(&state, "100 12 3");

  ASSERT_EQUAL (bf_size_dstack (&state), 3, "Stack should have three items");
  ASSERT_EQUAL (bf_size_rstack (&state), 0, "Rstack should be clean after compiling");

  ASSERT_EQUAL (bf_pop_dstack_int (&state), 3, "Should be 3");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 12, "Should be 12");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 100, "Should be 100");

  bf_free_state (&state);
  END_TEST;
}

void
test_compiling_literals ()
{
  bf_state state;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 4048);
  bf_init_vm (&state);

  bf_eval(&state, ": triple ( -- a b c ) 8 9 10 ;");

  ASSERT_EQUAL (bf_size_dstack (&state), 0, "Stack should be clean after compiling");
  ASSERT_EQUAL (bf_size_rstack (&state), 0, "Rstack should be clean after compiling");

  bf_eval(&state, "triple");
  
  ASSERT_EQUAL (bf_size_dstack (&state), 3, "Stack should have three items");
  ASSERT_EQUAL (bf_size_rstack (&state), 0, "Rstack should be clean after compiling");

  ASSERT_EQUAL (bf_pop_dstack_int (&state), 10, "Should be 10");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 9, "Should be 9");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 8, "Should be 8");

  bf_free_state (&state);
  END_TEST;
}

int
main ()
{
  test_eval_putting_literals ();
  test_compiling_literals ();
  
  return 0;
}
