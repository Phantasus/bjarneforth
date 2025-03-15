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

#include "bf_prim.h"
#include "bf_state.h"

/* DOC: set the vm TRUE flag when the string is a number, without
 *      removing it from the dstack */
void
bf_prim_isnumber(bf_state *state)	/* ( str strlen -- str strlen ) */
{
  cell i;
  int count = bf_pop_dstack_int (state);
  int start;
  
  char *adr = bf_pop_dstack_char_ptr(state);
  char buf;
  char bbuf = state->vars.base;

  bf_push_dstack_char_ptr (state, adr);
  bf_push_dstack_int (state, count);

  if (count > 0)
    {
      buf = adr[start];
      if ((buf == '#') || (buf == '%') || (buf == '$'))
	{
	  if (buf == '$')
	    bbuf = 16;
	  if (buf == '#')
	    bbuf = 10;
	  if (buf == '%')
	    bbuf = 2;
	  start++;
	}

      buf = adr[start];
      if ((buf == '-') || (buf == '+'))
	start++;
      if (start == count)
	{
	  bf_prim_setfalse (state);
	  return;
	}
      for (i = start; i < count; i++)
	{
	  buf = adr[i];
	  if (!((buf < 58) && (buf > 47)))
	    {
	      if (bbuf == 16)
		{
		  if ((buf > 96) && (buf < 103))
		    buf = buf & 0x4f;

#ifdef DEBUG
		  printf ("N&%c", buf);
#endif

		  if (!((buf > 64) && (buf < 71)))
		    {
		      bf_prim_setfalse (state);
		      return;
		    }
		}
	      else
		{
		  bf_prim_setfalse (state);
		  return;
		}
	    }

	}
      bf_prim_settrue (state);
      return;
    }
  bf_prim_setfalse (state);
}

/* DOC: converts the given string to a number */
void
bf_prim_tonumber (bf_state *state)	/* ( str strlen -- num ) */
{
  int number = 0;
  char *adr, buf;
  cell count, i, start = 0, base, sign = 1;

  count = (cell) bf_pop (&(state->dstack));
  adr = (char *) bf_pop (&(state->dstack));

  base = state->vars.base;

  buf = adr[start];
  switch (adr[start])
    {
    case '#':
      base = 10;
      start++;
      break;
    case '%':
      base = 2;
      start++;
      break;
    case '$':
      base = 16;
      start++;
      break;
    };

  buf = adr[start];
  if (buf == '-')
    {
      start++;
      sign = -1;
    }
  for (i = start; i < count; i++)
    {
      /* that's fucking disgusting code, 
       * I mean there must be a much better
       * way. Perhaps I get a better idea,
       * which works. */
      number *= base;
      if ((adr[i] < 58) && (adr[i] > 47))
	number += (adr[i] - 48);
      if ((adr[i] < 91) && (adr[i] > 65))
	number += (adr[i] - 55);
      if ((adr[i] < 123) && (adr[i] > 96))
	number += (adr[i] - 87);
    }
  bf_push (&(state->dstack), (cell) (number * sign));
}
