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
unittest::pass (std::string message)
{
  std::cout << "\033[32;1mPASS\033[0m";
  std::cout << " .......... ";
  std::cout << message;
  std::cout << std::endl;
  
  return 0;
}

int
unittest::fail (std::string message)
{
  std::cout << "\033[31;1mFAIL\033[0m";
  std::cout << " .......... ";
  std::cout << message;
  std::cout << std::endl;
  
  exit (1);

  return 1;
}

std::string
unittest::cast_message (std::string message, va_list args)
{
  static std::string messages[1024];
  static int msg_idx = 0;

  char buffer[1024];

  int ref_i = msg_idx;

  vsnprintf (buffer, sizeof(buffer), message.c_str(), args);
  
  messages[ref_i] = std::string {buffer};
  msg_idx = (msg_idx + 1) % 64;

  return messages[ref_i];
}

void
unittest::begin_testcase (std::string name) {
  std::cout << std::format ("----------------------- {} -----------------------\n", name) << std::endl;
}
  
void
unittest::end_testcase (std::string name) {
  std::cout << std::format ("----------------------- end of {} -----------------------\n", name) << std::endl;
}
