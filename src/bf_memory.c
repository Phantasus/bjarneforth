/* ------------------------------------------------------------------------- */
/* Copyright 2007 -- 2014 Josef Philip Bernhart
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

#include <bf_memory.h>
#include <bf_stack.h>
#include <string.h>

void bf_init_memory(bf_memory *memory) /* DOC: sets up a memory structure */
{
  memory->size    = 0;
  memory->a_reg   = 0;
  memory->content = NULL;
  memory->heap    = 0;
  memory->end     = NULL;
}

/* Allocates a bf_memory object with the given size of contained space */
void bf_allot_memory (bf_memory *memory, size_t size) 
{
  memory->size=size;
  memory->a_reg=0;

  if (memory->content!=0) 
    free ((void *)memory->content);

  if (size<BF_MEMORY_MIN_SIZE) 
    size = BF_MEMORY_MIN_SIZE;

  memory->content=(cell *)malloc ((sizeof(cell)*size));
  memory->end=&memory->content[(size-1)];
  memory->heap=memory->content;

  memset ((void *)memory->content, 0, size);
}

void bf_free_memory (bf_memory *memory) /* DOC: frees memory */
{
  memory->size  = 0;
  memory->end   = NULL;
  memory->a_reg = 0;

  if (memory->content!=0) {
    free ((void * )memory->content);
    bf_init_memory (memory);
  }
}
