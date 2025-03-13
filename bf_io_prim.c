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

/* fname: space */
/* DOC: prints a space */
void
bf_prim_space (bf_state *state)	/* ( -- ) */
{
  bf_push_dstack_int (state, BF_CHAR_SPACE);
  bf_prim_emit (state);
}

/* fname: . */
/* DOC: prints TOS as a number with a following space */
void
bf_prim_dot (bf_state *state)	/* ( number -- ) */
{
  cell value = bf_pop_dstack (state);
  printf ("%d ", value.signed_value);
}

/* DOC: prints TOS as a number without a following space */
void
bf_prim_printtos (bf_state *state)	/* ( number -- ) */
{
  cell value = bf_pop_dstack (state);
  printf ("%d", value.signed_value);
}

/* DOC: prints the character which is matching to value */
void
bf_prim_emit (bf_state *state)	/* ( value -- ) */
{
  cell value = bf_pop_dstack (state);
  bf_putc (&(state->output), value);
}

/* DOC: prints a newline */
void
bf_prim_newline (bf_state *state)	/* ( -- ) */
{
  bf_push_dstack_int (state, BF_CHAR_NEWLINE);
  bf_prim_emit (state);
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

/* fname: .s */
/* DOC: prints elements on the stack,
 *      without removing them from the stack */
void
bf_prim_dots (bf_state *state)	/* ( -- ) */
{
  size_t i;
  cell value;
  size_t stack_size = bf_size_dstack(state);

  for (i = 0; i < stack_size; i++)
    {
      value = bf_stack_get_at(&state->dstack, i);
      bf_push_dstack (state, value);
      bf_prim_dot (state);
    }
  fflush (stdout);

#ifdef DEBUG
  printf ("\n");
#endif
}

/* DOC: reads a string from input until it finds a whitespace character */
void
bf_prim_wsparse (bf_state *state)	/* ( -- ) */
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

  unsigned int i     = 0;
  char *addr         = bf_pop_dstack_char_ptr (state);

  bf_push_dstack_char_ptr (state, state->tib);

  if (state->flags & flag_eol)
    state->flags = state->flags & (~flag_eol);

  buf = bf_getc (&(state->input));
  while ((char_isexcluded (addr, count, buf)) &&
         (i < state->tibsize) &&
         (buf.unsigned_value != EOF))
    {
      state->tib[i] = (char) buf.unsigned_value;
      i++;
      buf = bf_getc (&(state->input));
    }

  if (buf.unsigned_value == '\n')
    state->flags |= flag_eol;

  bf_push_dstack_uint (state, i);
}

