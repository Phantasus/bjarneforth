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

/* DOC: add the two numbers A and B together */
void
prim_add (bf_state *state)	/* ( A B -- A+B ) */
{
  int b = bf_pop (&(state->dstack));
  int a = bf_pop (&(state->dstack));
  int result = a + b;

  if (result < 0)
    prim_setnegative (state);

  bf_push (&(state->dstack), (cell) result);
}

/* DOC: subtract B from A */
void
prim_sub (bf_state *state)	/* ( A B -- A-B ) */
{
  int b = bf_pop (&(state->dstack));
  int a = bf_pop (&(state->dstack));
  int result = a - b;

  if (result < 0)
    prim_setnegative (state);

  bf_push (&(state->dstack), (cell) result);
}

/* DOC: multiply A and B */
void
prim_mul (bf_state *state)	/* ( A B -- A*B) */
{
  int b = bf_pop (&(state->dstack));
  int a = bf_pop (&(state->dstack));
  int result = a * b;

  if (result < 0)
    prim_setnegative (state);

  bf_push (&(state->dstack), (cell) result);
}

/* DOC: divide A through B */
void
prim_div (bf_state *state)	/* ( A B -- A/B ) */
{
  int b = bf_pop (&(state->dstack));
  int a = bf_pop (&(state->dstack));
  int result = a / b;

  if (result < 0)
    prim_setnegative (state);

  bf_push (&(state->dstack), (cell) result);
}

/* DOC: push the result of A modulo B on the stack */
void
prim_mod (bf_state *state)	/* ( A B -- A%B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));
  cell result = a % b;

  bf_push (&(state->dstack), (cell) result);
}
