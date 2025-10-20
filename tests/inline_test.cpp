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
#include "unittest.h"

int
main ()
{
  bf_state state;
  cell i;

  printf ("init state\n");
  bf_init_state (&state);

  printf ("allocate memory\n");
  bf_allot (&state, 512);

  printf ("cell inline\n");
  for (i = 1; i < 20; i++)
    {
      bf_inlinecell (&state, i);
    }

  printf ("byte inline\n");
  for (i = 1; i < 20; i++)
    {
      bf_inlinebyte (&state, (char) i);
    }
  bf_push (&state.dstack, state.vars.here);

  prim_dots (&state);
  prim_align (&state);
  prim_dots (&state);

  return 0;
}
