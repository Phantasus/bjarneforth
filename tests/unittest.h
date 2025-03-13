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
const char *__unittest_cast_message (const char *message, va_list args);

void __unittest_assert_equal_int (long long int value_a,
				  long long int value_b,
				  long unsigned int line, const char *message,
				  ...);

void __unittest_assert_equal_char_ptr (char *value_a,
                                       char *value_b,
                                       long unsigned int line, const char *message,
                                       ...);

void __unittest_assert_unequal_int (long long int value_a,
				    long long int value_b,
				    long unsigned int line,
				    const char *message, ...);

void __unittest_assert_unequal_char_ptr (char *value_a,
                                         char *value_b,
                                         long unsigned int line,
                                         const char *message, ...);

#define ASSERT_STR_EQUAL(actual, expected, ...) \
  __unittest_assert_equal_char_ptr(actual, expected, __LINE__, __VA_ARGS__)

#define ASSERT_STR_UNEQUAL(actual, expected, ...) \
  __unittest_assert_unequal_char_ptr(actual, expected, __LINE__, __VA_ARGS__)

#define ASSERT_EQUAL(actual, expected, ...) \
  __unittest_assert_equal_int(actual, expected, __LINE__, __VA_ARGS__)

#define ASSERT_UNEQUAL(actual, expected, ...)            \
  __unittest_assert_unequal_int(actual, expected, __LINE__, __VA_ARGS__)

#define BF_UNITTESTH
#endif
