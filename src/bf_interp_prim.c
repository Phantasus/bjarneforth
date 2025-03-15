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

/* DOC: evals a string */
void
bf_prim_eval (bf_state *state)	/* ( str strlen -- ) */
{
  cell count = bf_pop (&(state->dstack));
  cell i = 0;
  cell strc = 0;
  char *str = (char *) bf_pop (&(state->dstack));

#ifdef DEBUG_EVAL
  printf ("EVAL: ");
  for (i = 0; i < count; i++)
    printf ("%c", str[i]);

  printf ("\n");
  i = 0;
#endif

  if ((str != 0) && (count > 0))
    {
      while (i < count)
	{
	  if (char_isincluded (&state->vars.ws[1], state->vars.ws[0], str[i]))
	    {
	      if (strc > 0)
		{
		  bf_push (&(state->dstack), (cell) strc);
		  bf_push (&(state->dstack), (cell) state->vars.eachword);
		  bf_prim_execute (state);
		}
	      strc = 0;
	    }
	  else
	    {
	      if (strc == 0)
		bf_push (&(state->dstack), (cell) & str[i]);
	      strc++;
	    }
	  i++;
	}
      if (strc > 0)
	{
	  bf_push (&(state->dstack), (cell) strc);
	  bf_push (&(state->dstack), (cell) state->vars.eachword);
	  bf_prim_execute (state);
	}
    }
}

/* DOC: include the given file and evaluate it */
void
bf_prim_include (bf_state *state)	/* ( str strlen -- ) */
{
  bf_stream buf;

  cell len = bf_pop (&(state->dstack));
  char *str = (char *) bf_pop (&(state->dstack));
  char *filen = (char *) malloc (len + 1);
  FILE *file = 0;

  if ((str != 0) && (len != 0))
    {
      memcpy ((void *) filen, (void *) str, len);
      filen[len] = '\0';
      file = fopen (filen, "r");
    }

  if (file != 0)
    {
      memcpy ((void *) &buf, (void *) &(state->input), sizeof (bf_stream));
      bf_filestream (&(state->input), file);

      while (!feof ((FILE *) state->input.stream))
	{
	  bf_prim_wsparse (state);
	  bf_prim_eval (state);
	}
      memcpy ((void *) &(state->input), (void *) &buf, sizeof (bf_stream));
      fclose (file);
    }
  free ((void *) filen);
}

/* DOC: executes a xt */
void
bf_prim_execute (bf_state *state)	/* ( xt -- ) */
{
  bf_prim *xts;
  xts = (bf_prim *) bf_pop (&(state->dstack));

  if (xts != 0)
    {
      state->W = (cell *) xts;
#ifdef DEBUG
      printf ("XT: do %d arg %d\n", (int) xts[0], (int) xts[1]);
#endif

      BF_INMEMORY (state, (cell *) xts[0])
      {
	bf_push (&(state->dstack), (cell) xts[0]);
	bf_prim_execute (state);
      }
      else
      xts[0] (state);
    }
#ifdef DEBUG
  bf_prim_dots (state);
#endif
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

/* DOC: evaluates the given Forth source string, with cool C replacement */
void
bf_eval (bf_state *state, char *string, ...)
{
  bf_stream buf;
  char *out = (char *) state->vars.tib;
  va_list ap;

#ifdef DEBUG_EVAL
  printf ("eval<# %s ", string);
#endif

  va_start (ap, string);
  vsprintf (out, string, ap);
  va_end (ap);


  memcpy ((void *) &buf, (void *) &(state->input), sizeof (bf_stream));
  cell len = (cell) strlen (out);
  bf_memstream (&(state->input), (char *) out, len);

  while (state->input.pos < len)
    {
      bf_prim_wsparse (state);
      bf_prim_eval (state);
    }

  memcpy ((void *) &(state->input), (void *) &buf, sizeof (bf_stream));

#ifdef DEBUG_EVAL
  printf ("#>\n");
#endif
}

/* DOC: reads a string from input to first occurence of delimiter */
void
bf_prim_parse (bf_state *state)	/* ( delimiter -- str strlen ) */
{
  cell end = bf_pop (&(state->dstack));
  cell i = 0, buf;

  bf_push (&(state->dstack), (cell) state->vars.tib);

  if (state->vars.istate & BF_FLAG_EOL)
    state->vars.istate = state->vars.istate & (~BF_FLAG_EOL);

  buf = bf_getc (&(state->input));
  while ((buf != end) && (i < state->vars.tibsize) && (buf != EOF))
    {
      state->vars.tib[i] = (char) buf;
      i++;
      buf = bf_getc (&(state->input));
    }
  if (buf == '\n')
    state->vars.istate |= BF_FLAG_EOL;

  bf_push (&(state->dstack), i);
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
