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

#include "bf_memory.h"
#include "bf_stack.h"

void
bf_init_memory (bf_memory *memory)	/* DOC: sets up a memory structure */
{
  memory->size    = 0;
  memory->content = 0;
  memory->last_useable     = 0;
}

void
bf_allot_memory (bf_memory *memory, size_t size)	/* DOC: allocates some memory */
{
  int i;

  memory->size = size;

  if (memory->content != 0)
    free ((void *) memory->content);

  memory->content = (cell *) calloc (size, sizeof (cell));
  memory->last_useable  = &memory->content[(size - 1)];
}

void
bf_free_memory (bf_memory *memory)	/* DOC: frees memory */
{
  if (memory->content != 0)
    {
      free ((void *) memory->content);
    }
  bf_init_memory (memory);
}

/* DOC: inlines one cell into memory and stores the increase into location at here_ptr */
void
bf_memory_inlinecell (bf_memory *memory, cell **here_ptr, cell value)
{
  cell *here = *here_ptr;
  
  here[0] = value;
  if (here <= memory->last_useable)
    *here_ptr = (cell *) &here[1];
}

/* DOC: inlines one byte into memory and stores the new address into location at here ptr */
void
bf_memory_inlinebyte (bf_memory *memory, cell **here_ptr, char value)
{
  char *here = (char *) *here_ptr;
  char *last_useable = (char *)memory->last_useable;
  here[0] = value;

  if (here <= &last_useable[sizeof(cell) - 1])
    *here_ptr = (cell *) & here[1];
}
