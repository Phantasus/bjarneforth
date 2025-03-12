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

/*
 * types of bf
 * */



#ifndef BF_TYPESH
#include <stdio.h>
#include <stdint.h>

typedef union {
  signed int    signed_value;
  unsigned int  unsigned_value;
  float         float_value;
  void         *ptr_value;
  char         *byte_ptr;
} cell; /* a cell */

typedef unsigned char byte;	/* a byte */

#define BF_TYPESH
#endif
