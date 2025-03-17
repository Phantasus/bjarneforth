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

  cell *here = state->here;
  state->here = state->strs;

  bf_inlinebyte (state, count);
  for (i = 0; i < count; i++)
    bf_inlinebyte (state, (cell) adr[i]);

  state->strs = state->vars.here;
  state->here = here;
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
prim_begin_compile (bf_state *state)	/* ( -- ) */
{
  char *name;

  prim_wsparse (state);
  state->vars.state = 1;

  name = (char *) state->vars.strs;

  prim_inlinestring (state);
  name[0] = name[0] & BF_WORD_LENMASK;
  name[0] |= (BF_WORD_NORMAL | BF_WORD_HIDDEN);

  bf_inline_word (state, state->vars.last, name, &prim_dolink,
	       (cell) state->vars.here);
}

/* DOC: new empty word with the given name */
void
prim_newword (bf_state *state)	/* ( str-adr -- ) */
{
  char *name = (char *) bf_pop (&(state->dstack));
  bf_word word;

  word.prev = state->vars.last;
  word.name = (cell) name;
  word.dofield = &prim_doliteral;
  word.arfield = state->vars.here;
  
  bf_inline_word (state, &word);
}

/* DOC: end the the word and stop compilation, at runtime it does nothing */
void
prim_end_compile (bf_state *state)	/* ( -- ) */
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

/* fname: (does) */
/* DOC: turns the latest defined word into a 'does' */
void
prim_does(bf_state *state) /* ( lasthere -- ) */
{
  /* not the elegant version (more a dirty hack), sorry */

#ifdef DEBUG
  printf("(does)\n");
#endif
  cell *lasthere=(cell *)bf_pop(&(state->dstack));
  cell *last=(cell *)state->vars.last;
  cell *here=state->vars.here;
  char *data=(char *)last[BF_WORD_ARGF];
  
  cell size=((char *)here-data), i;
	
  /* inline data location */
  if(size>0)
    bf_inlinecell(state, (cell)&here[2]);
  else bf_inlinecell(state, (cell)data); 
  
  /* inline code location */
  bf_inlinecell(state, (cell)lasthere);
  last[BF_WORD_DOF]=(cell)&prim_dodoes;
  last[BF_WORD_ARGF]=(cell)here;

  /* copy old content to new location */
  if(size>0) {
    for(i=0;i<size;i++)
      bf_inlinebyte(state, data[i]);
  }

  /* TODO: overwriting & realigning old content */
}
