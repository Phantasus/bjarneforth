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
#include <string.h>

#define __unittest_equal_fail_msg  "%s\n  %d = %d\n  at line %d"
#define __unittest_unequal_fail_msg "%s\n  %d != %d \n  at line %d"


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
__unittest_cast_message (const char *message, va_list args)
{
  static char messages[64][1024];
  static int msg_idx = 0;

  int ref_i = msg_idx;

  vsnprintf (&messages[ref_i][0], 1024, message, args);
  msg_idx = (msg_idx + 1) % 64;

  return &messages[ref_i][0];
}

void
__unittest_assert_equal_int (long long int a, long long int b,
			     long unsigned int line, const char *message, ...)
{
  char fail_message[512];

  va_list args;

  const char *pass_message = __unittest_cast_message (message, args);

  snprintf (fail_message,
	    sizeof (fail_message),
	    __unittest_equal_fail_msg, pass_message, a, b, line);

  if (a == b)
    __unittest_pass (pass_message);
  else
    __unittest_fail (fail_message);
}

void
__unittest_assert_equal_char_ptr (char *a, char *b,
			     long unsigned int line, const char *message, ...)
{
  char fail_message[512];

  va_list args;

  const char *pass_message = __unittest_cast_message (message, args);

  snprintf (fail_message,
	    sizeof (fail_message),
	    __unittest_equal_fail_msg,
            pass_message,
            a,
            b,
            line);

  if (strcmp(a, b))
    __unittest_fail (fail_message);
  else
    __unittest_pass (pass_message);
}

void
__unittest_assert_unequal_char_ptr (char *a, char *b,
			     long unsigned int line, const char *message, ...)
{
  char fail_message[512];

  va_list args;

  const char *pass_message = __unittest_cast_message (message, args);

  snprintf (fail_message,
	    sizeof (fail_message),
	    __unittest_equal_fail_msg,
            pass_message,
            a,
            b,
            line);

  if (strcmp(a, b))
    __unittest_pass (pass_message);
  else
    __unittest_fail (fail_message);
}

void
__unittest_assert_unequal_int (long long int a, long long int b,
			       long unsigned int line, const char *message,
			       ...)
{
  char fail_message[512];

  va_list args;

  const char *pass_message = __unittest_cast_message (message, args);

  snprintf (fail_message,
	    sizeof (fail_message),
	    __unittest_equal_fail_msg, pass_message, a, b, line);

  if (a == b)
    __unittest_fail (fail_message);
  else
    __unittest_pass (pass_message);
}
