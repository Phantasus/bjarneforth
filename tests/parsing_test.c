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
test_reading_words_without_input ()
{
  bf_state state;
  bf_stream mystream;
  char mybuffer[] = "";
  char *str;

  BEGIN_TEST;

  bf_init_state (&state);
  bf_allot (&state, 4048);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);
  
  bf_init_vm (&state);
  
  bf_open_memstream (&state.input, mybuffer, sizeof(mybuffer));
  bf_prim_parse_name (&state); /* parsing empty */

  ASSERT_EQUAL (bf_size_dstack (&state), 2, "Should be two elements");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 0, "Should be empty string");
  str = bf_pop_dstack_char_ptr (&state);

  ASSERT_EQUAL (str[0], 0, "Should be accessible but point to zero");

  bf_free_state (&state);
  END_TEST;
}

void
test_reading_words ()
{
  bf_state state;
  bf_stream mystream;
  char mybuffer[] = "one two three";
  char *str;
  
  BEGIN_TEST;

  bf_init_state (&state);
  bf_allot (&state, 4048);
  bf_allot_dstack (&state, 64);
  bf_allot_rstack (&state, 64);
  
  bf_init_vm (&state);
  
  bf_open_memstream (&state.input, mybuffer, sizeof(mybuffer));

  bf_prim_parse_name (&state); /* parsing one */

  ASSERT_EQUAL (bf_size_dstack (&state), 2, "Should show two elements on stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 3, "First should be the length of 'one'");

  /* Secondly should be the pointer to 'one' */
  str = bf_pop_dstack_char_ptr (&state);
  ASSERT_EQUAL (str[0], 'o', "Should be 'o' of 'one'");
  ASSERT_EQUAL (str[1], 'n', "Should be 'n' of 'one'");
  ASSERT_EQUAL (str[2], 'e', "Should be 'e' of 'one'");
  ASSERT_EQUAL (str[3], '\0', "Should be NULL for being handled in C");

  bf_prim_parse_name (&state); /* parsing two */

  ASSERT_EQUAL (bf_size_dstack (&state), 2, "Should show two elements on stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 3, "First should be the length of 'two'");

  str = bf_pop_dstack_char_ptr (&state);
  ASSERT_EQUAL (str[0], 't', "Should be 't' of 'two'");
  ASSERT_EQUAL (str[1], 'w', "Should be 'w' of 'two'");
  ASSERT_EQUAL (str[2], 'o', "Should be 'o' of 'two'");
  ASSERT_EQUAL (str[3], '\0', "Should be NULL for being handled in C");

  bf_prim_parse_name (&state); /* parsing three */
  ASSERT_EQUAL (bf_size_dstack (&state), 2, "Should show two elements on stack");
  ASSERT_EQUAL (bf_pop_dstack_int (&state), 5, "First should be the length of 'three'");

  str = bf_pop_dstack_char_ptr (&state);
  ASSERT_EQUAL (str[0], 't', "Should be 't' of 'three'");
  ASSERT_EQUAL (str[1], 'h', "Should be 'h' of 'three'");
  ASSERT_EQUAL (str[2], 'r', "Should be 'r' of 'three'");
  ASSERT_EQUAL (str[3], 'e', "Should be 'e' of 'three'");
  ASSERT_EQUAL (str[4], 'e', "Should be 'e' of 'three'");
  ASSERT_EQUAL (str[5], '\0', "Should be NULL for being handled in C");
  
  bf_free_state (&state);
  END_TEST;
}

int
main ()
{
  test_reading_words_without_input ();
  test_reading_words ();
  
  return 0;
}
