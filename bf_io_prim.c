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
prim_space (bf_state *state)	/* ( -- ) */
{
  bf_push (&(state->dstack), BF_CHAR_SPACE);
  prim_emit (state);
}

/* fname: . */
/* DOC: prints TOS as a number with a following space */
void
prim_dot (bf_state *state)	/* ( number -- ) */
{
  cell value = bf_pop (&(state->dstack));
  printf ("%d ", (int) value);
}

/* DOC: prints TOS as a number without a following space */
void
prim_printtos (bf_state *state)	/* ( number -- ) */
{
  cell value = bf_pop (&(state->dstack));
  printf ("%d", (int) value);
}

/* DOC: prints the character which is matching to value */
void
prim_emit (bf_state *state)	/* ( value -- ) */
{
  cell value = bf_pop (&(state->dstack));
  bf_putc (&(state->output), value);
}

/* DOC: prints a newline */
void
prim_newline (bf_state *state)	/* ( -- ) */
{
  bf_push (&(state->dstack), BF_CHAR_NEWLINE);
  prim_emit (state);
}

/* DOC: prints the given string */
void
prim_type (bf_state *state)	/* ( str strlen -- ) */
{
  cell count = bf_pop (&(state->dstack));
  cell i = 0;
  char *text = (char *) bf_pop (&(state->dstack));

  for (i = 0; i < count; i++)
    {
      bf_putc (&(state->output), (cell) text[i]);
    }
}

/* fname: key */
/* DOC: reads one character value from the input, the 
 *      character value is a character value of an official
 *      charset. It reads the character with blocking  */
void
prim_getkey (bf_state *state)	/* ( -- keyvalue ) */
{
  cell key = bf_getc (&(state->input));
  bf_push (&(state->dstack), key);
}

/* fname: .s */
/* DOC: prints the first 6 elements on the stack,
 *      without removing them from the stack */
void
prim_dots (bf_state *state)	/* ( -- ) */
{
  cell elements[6];
  int i;

  for (i = 0; i < 6; i++)
    elements[i] = 0;

  for (i = 0; i < 6; i++)
    {
      elements[i] = bf_pop (&(state->dstack));
    }

  for (i = 5; i >= 0; i--)
    {
      bf_push (&(state->dstack), elements[i]);
      prim_dot (state);
    }

  for (i = 5; i >= 0; i--)
    {
      bf_push (&(state->dstack), elements[i]);
    }
  fflush (stdout);

#ifdef DEBUG
  printf ("\n");
#endif
}

/* DOC: reads a string from input until it finds a whitespace character */
void
prim_wsparse (bf_state *state)	/* ( -- ) */
{
  bf_push (&(state->dstack), (cell) & state->vars.ws[1]);
  bf_push (&(state->dstack), (cell) state->vars.ws[0]);
  prim_sparse (state);
}
