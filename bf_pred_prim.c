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

#define BF_TEST_TWO_ITEMS(state, expression) \
  cell b = bf_pop(&(state->dstack)); \
  cell a = bf_pop(&(state->dstack)); \
  if(expression) \
    prim_settrue(state); \
  else \
    prim_setfalse(state);

/* fname: < */
/* DOC: tests if A is lower than B */
void
prim_lower (bf_state *state)	/* ( a b  --  ) */
{
  BF_TEST_TWO_ITEMS (state, a.signed_value < b.signed_value)
}

/* fname: > */
/* DOC: tests if B is greater than A */
void
prim_greater (bf_state *state)	/* ( a b --  ) */
{
  BF_TEST_TWO_ITEMS(state, a.signed_value > b.signed_value)
}

/* fname: = */
/* DOC: tests if A and B are equal */
void
prim_equal (bf_state *state)	/* ( a b -- ) */
{
  BF_TEST_TWO_ITEMS(state, a.signed_value == b.signed_value)
}

/* fname: <= */
/* DOC: tests if B is lower or equal to A */
void
prim_loweq (bf_state *state)	/* ( a b -- ) */
{
  BF_TEST_TWO_ITEMS(state, a.signed_value <= b.signed_value)
}

/* fname: >= */
/* DOC: tests if A is greater or equal to B */
void
prim_greeq (bf_state *state)	/* ( a b -- ) */
{
  BF_TEST_TWO_ITEMS(state, a.signed_value >= b.signed_value)
}

/* DOC: tests if A and B are not equal */
void
prim_notequal (bf_state *state)	/* ( a b -- ) */
{
  BF_TEST_TWO_ITEMS(state, a.signed_value != b.signed_value)
}
