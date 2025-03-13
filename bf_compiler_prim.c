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


/* DOC: inline num as a cell to here */
void
prim_inlinecell (bf_state *state)	/* ( num  -- ) */
{
  bf_inlinecell (state, bf_pop (&(state->dstack)));
}

/* DOC: inline num as a byte/character to here */
void
prim_inlinebyte (bf_state *state)	/* ( num -- ) */
{
  bf_inlinebyte (state, bf_pop (&(state->dstack)));
}

/* DOC: inline the string on TOS to there */
void
prim_inlinestring (bf_state *state)	/* ( str strlen -- ) */
{
  char *adr;
  cell count = bf_pop (&(state->dstack)), i;
  adr = (char *) bf_pop (&(state->dstack));

#ifdef BF_USE_STRS
  cell *here = state->vars.here;
  state->vars.here = state->vars.strs;
#endif

  bf_inlinebyte (state, count);
  for (i = 0; i < count; i++)
    bf_inlinebyte (state, (cell) adr[i]);

#ifdef BF_USE_STRS
  state->vars.strs = state->vars.here;
  state->vars.here = here;
#endif
}

/* fnames: literal, lit, */
/* DOC: inlines a literal */
void
prim_inlineliteral (bf_state *state)	/* ( value -- ) */
{
  bf_inlinecell (state, (cell) BF_VM_PRIM (state, BF_VM_PUSHLIT));
  prim_inlinecell (state);
}

/* DOC: inlines a string literal */
void
prim_inlinesliteral (bf_state *state)	/* ( cstr --  ) */
{
  bf_inlinecell (state, (cell) BF_VM_PRIM (state, BF_VM_PUSHSLIT));
  prim_inlinecell (state);
}

/* DOC: create a link word and start compilation */
void
prim_compile (bf_state *state)	/* ( -- ) */
{
  char *name;

  prim_wsparse (state);
  state->vars.state = 1;

#ifdef BF_USE_STRS
  name = (char *) state->vars.strs;
#endif

#ifndef BF_USE_STRS
  name = (char *) state->vars.here;
#endif

  prim_inlinestring (state);
  name[0] = name[0] & BF_WORD_LENMASK;
  name[0] |= (BF_WORD_NORMAL | BF_WORD_HIDDEN);

  bf_def_stub (state, state->vars.last, name, &prim_dolink,
	       (cell) state->vars.here);
}

/* DOC: new empty word with the given name */
void
prim_newword (bf_state *state)	/* ( str-adr -- ) */
{
  char *name = (char *) bf_pop (&(state->dstack));
  bf_def_stub (state, state->vars.last, name, &prim_doliteral,
	       (cell) state->vars.here);
}

/* DOC: end the the word and stop compilation, at runtime it does nothing */
void
prim_endcompile (bf_state *state)	/* ( -- ) */
{
  char *data = (char *) state->vars.last[BF_WORD_NAME];

  if (state->vars.state)
    {
      state->vars.state = 0;
      bf_inlinecell (state, (cell) 0);

      data[0] &= ~BF_WORD_HIDDEN;

#ifdef DEBUG
      printf ("END");
#endif
    }
}
