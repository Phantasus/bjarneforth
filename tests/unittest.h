/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2025 Josef Philip Bernhart
 *
 * This file is part of bjarneforth.
 *
 * bjarneforth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * bjarneforth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bjarneforth.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                           
 * ------------------------------------------------------------------------- */

/**
 * This file describes a minimal unittesting framework
 */

#ifndef BF_UNITTEST_H

#include <stdio.h>
#include <string>
#include <format>
#include <iostream>

namespace unittest {

  int pass (std::string message);
  int fail (std::string message);

  void begin_testcase (std::string name);
  void end_testcase (std::string name);

  std::string cast_message (std::string message, va_list args);

  /* templates */
  #include "unittest_templates.h"
}

#define BEGIN_TEST \
  begin_testcase (__FUNCTION__)

#define END_TEST \
  end_testcase (__FUNCTION__)

#define ASSERT_EQUAL(actual, expected, ...) \
  unittest::assert_equal(actual, expected, __LINE__, __VA_ARGS__)

#define ASSERT_UNEQUAL(actual, expected, ...)            \
  unittest::assert_unequal(actual, expected, __LINE__, __VA_ARGS__)


#define BF_UNITTEST_H
#endif
