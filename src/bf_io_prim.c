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

#include "bf_state.h"
#include "bf_prim.h"

/* DOC: prints the character which is matching to value */
void
bf_prim_emit (bf_state *state)	/* ( value -- ) */
{
  cell value = bf_pop_dstack (state);
  bf_putc (&(state->output), value);
}

/* DOC: prints the given string */
void
bf_prim_type (bf_state *state)	/* ( str strlen -- ) */
{
  unsigned int i = 0;

  cell count = bf_pop_dstack (state);
  cell value;
  char *text = (char *) bf_pop_dstack_char_ptr (state);

  for (i = 0; i < count.unsigned_value; i++)
    {
      value.unsigned_value = (unsigned int) text[i];
      bf_putc (&(state->output), value);
    }
}

/* fname: key */
/* DOC: reads one character value from the input, the 
 *      character value is a character value of an official
 *      charset. It reads the character with blocking  */
void
bf_prim_getkey (bf_state *state)	/* ( -- keyvalue ) */
{
  cell key = bf_getc (&(state->input));
  bf_push_dstack (state, key);
}

/* DOC: reads a word from input */
void
bf_prim_parse_word (bf_state *state)
{
  /* parse word*/
}

/* DOC: save current input selection so that it can later be restored */
void
bf_prim_save_input (bf_state *state)
{

}

/* DOC: save current input selection so that it can later be restored */
void
bf_prim_restore_input (bf_state *state)
{

}

/* DOC: reads a string from input until it finds a whitespace character */
void
bf_prim_parse_name (bf_state *state)	/* ( -- str strlen ) */
{
  cell value;

  BF_CLEAR_CELL(value);

  value.char_ptr = &state->whitespaces[1];
  bf_push_dstack (state,  value);

  value.unsigned_value = (unsigned int)state->whitespaces[0];
  bf_push_dstack (state, value);
  bf_prim_sparse (state);
}

static int
char_isexcluded (char *list, cell length, cell value)
{
  int i = 0;
  for (i = 0; i < length.signed_value; i++)
    {
      if (list[i] == value.unsigned_value)
        return 0;
    }
  return 1;
}

/* DOC: reads a string from input until a character in string matches
 *      matches one input character */
void
bf_prim_sparse (bf_state *state)	/* ( str strlen -- str strlen ) */
{
  cell buf;
  cell count         = bf_pop_dstack (state);
  int continue_parse = 1;

  unsigned int i     = 0;
  char *addr         = bf_pop_dstack_char_ptr (state);
  char *tib          = bf_get_source_buffer (state);

  bf_push_dstack_char_ptr (state, tib);

  while (continue_parse)
    {
      buf = bf_getc (&(state->input));
      
      continue_parse = continue_parse && (char_isexcluded (addr, count, buf));
      continue_parse = continue_parse && (i < bf_size_source_buffer(state));
      continue_parse = continue_parse && (buf.signed_value != EOF);
      continue_parse = continue_parse && (buf.unsigned_value != 0);

      if (continue_parse) 
        {
          tib[i] = (char) buf.unsigned_value;
          i++;
        }
    }

  bf_push_dstack_uint (state, i);
}

