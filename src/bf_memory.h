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
#include <stdbool.h>

struct bf_memory
{
  size_t size;			/* memory size */
  
  cell *content;		/* memory area */
  cell *last_useable;		/* last writeable/readable address of cell */
};

typedef struct bf_memory bf_memory;

#define BF_MEMORY_MAGIC 0x08090a0b0c0d0e0f

/* BootForth's memory functions */

void bf_init_memory (bf_memory * memory);
void bf_allot_memory (bf_memory * memory, size_t size);
void bf_free_memory (bf_memory * memory);

/* store/fetch functions */
void bf_memory_store (bf_memory *memory, cell value, bf_offset pos);
cell bf_memory_fetch (bf_memory *memory, bf_offset pos);

void   bf_memory_store_int (bf_memory *memory, bf_int value, bf_offset pos);
bf_int bf_memory_fetch_int (bf_memory *memory, bf_offset pos);

void bf_memory_store_byte (bf_memory *memory, char value, bf_offset pos);
char bf_memory_fetch_byte (bf_memory *memory, bf_offset pos);

/* inline functions */
void bf_memory_inlinecell (bf_memory *memory, cell **here_ptr, cell value);
void bf_memory_inlinebyte (bf_memory *memory, cell **here_ptr, char value);

/* comparing memories */
bool bf_cmp_memory (bf_memory *memory_a, bf_memory *memory_b);

/* memory dumping/restoring */
void bf_memory_dump (bf_memory *memory, FILE *file);
void bf_memory_restore (bf_memory *memory, FILE *file);

/* sizing */
void bf_memory_resize (bf_memory *memory, size_t size);

#define BF_MEMORYH
#endif
