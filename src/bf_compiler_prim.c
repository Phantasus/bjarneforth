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
#include "bf_dict.h"
#include "bf_prim.h"


/* DOC: inline num as a cell to here */
void
bf_prim_inlinecell (bf_state *state)	/* ( num  -- ) */
{
  bf_inlinecell (state, bf_pop_dstack (state));
}

/* DOC: inline num as a byte/character to here */
void
bf_prim_inlinebyte (bf_state *state)	/* ( num -- ) */
{
  bf_inlinebyte (state, (char)bf_pop_dstack_int (state));
}

/* DOC: inline the string on TOS to there */
void
bf_prim_inlinestring (bf_state *state)	/* ( str strlen -- ) */
{
  char *addr = bf_pop_dstack_char_ptr (state);
  cell count = bf_pop_dstack (state);
  cell *here = state->here;
  
  bf_memory_inlinebyte (&state->memory, &here, (char)count.signed_value);
  for (size_t i = 0; i < count.unsigned_value; i++)
    bf_memory_inlinebyte (&state->memory, &here, addr[i]);
}

/* fnames: literal, lit, */
/* DOC: inlines a literal */
void
bf_prim_inlineliteral (bf_state *state)	/* ( value -- ) */
{
  bf_inlinecell (state, (cell) bf_get_vmprimitive (state, BF_VM_PUSHLIT));
  bf_prim_inlinecell (state);
}

/* DOC: inlines a string literal */
void
bf_prim_inlinesliteral (bf_state *state)	/* ( cstr --  ) */
{
  bf_inlinecell (state, (cell) bf_get_vmprimitive (state, BF_VM_PUSHSLIT));
  bf_prim_inlinecell (state);
}

/* DOC: create a link word and start compilation */
void
bf_prim_begin_compile (bf_state *state)	/* ( -- ) */
{
  char *name;
  bf_word newword;

  bf_prim_parse_name (state);
  state->flags |= flag_compiling;

  bf_prim_inlinestring (state);
  
  newword.flags.unsigned_value = (normal_word | hidden_word);
  newword.prev.cell_ptr        = state->last;
  newword.dofield.prim_ptr     = &bf_prim_dolink;
  newword.argfield.cell_ptr    = state->here;

  bf_inline_word (state, &newword);
}

/* DOC: new empty word with the given name */
void
bf_prim_newword (bf_state *state)	/* ( str-adr -- ) */
{
  bf_word newword;

  bf_prim_inlinestring (state);
  bf_align (state);

  newword.prev.cell_ptr        = state->last;
  newword.flags.unsigned_value = normal_word;
  newword.dofield.prim_ptr     = &bf_prim_doliteral;
  newword.argfield.cell_ptr    = state->here;
  
  bf_inline_word (state, &newword);
}

/* DOC: end the the word and stop compilation, at runtime it does nothing */
void
bf_prim_end_compile (bf_state *state)	/* ( -- ) */
{
  bf_word *last_word = (bf_word *)state->last;

  if (state->flags & flag_compiling)
    {
      bf_inlineuint (state, 0); /* exit */

      last_word->flags.unsigned_value &= ~hidden_word;
      state->flags &= ~flag_compiling;
    }
}

/* fname: (does) */
/* DOC: turns the latest defined word into a 'does' */
void
bf_prim_does (bf_state *state) /* ( lasthere -- ) */
{
  /* not the elegant version (more a dirty hack), sorry */

#ifdef DEBUG
  printf("(does)\n");
#endif
  cell tos       = bf_pop_dstack (state); /* lasthere */
  cell *lasthere = tos.cell_ptr;
  bf_word *last_word = (bf_word *)state->last;

  /*
  cell *here = state->here;
  char *data = last_word->argfield.char_ptr;
  
  cell size = ((char *)here-data);
  */
	
  /* inline data location */
  /*
  if (size > 0)
    bf_inlinecell (state, (cell)&here[2]);
  else
    bf_inlinecell (state, (cell)data); 
  */
  
  /* inline code location */
  /*bf_inlinecell (state, (cell)lasthere);

  last_word.dofield.prim_ptr  = &bf_prim_dodoes;
  last_word.argfield.cell_ptr = here;

  */
  /* copy old content to new location */
  /*if (size > 0) {
    for (size_t i = 0; i < size; i++)
      bf_inlinebyte (state, data[i]);
      } */

  /* TODO: overwriting & realigning old content */
}
