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
#include <bf_dict.h>
#include <bf_prim.h>
#include <stdio.h>
#include "unittest.h"
#include <string.h>

void
test_defining_words ()
{
  bf_state state;
  bf_word word;
  
  BEGIN_TEST;
  
  bf_init_state (&state);
  

  bf_free_state (&state);
  
  END_TEST;
}

int
main ()
{
  test_defining_words ();
  
  return 0;
}
