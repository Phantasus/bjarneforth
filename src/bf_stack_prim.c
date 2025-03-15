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
bf_prim_dup (bf_state *state)	/* ( a -- a a ) */
{
  cell value = bf_pop_dstack (state);
  
  bf_push_dstack (state, value);
  bf_push_dstack (state, value);
}

/* DOC: see stack comment */
void
bf_prim_swap (bf_state *state)	/* ( a b -- b a ) */
{
  cell a = bf_pop_dstack(state);
  cell b = bf_pop_dstack(state);

  bf_push_dstack (state, a);
  bf_push_dstack (state, b);
}

/* DOC: see stack comment */
void
bf_prim_nip (bf_state *state)	/* ( a b -- b a b ) */
{
  bf_prim_swap (state);
  bf_prim_drop (state);
}

/* DOC: see stack comment */
void
bf_prim_tuck (bf_state *state)	/* ( a b -- b ) */
{
  bf_prim_swap (state);
  bf_prim_over (state);
}

/* DOC: see stack comment */
void
bf_prim_drop (bf_state *state)	/* ( a -- ) */
{
  bf_pop_dstack (state);
}

/* DOC: see stack comment */
void
bf_prim_over (bf_state *state)	/* ( a b -- a b a ) */
{
  cell a = bf_pop_dstack (state);
  cell b = bf_pop_dstack (state);

  bf_push_dstack (state, b);
  bf_push_dstack (state, a);
  bf_push_dstack (state, b);
}

/* fname: >r */
/* DOC: pushes the TOS of dstack on the rstack */
void
bf_prim_tor (bf_state *state)	/* ( value -- Rstack:value ) */
{
  bf_push_rstack (state, bf_pop_dstack (state));
}

/* fname: r> */
/* DOC: pushes TOS from rstack to dstack */
void
bf_prim_fromr (bf_state *state)	/* ( Rstack:value -- value ) */
{
  bf_push_dstack (state, bf_pop_rstack (state));
}

/* fname: r r@ */
/* DOC: pushes TOS of the rstack on the data stack, without
 * changing the rstack */
void
bf_prim_tosr (bf_state *state)	/* ( -- Rtos) */
{
  bf_push_dstack (state, bf_tos_rstack(state));
}
