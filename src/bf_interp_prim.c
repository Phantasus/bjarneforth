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
#include <stdarg.h>

static int
char_iswhitespace (bf_state *state, char value);

/* DOC: evals a string */
void
bf_prim_eval (bf_state *state)	/* ( str strlen -- ) */
{
  size_t count = bf_pop_dstack_uint (state);
  char *str    = bf_pop_dstack_char_ptr (state);
  size_t i     = 0;
  size_t str_count; 

  if (str)
    {
      while (i < count)
	{
	  if (char_iswhitespace (state, str[i]))
	    {
	      if (str_count > 0)
		{
		  bf_push_dstack_uint (state, str_count);
		  bf_push_dstack (state, state->eachword);
		  bf_prim_execute (state);
		}
	      str_count = 0;
	    }
	  else
	    {
	      if (str_count == 0)
		bf_push_dstack_int (state, (intptr_t)&str[i]);
              
	      str_count++;
	    }
	  i++;
	}
      if (str_count > 0)
	{
	  bf_push_dstack_uint (state, str_count);
	  bf_push_dstack_uint (state, (state->eachword).unsigned_value);
	  bf_prim_execute (state);
	}
    }
}

/* DOC: include the given file and evaluate it */
void
bf_prim_include (bf_state *state)	/* ( str strlen -- ) */
{
  bf_stream stream;

  cell strlen = bf_pop_dstack (state);
  char *str   = bf_pop_dstack_char_ptr (state);
  char *filen = (char *) malloc (strlen.unsigned_value + 1);
  FILE *file  = 0;

  if (str && strlen.unsigned_value)
    {
      memcpy ((void *) filen, (void *) str, strlen.unsigned_value);
      filen[strlen.unsigned_value] = '\0';
      file = fopen (filen, "r");
    }

  if (file)
    {
      memcpy ((void *) &stream, (void *) &(state->input), sizeof (bf_stream));
      bf_open_stdstream (&(state->input), file);

      while (!feof ((FILE *) state->input.file_ptr))
	{
	  bf_prim_parse_name (state);
	  bf_prim_eval (state);
	}
      memcpy ((void *) &(state->input), (void *) &stream, sizeof (bf_stream));
      fclose (file);
      free ((void *) filen);
    }
}

/* DOC: executes a xt */
void
bf_prim_execute (bf_state *state)	/* ( xt -- ) */
{
  cell tos = bf_pop_dstack (state);
  bf_prim code_proc;

  if (tos.cell_ptr)
    {
      state->W  = tos.cell_ptr;
      code_proc = (*state->W).prim_ptr;

      code_proc (state);
    }
}

/* DOC: evaluates the given Forth source string, with cool C replacement */
void
bf_eval (bf_state *state, char *string, ...)
{
  bf_stream stream;
  va_list args;
  char *out = (char *) state->tib;
  size_t length;

  vsprintf (out, string, args);

  memcpy ((void *) &stream, (void *) &(state->input), sizeof (bf_stream));
  length = strlen (out);
  bf_open_memstream (&(state->input), (char *) out, length);

  while (state->input.pos < length)
    {
      bf_prim_parse_name (state);
      bf_prim_eval (state);
    }

  memcpy ((void *) &(state->input), (void *) &stream, sizeof (bf_stream));
}

/* DOC: reads a string from input to first occurence of delimiter */
void
bf_prim_parse (bf_state *state)	/* ( delimiter -- str strlen ) */
{
  cell end = bf_pop_dstack (state);
  size_t i = 0;
  cell buf;

  bf_push_dstack (state, (cell) state->tib);

  buf = bf_getc (&(state->input));
  while ((buf.unsigned_value != end.unsigned_value) &&
         (i < state->tibsize) &&
         (buf.signed_value != EOF))
    {
      state->tib[i] = (char) buf.signed_value;
      i++;
      buf = bf_getc (&(state->input));
    }

  bf_push_dstack_uint (state, i);
}

static int
char_isincluded (char *list, cell length, char value)
{
  int i = 0;
  for (i = 0; i < length.signed_value; i++)
    {
      if (list[i] == value)
	return 1;
    }
  return 0;
}

static int
char_iswhitespace (bf_state *state, char value)
{
  cell length;

  length.unsigned_value = state->whitespaces[0];
  
  return char_isincluded (&state->whitespaces[1], length, value);
}
