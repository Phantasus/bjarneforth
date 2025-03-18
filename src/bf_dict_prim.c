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

/* DOC: converts a xt to a word token (wt) */
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
bf_prim_lookup (bf_state *state)	/* ( sadr sc -- xt ) */
{
  cell last;
  cell lastwt;
  cell word_prev;
  cell value;
  
  bf_word *word;
  size_t strlength;

  char *str;
  char *word_name;

  strlength = bf_pop_dstack_uint (state);
  str       = bf_pop_dstack_char_ptr (state);

  last.cell_ptr = state->last;
  word          = (bf_word *)last.cell_ptr;

  if (str && strlength)
    {
      while (word)
	{
	  word_name = (word->name).char_ptr;	/* name ptr */

	  if (!(word->flags.unsigned_value & hidden_word))
	    {
	      if (word->name_length.unsigned_value == strlength)
		{
		  if (!strncmp (word_name, &str[1], strlength))
		    {
		      lastwt.char_ptr = BF_WORD_WT(word);
                      state->lastwt = lastwt.cell_ptr;
                      
		      bf_push_dstack_char_ptr (state, BF_WORD_XT(word));
                      
		      return;
		    }
		}
	    }
          word_prev = word->prev;
	  word = (bf_word *)word_prev.cell_ptr;
	}
    }
  /* when word wasn't found */
  for (size_t i = 0; i < strlength; i++)
    {
      value.signed_value = str[i];
      
      bf_putc (&(state->output), value);
    }
  value.unsigned_value = '?';
  bf_putc (&(state->output), value);
  bf_push_dstack_int (state,  0);
}
