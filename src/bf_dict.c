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

/* DOC: creates a word stub in memory and returns the address to it */
cell *
bf_inline_word (bf_state *state, bf_word *word)
{
  cell *last, *here;

  last = (cell *) state->dhere;
  here = state->here;
  state->here = state->dhere;

  bf_inlinecell (state, word->prev);
  bf_inlinecell (state, word->name_length);
  bf_inlinecell (state, word->name);
  bf_inlinecell (state, word->flags);

  bf_inlinecell (state, word->dofield);
  bf_inlinecell (state, word->argfield);

  state->last  = last;
  state->dhere = state->here;
  state->here  = here;

  return last;
}

/* DOC: defines a word with the given name, dofield value and argfield value */
cell *
bf_define_word (bf_state *state, const char *name, bf_word_flag flags,
                bf_prim dofield, cell argfield)
{
  char *string = (char *) state->here;

  cell name_length;
  bf_word word;

  name_length.unsigned_value = strlen (name);

  /* max word name length = 31 characters, that's for example
   * eg. MrDishWasherWhoIsAGreatMoronPIG, to make room for the flags */
  bf_inlinecell (state, name_length);

  for (size_t i = 0; i < name_length.unsigned_value; i++)
    bf_inlinebyte (state, name[i]);

  word.name_length        = name_length;
  word.prev.ptr_value     = state->last;
  word.name.ptr_value     = string;
  word.dofield.ptr_value  = dofield;
  word.argfield           = argfield;

  return bf_inline_word (state, &word);
}

/* DOC: defines a normal primitive */
cell *
bf_define_prim (bf_state *state, const char *name, bf_prim primitive)
{
  cell argfield;

  argfield.ptr_value = (void *)primitive;
  
  return bf_define_word (state, name, normal_word, &bf_prim_doprim,
                         argfield);
}

/* DOC: defines a normal literal */
cell *
bf_define_literal (bf_state *state, const char *name, cell value)
{
  return bf_define_word (state, name, normal_word, &bf_prim_doliteral, value);
}

/* DOC: defines an imediate primitive */
cell *
bf_define_iprim (bf_state *state, const char *name, bf_prim primitive)
{
  cell argfield;

  argfield.ptr_value = (void *)primitive;
  
  return bf_define_word (state, name, immediate_word, &bf_prim_doprim,
                         argfield);
}

/* DOC: defines an imediate literal */
cell *
bf_define_iliteral (bf_state *state, const char *name, cell value)
{
  return bf_define_word (state, name, normal_word, &bf_prim_doliteral, value);
}

/* DOC: returns the address of the dofield with a bf_prim for the given opcode */
cell
bf_get_vmprimitive (bf_state *state, bf_opcode opcode)
{
  bf_word *word = &state->vmprims [opcode];

  return (cell)&word->dofield;
}
