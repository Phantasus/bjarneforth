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


/* DOC: see stack comment */
void
prim_dup (bf_state *state)	/* ( a -- a a ) */
{
  cell value = bf_pop (&(state->dstack));
  bf_push (&(state->dstack), value);
  bf_push (&(state->dstack), value);
}

/* DOC: see stack comment */
void
prim_swap (bf_state *state)	/* ( a b -- b a ) */
{
  cell a = bf_pop (&(state->dstack));
  cell b = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), a);
  bf_push (&(state->dstack), b);
}

/* DOC: see stack comment */
void
prim_nip (bf_state *state)	/* ( a b -- b a b ) */
{
  prim_swap (state);
  prim_drop (state);
}

/* DOC: see stack comment */
void
prim_tuck (bf_state *state)	/* ( a b -- b ) */
{
  prim_swap (state);
  prim_over (state);
}

/* DOC: see stack comment */
void
prim_drop (bf_state *state)	/* ( a -- ) */
{
  bf_pop (&(state->dstack));
}

/* DOC: see stack comment */
void
prim_over (bf_state *state)	/* ( a b -- a b a ) */
{
  cell a = bf_pop (&(state->dstack));
  cell b = bf_pop (&(state->dstack));

  bf_push (&(state->dstack), b);
  bf_push (&(state->dstack), a);
  bf_push (&(state->dstack), b);
}

/* fname: >r */
/* DOC: pushes the TOS of dstack on the rstack */
void
prim_tor (bf_state *state)	/* ( value -- Rstack:value ) */
{
  bf_push (&(state->rstack), bf_pop (&(state->dstack)));
}

/* fname: r> */
/* DOC: pushes TOS from rstack to dstack */
void
prim_fromr (bf_state *state)	/* ( Rstack:value -- value ) */
{
  bf_push (&(state->dstack), bf_pop (&(state->rstack)));
}

/* fname: r r@ */
/* DOC: pushes TOS of the rstack on the data stack, without
 * changing the rstack */
void
prim_tosr (bf_state *state)	/* ( -- Rtos) */
{
  bf_push (&(state->dstack), bf_tos (&(state->rstack)));
}
