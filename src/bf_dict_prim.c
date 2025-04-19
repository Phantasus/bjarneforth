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
#include "bf_dict.h"
#include <stddef.h>

/* DOC: converts a xt to a word token (wt) (defunct) */
void
bf_prim_towordtoken (bf_state *state)	/* ( xt -- wt ) */
{
  cell top = bf_pop_dstack (state);
  cell word_start;

  word_start.char_ptr = top.char_ptr - offsetof(bf_word, dofield);
  
  bf_push_dstack (state, word_start);
}

/* DOC: lookups a word */
void
bf_prim_lookup (bf_state *state) /* ( sadr sc -- xt ) */
{
  cell last;
  cell lastwt;
  cell word_prev;
  cell value;
  
  bf_word *word;
  size_t strlength;
  size_t name_pad;
  size_t name_end;
  size_t i = 0;
  
  char *query;
  char *word_name;
  unsigned char name_length;

  strlength = bf_pop_dstack_int (state);
  query     = bf_pop_dstack_char_ptr (state);

  last.cell_ptr = state->last;
  word_name     = (char *)last.cell_ptr;

  if (query && strlength)
    {
      while (word_name)
	{
          name_length = (unsigned int)word_name[0];
          name_end    = (intptr_t)word_name + name_length;
          name_pad    = sizeof (cell) - (name_end % sizeof (cell));
          word        = (bf_word *)&word_name[name_length + name_pad];

	  if (!(word->flags.unsigned_value & hidden_word))
	    {
	      if (name_length == strlength)
		{
		  if (!strncmp (&word_name[1], query, strlength))
		    {
		      bf_push_dstack_char_ptr (state, (char *)&word->dofield);
                      
		      return;
		    }
		}
	    }
	  word_name = word->prev.char_ptr;
          i++;
	}
    }
  /* when word wasn't found */
  for (size_t i = 0; i < strlength; i++)
    {
      value.signed_value = query[i];
      
      bf_putc (&(state->output), value);
    }
  value.unsigned_value = '?';
  bf_putc (&(state->output), value);
  bf_push_dstack_int (state,  0);
}
