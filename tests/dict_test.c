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
#include "unittest.h"
#include <string.h>

void
test_aligning_data ()
{
  bf_state state;
  char *here;
  cell *memory;
  cell value;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);

  memory = state.here;
  here = (char *)state.here;

  bf_inlinebyte (&state, 14);

  ASSERT_EQUAL ((intptr_t)state.here - (intptr_t)here, 1, "Should be one byte diff");

  bf_align (&state);
  ASSERT_EQUAL ((intptr_t)state.here - (intptr_t)here, sizeof (cell), "Should be a diff of one cell");

  for (size_t i = 1; i < sizeof (cell); i++)
    ASSERT_EQUAL (here[i], 0, "Alignment bytes should be zero", i);

  bf_inlineint (&state, 15);
  value = memory[1];
  
  ASSERT_EQUAL (value.signed_value, 15, "Should be 15 after alignment");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_inlining_empty_string ()
{
  bf_state state;

  BEGIN_TEST;
  bf_init_state (&state);
  bf_allot (&state, 1024);

  char *here = (char *)state.here;

  bf_inlinestring (&state, "");
  
  ASSERT_EQUAL ((intptr_t)state.here - (intptr_t)here, 1, "Should be one byte count for just the count");
  ASSERT_EQUAL (here[0], 0, "Should be zero");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_inlining_string ()
{
  bf_state state;

  BEGIN_TEST;
  bf_init_state (&state);
  bf_allot (&state, 1024);

  char *here = (char *)state.here;

  bf_inlinestring (&state, "abc");
  
  ASSERT_EQUAL ((intptr_t)state.here - (intptr_t)here, 4, "Should be a two byte count for just the count");
  ASSERT_EQUAL (here[0], 3, "The string length should be 3");
  
  ASSERT_EQUAL (here[1], 'a', "Should be 'a'");
  ASSERT_EQUAL (here[2], 'b', "Should be 'b'");
  ASSERT_EQUAL (here[3], 'c', "Should be 'c'");
  
  bf_free_state (&state);
  
  END_TEST;
}

void
test_inlining_words ()
{
  bf_state state;
  bf_word word;
  cell *dstart;
  cell cell_value;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);

  dstart = state.here;
  
  word.prev.signed_value = 1;
  word.flags.unsigned_value = hidden_word;
  word.dofield.signed_value = 13;
  word.argfield.signed_value = 14;

  ASSERT_EQUAL (state.last, NULL, "Before the first entry last should be zero");

  bf_inline_word (&state, &word);

  int word_size = (intptr_t)state.here - (intptr_t)dstart;

  ASSERT_EQUAL (word_size, sizeof (cell) * 4, "Should inline 4 cells");

  cell_value = dstart[0];
  ASSERT_EQUAL (cell_value.signed_value, 1, "prev should be 1");
  
  cell_value = dstart[1];
  ASSERT_EQUAL (cell_value.signed_value, hidden_word, "flags should be hidden_word");

  cell_value = dstart[2];
  ASSERT_EQUAL (cell_value.signed_value, 13, "dofield should be 14");

  cell_value = dstart[3];
  ASSERT_EQUAL (cell_value.signed_value, 14, "argfield should be 14");

  bf_free_state (&state);
  
  END_TEST;
}

void
test_looking_up_words ()
{
  bf_state state;
  cell *dstart;
  cell *last;
  char *expected_xt;
  char *word_name;

  size_t name_pad;
  size_t name_length;
  char *name_end;

  bf_word *word_body;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  bf_allot (&state, 1024);

  dstart = state.here;

  bf_define_literal (&state, "one", 1);
  bf_define_literal (&state, "two", 2);
  bf_define_literal (&state, "three", 3);
 
  last = state.last;

  word_name = (char *)last;
  name_length = word_name[0];
  name_end = &word_name[name_length - 1];
  name_pad = sizeof (cell) - ((intptr_t)name_end % sizeof (cell));

  ASSERT_EQUAL (name_length, 5, "The wordname of three is 5");
  ASSERT_EQUAL (word_name[1], 't', "Should be 't'");
  ASSERT_EQUAL (word_name[2], 'h', "Should be 'h'");
  ASSERT_EQUAL (word_name[3], 'r', "Should be 'r'");

  word_body = (bf_word *)&word_name[name_length + name_pad - 1]; 
  ASSERT_EQUAL ((intptr_t)word_body % sizeof(cell), 0, "Should be aligned on cell");

  word_name = word_body->prev.ptr_value;
  name_length = word_name[0];
  name_end = &word_name[name_length - 1];
  name_pad = sizeof (cell) - ((intptr_t)name_end % sizeof (cell));

  ASSERT_EQUAL (name_length, 3, "The wordname of two is 3");
  ASSERT_EQUAL (word_name[1], 't', "Should be 't'");
  ASSERT_EQUAL (word_name[2], 'w', "Should be 'w'");
  ASSERT_EQUAL (word_name[3], 'o', "Should be 'o'");

  word_body = (bf_word *)&word_name[name_length + name_pad - 1]; 
  expected_xt = (char *)&word_body->dofield;

  char str[] = "two";
  bf_push_dstack_char_ptr (&state, str);
  bf_push_dstack_int (&state, sizeof (str) - 1);

  ASSERT_EQUAL (bf_size_dstack (&state), 2,"Should be two items on the stack");

  bf_prim_lookup (&state);
  
  ASSERT_EQUAL (bf_size_dstack (&state), 1,"Should be one result on the stack");
  ASSERT_EQUAL (bf_pop_dstack_char_ptr (&state), expected_xt, "Lookup should produce the expected XT");

  bf_free_state (&state);
  END_TEST;
}

int
main ()
{
  test_aligning_data ();
  test_inlining_empty_string ();
  test_inlining_string ();
  test_inlining_words ();

  test_looking_up_words ();
  
  return 0;
}
