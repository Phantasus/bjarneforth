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

#include <bf_memory.h>
#include <bf_stack.h>

void
bf_init_memory (bf_memory *memory)	/* DOC: sets up a memory structure */
{
  memory->size = 0;
  memory->a_reg = 0;
  memory->content = 0;
  memory->heap = 0;
  memory->end = 0;
}

void
bf_allot_memory (bf_memory *memory, unsigned int size)	/* DOC: allocates some memory */
{
  int i;

  memory->size = size;
  memory->a_reg = 0;

  if (memory->content != 0)
    free ((void *) memory->content);

  if (size < BF_MEMORY_MIN_SIZE)
    size = BF_MEMORY_MIN_SIZE;

  memory->content = (cell *) malloc ((sizeof (cell) * size));
  memory->end = &memory->content[(size - 1)];
  memory->heap = memory->content;
  for (i = 0; i < size; i++)
    memory->content[i] = 0;
}

void
bf_free_memory (bf_memory *memory)	/* DOC: frees memory */
{
  memory->size = 0;
  memory->end = 0;
  memory->a_reg = 0;

  if (memory->content != 0)
    {
      free ((void *) memory->content);
      bf_init_memory (memory);
    }
}
