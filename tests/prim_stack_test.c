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

#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>
#include "unittest.h"

int
test_stackprims (bf_state *state)
{
  printf ("push: 1 2 3 \n");
  bf_init_state (state);

  bf_prim_newline (state);
  bf_push_dstack_int (state, 1);
  bf_push_dstack_int (state, 2);
  bf_push_dstack_int (state, 3);

  printf ("over; expected result: 1 2 3 2 \n");
  bf_prim_over (state);
  bf_prim_dots (state);
  bf_prim_newline (state);

  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));
  printf ("TOS: %d\n", bf_pop_dstack_int (state));

  return 0;
}

int
main ()
{
  bf_state state;
  bf_init_state (&state);

  test_stackprims (&state);
}
