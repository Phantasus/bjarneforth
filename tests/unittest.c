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
 * This file describes a minimal unittesting framework
 */

#include "unittest.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int
__unittest_pass (const char *message)
{
  printf ("\033[32;1mPASS\033[0m .......... %s\n", message);
  return 0;
}

int
__unittest_fail (const char *message)
{
  printf ("\033[31;1mFAIL\033[0m .......... %s\n", message);
  exit (1);

  return 1;
}

const char *
__unittest_cast_message (const char *message, ...)
{
  static char messages[64][1024];
  static int msg_idx = 0;
  va_list args;

  int ref_i = msg_idx;

  vsnprintf (&messages[ref_i][0], 1024, message, args);
  msg_idx = (msg_idx + 1) % 64;

  return &messages[ref_i][0];
}
