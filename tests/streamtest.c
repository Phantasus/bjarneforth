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
#include <bf_stream.h>
#include <stdio.h>
#include "unittest.h"

void
test_empty_stream() {
  bf_stream mystream;

  ASSERT_EQUAL (mystream.type, bf_empty_stream, "Unintialized should be the empty stream");
  ASSERT_EQUAL (mystream.pos,  0, "Position should be zero");
}

void
test_memory_stream() {
  bf_stream mystream;
  char mybuffer[] = "hello";

  bf_open_memstream(&mystream, mybuffer, sizeof(mybuffer));

  ASSERT_EQUAL (mystream.type, bf_memory_stream, "Should be a memory stream");
  ASSERT_EQUAL (mystream.pos, 0, "Position should still be zero");
  ASSERT_EQUAL (mystream.length, 6, "Length should be 6");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'h', "Reading 'h'");
  ASSERT_EQUAL (mystream.pos, 1, "Should be pos 1");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'e', "Reading 'e'");
  ASSERT_EQUAL (mystream.pos, 2, "Should be pos 2");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'l', "Reading 'l'");
  ASSERT_EQUAL (mystream.pos, 3, "Should be pos 3");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'l', "Reading 'l'");
  ASSERT_EQUAL (mystream.pos, 4, "Should be pos 4");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'o', "Reading 'o'");
  ASSERT_EQUAL (mystream.pos, 5, "Should be pos 5");

  /* we allow \0 at the end of the string, so that we can read binary data */
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 0, "Reading end-of-string");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");

  /* testing that bumping at the end of the stream causes no issues */
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 7");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 7");
  
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 7");
  
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 7");
}

void
test_stdio_stream() {
  bf_stream mystream;
  FILE *file;

  char fixture_path[] = "./fixtures/filestream.txt";
  file = fopen(fixture_path, "r");
  
  bf_open_stdstream(&mystream, file);

  ASSERT_EQUAL (mystream.type, bf_stdio_stream, "Should be a stdio stream");
  ASSERT_EQUAL (mystream.pos, 0, "Position should still be zero");
  ASSERT_EQUAL (mystream.length, -1, "Length should be unknown");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'c', "Reading 'c'");
  ASSERT_EQUAL (mystream.pos, 1, "Should be pos 1");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'o', "Reading 'o'");
  ASSERT_EQUAL (mystream.pos, 2, "Should be pos 2");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'f', "Reading 'f'");
  ASSERT_EQUAL (mystream.pos, 3, "Should be pos 3");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'f', "Reading 'f'");
  ASSERT_EQUAL (mystream.pos, 4, "Should be pos 4");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'e', "Reading 'e'");
  ASSERT_EQUAL (mystream.pos, 5, "Should be pos 5");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, 'e', "Reading 'e'");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");

  /* testing that bumping at the end of the stream causes no issues */
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");
  ASSERT_EQUAL (mystream.length, 6, "Length should be now known");

  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");
  
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");
  
  ASSERT_EQUAL (bf_getc(&mystream).signed_value, EOF, "Reading EOF");
  ASSERT_EQUAL (mystream.pos, 6, "Should be pos 6");
}

int
main () {
  test_empty_stream();
  test_memory_stream();
  test_stdio_stream();
  
  return 0;
}
