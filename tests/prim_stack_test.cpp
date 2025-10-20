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
#include "unittest.h"

void
test_prim_tuck()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);

  bf_push_dstack_int (&state, 1);
  bf_push_dstack_int (&state, 2);
  ASSERT_EQUAL (bf_size_dstack(&state), 2, "Stack should be two items");

  bf_prim_nip (&state);
  ASSERT_EQUAL (bf_size_dstack(&state), 3, "Stack should be three items");

  ASSERT_EQUAL (bf_pop_dstack_int(&state), 2, "Should be 2");
  ASSERT_EQUAL (bf_pop_dstack_int(&state), 1, "Should be 1");
  ASSERT_EQUAL (bf_pop_dstack_int(&state), 2, "Should be 2");

  END_TEST;
}

void
test_prim_nip()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);

  bf_push_dstack_int (&state, 1);
  bf_push_dstack_int (&state, 2);
  ASSERT_EQUAL (bf_size_dstack(&state), 2, "Stack should be two items");

  bf_prim_nip (&state);
  ASSERT_EQUAL (bf_size_dstack(&state), 1, "Stack should be three items");

  ASSERT_EQUAL (bf_pop_dstack_int(&state), 2, "Should be 2");

  END_TEST;
}

void
test_prim_dup()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);

  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be zero");
  bf_push_dstack_int (&state, 1);
  bf_prim_dup (&state);
  
  ASSERT_EQUAL (bf_size_dstack(&state), 2, "Stack should be two items");

  ASSERT_EQUAL (bf_pop_dstack_int(&state), 1, "Should be 1");
  ASSERT_EQUAL (bf_pop_dstack_int(&state), 1, "Should be 1");

  END_TEST;
}

void
test_prim_drop()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);

  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be zero");
  bf_push_dstack_int (&state, 1);

  ASSERT_EQUAL (bf_size_dstack(&state), 1, "Stack should be zero");
  bf_prim_drop (&state);
  
  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be zero");

  END_TEST;
}


void
test_prim_swap()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);

  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be zero");
  bf_push_dstack_int (&state, 1);
  bf_push_dstack_int (&state, 2);
  ASSERT_EQUAL (bf_size_dstack(&state), 2, "Stack should be two items");

  bf_prim_swap (&state);
  ASSERT_EQUAL (bf_size_dstack(&state), 2, "Stack should be two items");

  ASSERT_EQUAL (bf_pop_dstack_int(&state), 1, "Should be 1");
  ASSERT_EQUAL (bf_pop_dstack_int(&state), 2, "Should be 2");

  END_TEST;
}

void
test_prim_over()
{
  bf_state state;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);

  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be zero");
  bf_push_dstack_int (&state, 1);
  bf_push_dstack_int (&state, 2);
  bf_push_dstack_int (&state, 3);
  ASSERT_EQUAL (bf_size_dstack(&state), 3, "Stack should be three items");

  bf_prim_over (&state);
  
  ASSERT_EQUAL (bf_size_dstack(&state), 4, "Should after over have four items");
  ASSERT_EQUAL (bf_pop_dstack_int(&state),  2, "Should be  2");
  ASSERT_EQUAL (bf_pop_dstack_int(&state),  3, "Should be  3");
  ASSERT_EQUAL (bf_pop_dstack_int(&state),  2, "Should be  2");
  ASSERT_EQUAL (bf_pop_dstack_int(&state),  1, "Should be  1");

  END_TEST;
}

void
test_rstack ()
{
  bf_state state;

  BEGIN_TEST;

  bf_init_state (&state);
  bf_allot (&state, 1024);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);

  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be empty");
  ASSERT_EQUAL (bf_size_rstack(&state), 0, "Return Stack should be empty");

  bf_push_dstack_int (&state, 199);
  ASSERT_EQUAL (bf_size_dstack(&state), 1, "Stack should be one item");

  bf_prim_tor (&state);
  ASSERT_EQUAL (bf_size_dstack(&state), 0, "Stack should be empty");
  ASSERT_EQUAL (bf_size_rstack(&state), 1, "Return Stack should now have one item");
  ASSERT_EQUAL (bf_tos_rstack_int (&state), 199, "Item should now be on the return stack");
  
  bf_prim_fromr (&state);
  ASSERT_EQUAL (bf_size_dstack(&state), 1, "Stack should now have one item");
  ASSERT_EQUAL (bf_size_rstack(&state), 0, "Return Stack should now be empty again");
  ASSERT_EQUAL (bf_pop_dstack_int(&state), 199, "Stack should now be 199");

  END_TEST;
}
  
int
main ()
{
  test_prim_dup ();
  test_prim_swap ();
  test_prim_drop ();
  test_prim_nip ();
  test_rstack ();

  test_prim_over ();
}
