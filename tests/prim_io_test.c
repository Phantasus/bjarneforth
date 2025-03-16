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
#include <string.h>

void
test_prim_emit ()
{
  bf_state state;
  bf_stream mystream;
  bf_memory inmemory;
  bf_memory outmemory;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_init_memory (&inmemory);
  bf_init_memory (&outmemory);
  
  bf_allot_memory (&inmemory, 1024);
  bf_allot_memory (&outmemory, 1024);

  bf_open_memory_stream (&state.input, &inmemory);
  bf_open_memory_stream (&state.output, &outmemory);
  
  ASSERT_STR_EQUAL (state.output.content_ptr, "", "Should be empty");
  bf_push_dstack_int (&state, 'c');
  bf_push_dstack_int (&state, 'b');
  bf_push_dstack_int (&state, 'a');

  bf_prim_emit (&state);

  ASSERT_STR_EQUAL (state.output.content_ptr, "a", "Should emit a 'a'");
  bf_prim_emit (&state);

  ASSERT_STR_EQUAL (state.output.content_ptr, "ab", "Should emit a 'ab'");
  bf_prim_emit (&state);

  ASSERT_STR_EQUAL (state.output.content_ptr, "abc", "Should emit a 'abc'");
  bf_prim_emit (&state);

  bf_close_stream (&state.input);
  bf_close_stream (&state.output);

  bf_free_memory (&inmemory);
  bf_free_memory (&outmemory);

  END_TEST;
}

void
test_prim_getkey ()
{
  bf_state state;
  bf_stream mystream;
  bf_memory inmemory;
  bf_memory outmemory;

  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_init_memory (&inmemory);
  bf_init_memory (&outmemory);
  
  bf_allot_memory (&inmemory, 1024);
  bf_allot_memory (&outmemory, 1024);

  bf_open_memory_stream (&state.input, &inmemory);
  bf_open_memory_stream (&state.output, &outmemory);

  state.input.content_ptr[0] = 'g';
  state.input.content_ptr[1] = 'a';
  state.input.content_ptr[2] = 'i';
  state.input.content_ptr[3] = 'a';
  
  ASSERT_EQUAL (bf_size_dstack (&state), 0, "stack should be empty");

  bf_prim_getkey (&state);
  ASSERT_EQUAL (bf_size_dstack (&state), 1, "stack should be one cell");
  ASSERT_EQUAL (bf_tos_dstack_int(&state), 'g', "tos should be 'g'");

  bf_prim_getkey (&state);
  ASSERT_EQUAL (bf_size_dstack (&state), 2, "stack should be one cell");
  ASSERT_EQUAL (bf_tos_dstack_int(&state), 'a', "tos should be 'a'");
  
  bf_prim_getkey (&state);
  ASSERT_EQUAL (bf_size_dstack (&state), 3, "stack should be one cell");
  ASSERT_EQUAL (bf_tos_dstack_int(&state), 'i', "tos should be 'i'");

  bf_prim_getkey (&state);
  ASSERT_EQUAL (bf_size_dstack (&state), 4, "stack should be one cell");
  ASSERT_EQUAL (bf_tos_dstack_int(&state), 'a', "tos should be 'a'");

  /* cleanup */
  bf_close_stream (&state.input);
  bf_close_stream (&state.output);

  bf_free_memory (&inmemory);
  bf_free_memory (&outmemory);

  END_TEST;
}

int
main ()
{
  test_prim_emit();
  test_prim_getkey ();
  
  return 0;
}
