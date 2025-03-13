/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2024 Josef Philip Bernhart
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
 * along with BootForth.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                           
 * ------------------------------------------------------------------------- */

#include "bf_state.h"

static char
default_whitespaces[] = "\x04\n \t\v";

static void
init_variables(bf_state *state)
{
  state->last = 0;
  state->tib = 0;
  state->here = 0;
  state->state = 0;
  state->flags = flag_running;
  state->dhere = 0;
  state->tibsize = 0;
  state->strs = 0;

  state->whitespaces = default_whitespaces;
  state->base = BF_BASE_DEC;
}

void
bf_init_state (bf_state *state)
{
  bf_init_memory (&(state->memory));

  bf_init_stack (&(state->dstack));
  bf_init_stack (&(state->rstack));
  bf_clear_stream (&(state->input));
  bf_clear_stream (&(state->output));

  bf_open_stdstream (&(state->input), stdin);
  bf_open_stdstream (&(state->output), stdout);

  init_variables (state);

  state->flags = flag_unset;
}

void
bf_free_state (bf_state *state)
{
  bf_free_memory (&(state->memory));
  bf_close_stream (&(state->input));
  bf_close_stream (&(state->output));
}

void
bf_inlinecell (bf_state *state, cell value)
{
  state->here[0] = value;
  if (state->here < state->memory.end)
    state->here = (cell *) & state->here[1];
}

void
bf_inlinebyte (bf_state *state, char value)
{
  char *addr = (char *) state->here;
  addr[0] = value;

  if (state->here < state->memory.end)
    state->here = (cell *) & addr[1];
}

void
bf_allot (bf_state *state, size_t size)
{
  bf_allot_memory (&state->memory, size);
  state->here  = state->memory.content;
  state->dhere = state->memory.content;
}

void
bf_push_dstack(bf_state *state, cell value)
{
  bf_stack_push(&(state->dstack), value);
}

void
bf_push_dstack_int(bf_state *state, int value)
{
  bf_stack_push_int(&(state->dstack), value);
}

void
bf_push_dstack_uint(bf_state *state, unsigned int value)
{
  bf_stack_push_uint(&(state->dstack), value);
}

void
bf_push_dstack_char_ptr(bf_state *state, char *value)
{
  bf_stack_push_char_ptr(&(state->dstack), value);
}

cell
bf_pop_dstack(bf_state *state)
{
  return bf_stack_pop(&(state->dstack));
}

int
bf_pop_dstack_int(bf_state *state)
{
  return bf_stack_pop_int(&(state->dstack));
}

unsigned int
bf_pop_dstack_uint(bf_state *state)
{
  return bf_stack_pop_uint(&(state->dstack));
}

char *
bf_pop_dstack_char_ptr(bf_state *state)
{
  return bf_stack_pop_char_ptr(&(state->dstack));
}

cell
bf_tos_dstack(bf_state *state)
{
  return bf_stack_tos(&(state->dstack));
}

int
bf_tos_dstack_int(bf_state *state)
{
  return bf_tos_dstack(state).signed_value;
}

unsigned int
bf_tos_dstack_uint(bf_state *state)
{
  return bf_tos_dstack(state).unsigned_value;
}

size_t
bf_size_dstack(bf_state *state)
{
  return bf_stack_size(&state->dstack);
}

void
bf_push_rstack(bf_state *state, cell value)
{
  bf_stack_push(&(state->rstack), value);
}

cell
bf_pop_rstack(bf_state *state)
{
  return bf_stack_pop(&(state->rstack));
}

cell
bf_tos_rstack(bf_state *state)
{
  return bf_stack_tos(&(state->rstack));
}
  
size_t
bf_size_rstack(bf_state *state)
{
  return bf_stack_size(&state->rstack);
}
