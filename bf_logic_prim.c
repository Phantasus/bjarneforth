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

/* DOC: do a binary logic AND operation on A using B as bitmask */
void
bf_prim_and (bf_state *state)	/* ( A B -- A&B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a & b);
}

/* DOC: a binary logic OR operation on A using B as bitmask */
void
bf_prim_or (bf_state *state)	/* ( A B -- A|B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a | b);
}

/* DOC: A is XORed using B as a bitmask */
void
bf_prim_xor (bf_state *state)	/* ( A B -- A^B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a ^ b);
}

/* DOC: binary negate the TOS */
void
bf_prim_not (bf_state *state)	/* ( A -- ~A ) */
{
  bf_push (&(state->dstack), ~bf_pop (&(state->dstack)));
}

/* DOC: shifts the second element of stack by TOS left */
void
bf_prim_lshift (bf_state *state)	/* ( A B -- A<<B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a << b);
}

/* DOC: shifts the second element of stack by TOS right */
void
bf_prim_rshift (bf_state *state)	/* ( A B -- A>>B ) */
{
  cell b = bf_pop (&(state->dstack));
  cell a = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a >> b);
}

/* DOC: negates the result of a true/false operation */
void
bf_prim_opposite (bf_state *state)	/* ( a b -- ) */
{
  state->flags ^= BF_FLAG_TRUE;
}
