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

#ifndef BF_MEMORYH

#include "bf_types.h"
#include <stdlib.h>

struct bf_memory
{
  size_t size;			/* memory size */
  cell *a_reg;			/* adress register */
  
  cell *content;		/* memory area */
  cell *end;			/* last memory adr */
  cell *heap;			/* start of heap */
};

typedef struct bf_memory bf_memory;

/* BootForth's memory functions */

void bf_init_memory (bf_memory * memory);
void bf_allot_memory (bf_memory * memory, size_t size);
void bf_free_memory (bf_memory * memory);

#define BF_MEMORYH
#endif
