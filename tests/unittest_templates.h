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

template <typename T>
void
assert_equal (T a,
              T b,
              long unsigned int line,
              std::string message, 
              ...)
{
  va_list args;

  std::string pass_message = unittest::cast_message (message, args);
  std::string fail_message = std::format("{}\n  {} = {}\n  at line {}",
                                        pass_message,
                                        a,
                                        b,
                                        line);

  if (a == b)
    unittest::pass (pass_message);
  else
    unittest::fail (fail_message);
}

template <typename T>
void
assert_unequal(T a,
                T b,
                long unsigned int line,
                std::string message,
                ...)
{
  va_list args;

  std::string pass_message = unittest::cast_message (message, args);
  std::string fail_message = std::format("{}\n  {} = {}\n  at line {}",
                                        pass_message,
                                        a,
                                        b,
                                        line);

  if (a == b)
    unittest::fail (fail_message);
  else
    unittest::pass (pass_message);
}
