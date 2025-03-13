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


/* memory protection macro */
#define BF_INMEMORY(state, adr) \
if(((adr>=(cell *)state) && (adr<=(cell *)&BF_STATE_END(state))) || \
((adr>=(cell *)state->memory.content) && (adr<=(cell *)state->memory.end)))


/* fname: ! */
void
bf_prim_store (bf_state *state)	/* ( value adr -- ) */
{
  cell *adr = (cell *) bf_pop (&(state->dstack));
  cell value = bf_pop (&(state->dstack));

  BF_INMEMORY (state, (cell *) adr) * adr = value;
}

/* fname: @ */
void
bf_prim_fetch (bf_state *state)	/* ( adr -- value ) */
{
  cell *adr = (cell *) bf_pop (&(state->dstack));

  BF_INMEMORY (state, adr) bf_push (&(state->dstack), *adr);
  else
  bf_push (&(state->dstack), (cell) 0);
}

/* fname: c! */
void
bf_prim_bstore (bf_state *state)	/* ( value adr -- ) */
{
  char *adr = (char *) bf_pop (&(state->dstack));
  char value = (char) bf_pop (&(state->dstack));

  BF_INMEMORY (state, (cell *) adr) * adr = value;
}

/* fname: c@ */
void
bf_prim_bfetch (bf_state *state)	/* ( adr -- value ) */
{
  char *adr = (char *) bf_pop (&(state->dstack));

  BF_INMEMORY (state, (cell *) adr) bf_push (&(state->dstack), *adr);
  else
  bf_push (&(state->dstack), (cell) 0);
}

/* fname: allot */
void
bf_prim_allot (bf_state *state)	/* ( amount -- ) */
{
  cell amount = bf_pop (&(state->dstack));
  state->vars.here += amount;
}

/* fname: align */
void
bf_prim_align (bf_state *state)	/* ( adr -- aligned ) */
{
  char *adr = (char *) bf_pop (&(state->dstack));
  adr += ((cell) adr) % ((cell) (sizeof (cell)));
  bf_push (&(state->dstack), (cell) adr);
}

void
bf_prim_astore (bf_state *state)
{
  cell a = bf_pop (&(state->dstack));
  state->memory.a_reg = a;
}

void
bf_prim_afetch (bf_state *state)
{
  bf_push (&(state->dstack), state->memory.a_reg);
}

void
bf_prim_ainc (bf_state *state)	/* ( -- ) */
{
  state->memory.a_reg++;
}

void
bf_prim_adec (bf_state *state)	/* ( -- ) */
{
  state->memory.a_reg--;
}

/* DOC: copies the bytes from to to using count as a length */
void
bf_prim_copy (bf_state *state)	/* ( from count to -- ) */
{
  char *to = (char *) bf_pop (&(state->dstack));
  cell count = (cell) bf_pop (&(state->dstack));
  char *from = (char *) bf_pop (&(state->dstack));
  cell i;

  for (i = 0; i < count; i++)
    to[i] = from[i];
}

