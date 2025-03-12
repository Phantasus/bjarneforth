/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2014 Josef Philip Bernhart
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


#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>

void
helloprim (bf_state *state)
{
  printf ("\nI'm a primitive, beware of me!\n");
}

int
main ()
{

  printf ("deftest\n");
  bf_state state;

  bf_init_state (&(state));
  bf_allot (&(state.memory), 1024);
  state.vars.tib = (char *) &state.memory.content[512];
  bf_init_stack (&state.dstack);

  bf_def_prim (&state, "barbie", &helloprim);
  bf_def_literal (&state, "theonlytruth", 42);

  printf ("prompt>");
  bf_push (&state.dstack, '\n');
  parse (&state);
  dots (&state);
  newline (&state);
  eval (&state);
  dots (&state);
  newline (&state);

  return 0;
}
