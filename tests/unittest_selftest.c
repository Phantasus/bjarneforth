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

/**
   This file does a selftest of the included unittesting framework
 */

#include "unittest.h"

int
main (int argc, char **argv)
{
  ASSERT_EQUAL (1, 1, "equality test");
  ASSERT_UNEQUAL (1, 2, "inequality test");

  ASSERT_STR_EQUAL ("abc", "abc", "equality with string test");
  ASSERT_STR_UNEQUAL ("abc1", "abc", "inequality with string test");

  return 0;
}
