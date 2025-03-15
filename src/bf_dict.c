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


/* DOC: creates a word stub in memory and returns the address to it */
cell *
bf_def_stub (bf_state *state, cell *prev, char *name, bf_prim dofield,
	     cell argfield)
{
  cell *last, *here;

  last = (cell *) state->vars.dhere;
  here = state->vars.here;
  state->vars.here = state->vars.dhere;
  bf_inlinecell (state, (cell) prev);
  bf_inlinecell (state, (cell) name);

  bf_inlinecell (state, (cell) dofield);
  bf_inlinecell (state, (cell) argfield);
  state->vars.last = last;
  state->vars.dhere = state->vars.here;
  state->vars.here = here;

  return last;
}

/* DOC: defines a word with the given name, dofield value and argfield value */
cell *
bf_def_word (bf_state *state, const char *name, unsigned char flags,
	     bf_prim dofield, cell argfield)
{
  unsigned char count = strlen (name);
  char *string = (char *) state->vars.here;
  cell i;

  /* max word name length = 31 characters, that's for example
   * eg. MrDishWasherWhoIsAGreatMoronPIG, to make room for the flags */
  count = count & BF_WORD_LENMASK;
  count = count | flags;

  bf_inlinebyte (state, count);
  count = count & BF_WORD_LENMASK;
  for (i = 0; i < count; i++)
    bf_inlinebyte (state, name[i]);

  return bf_def_stub (state, state->vars.last, string, dofield, argfield);
}

/* DOC: defines a normal primitive */
cell *
bf_def_prim (bf_state *state, const char *name, bf_prim primitive)
{
  return bf_def_word (state, name, BF_WORD_NORMAL, &prim_doprim,
		      (cell) primitive);
}

/* DOC: defines a normal literal */
cell *
bf_def_literal (bf_state *state, const char *name, cell value)
{
  return bf_def_word (state, name, BF_WORD_NORMAL, &prim_doliteral, value);
}

/* DOC: defines an imediate primitive */
cell *
bf_def_iprim (bf_state *state, const char *name, bf_prim primitive)
{
  return bf_def_word (state, name, BF_WORD_ALLTIME, &prim_doprim,
		      (cell) primitive);
}

/* DOC: defines an imediate literal */
cell *
bf_def_iliteral (bf_state *state, const char *name, cell value)
{
  return bf_def_word (state, name, BF_WORD_NORMAL, &prim_doliteral, value);
}
