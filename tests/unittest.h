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

#ifndef BF_UNITTESTH

#include <stdio.h>


int __unittest_pass (const char *message);
int __unittest_fail (const char *message);
const char *__unittest_cast_message (const char *message, ...);

#define __unittest_equal_fail_msg  \
  "%s\n  %ll = %ll\n  at line %ll"
#define __unittest_unequal_fail_msg \
  "%s\n  %ll != %ll \n  at line %ll"

#define ASSERT_EQUAL(value_a, value_b, ...) \
  { \
    long long a = (long long)value_a; \
    long long b = (long long)value_b; \
    char fail_message[512];  \
    const char *pass_message =__unittest_cast_message(__VA_ARGS__); \
    \
    snprintf(fail_message, \
             sizeof(fail_message), \
             __unittest_equal_fail_msg, \
             pass_message, \
             a, \
             b, \
             __LINE__); \
    \
    if (a == b) \
      __unittest_pass(pass_message); \
    else \
      __unittest_fail(fail_message); \
  }

#define ASSERT_UNEQUAL(value_a, value_b, ...) \
  { \
    char fail_message[512];  \
    const char *pass_message =__unittest_cast_message(__VA_ARGS__); \
    long long a = (long long)value_a; \
    long long b = (long long)value_b; \
    \
    snprintf(fail_message, \
             sizeof(fail_message), \
             __unittest_unequal_fail_msg, \
             pass_message, \
             a, \
             b, \
             __LINE__); \
    \
    if (a == b) \
      __unittest_fail(fail_message); \
    else \
      __unittest_pass(pass_message); \
  }

#define BF_UNITTESTH
#endif
