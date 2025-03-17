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
#include "xxx"

/* DOC: converts a xt to a word token (wt) */
void
bf_prim_towordtoken (bf_state *state)	/* ( xt -- wt ) */
{
  cell top = bf_pop (&(state->dstack));
  bf_push (&(state->dstack), top - (2 * sizeof (cell)));
}

/* DOC: lookups a word */
void
bf_prim_lookup (bf_state *state)	/* ( sadr sc -- xt ) */
{
  cell *word = state->vars.last;
  cell strlength;
  cell i = 0;

  char *str;
  char *sstr;

  strlength = bf_pop (&(state->dstack));
  str = (char *) bf_pop (&(state->dstack));

  if ((str != 0) && (strlength != 0))
    {
#ifdef DEBUG
      printf ("\"");
      for (i = 0; i < strlength; i++)
	printf ("%c", str[i]);

      printf ("\"");
#endif

      while (word != 0)
	{
	  sstr = (char *) word[BF_WORD_NAME];	/* name ptr */

	  if (!(sstr[0] & BF_WORD_HIDDEN))
	    {
	      if ((sstr[0] & BF_WORD_LENMASK) == strlength)
		{
		  sstr = &sstr[1];
		  for (i = 0; i < strlength; i++)
		    {
		      if (str[i] != sstr[i])
			break;
		    }
		  if (i == strlength)
		    {
		      state->vars.lastwt = (cell *) BF_WORD_WT (word);
		      bf_push (&(state->dstack), (cell) BF_WORD_XT (word));
		      return;
		    }
		}
	    }
	  word = (cell *) (word[BF_WORD_PREV]);	/* link ptr */
	}
    }
  /* when word wasn't found */
  for (i = 0; i < strlength; i++)
    {
      bf_putc (&(state->output), (cell) str[i]);
    }
  bf_putc (&(state->output), '?');
  bf_push (&(state->dstack), (cell) 0);
}
