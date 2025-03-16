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

/* DOC: stores one cell at the given position (pos) */
void bf_memory_store (bf_memory *memory, cell value, bf_offset pos)
{
  cell *addr = &memory->content[pos];
  
  if (addr <= memory->last_useable)
    *addr = value;
}

/* DOC: fetches one cell from the given position (pos) */
cell
bf_memory_fetch (bf_memory *memory, bf_offset pos)
{
  cell *addr = &memory->content[pos];
  cell value;

  BF_CLEAR_CELL(value);
  
  if (addr <= memory->last_useable)
    value = *addr;

  return value;
}

void
bf_memory_store_int (bf_memory *memory, bf_int value, bf_offset pos)
{
  cell cell_value;
  cell_value.signed_value = value;

  bf_memory_store (memory, cell_value, pos);
}

bf_int
bf_memory_fetch_int (bf_memory *memory, bf_offset pos)
{
  return bf_memory_fetch (memory, pos).signed_value;
}

char
bf_memory_fetch_byte (bf_memory *memory, bf_offset pos)
{
  char *addr = (char *)memory->content;

  if (pos < memory->size * sizeof(cell))
    return addr[pos];

  return 0;
}

void
bf_memory_store_uint (bf_memory *memory, bf_uint value, bf_offset pos)
{
  cell cell_value;
  cell_value.unsigned_value = value;

  bf_memory_store (memory, cell_value, pos);
}

void
bf_memory_store_byte (bf_memory *memory, char value, bf_offset pos)
{ 
  char *addr = (char *)memory->content;

  if (pos < memory->size * sizeof(cell))
    addr[pos] = value;
}
  
bf_int
bf_memory_fetch_uint (bf_memory *memory, bf_offset pos)
{
  return bf_memory_fetch (memory, pos).unsigned_value;
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

/* DOC: compares two memories and returns true if they are equal else false */
bool
bf_cmp_memory (bf_memory *memory_a, bf_memory *memory_b)
{
  if (memory_a == NULL && memory_b == NULL)
    return true;

  if (memory_a && memory_b)
    {
      if (memory_a->size == memory_b->size)
        {
          if (memory_a->content && memory_b->content) {
            size_t memsize = sizeof(cell) * memory_a->size;
            int result = memcmp(memory_a->content, memory_b->content, memsize);
            
            return 0 == result;
          }
          else
            return true;
        }
    }
  
  return false;
}

void
bf_memory_resize (bf_memory *memory, size_t newsize)
{
  size_t oldsize = memory->size;
  size_t memsize = sizeof (cell) * newsize;
  size_t clearsize;
  
  if (memory->content)
    {
      /* the memory exists already, so we can resize it */
      
      memory->content = (cell *)realloc (memory->content, memsize);
      memory->size = newsize;
      memory->last_useable = &memory->content[newsize - 1];
      
      if (newsize > oldsize)
        {
          clearsize = newsize - oldsize;

          memset (&memory->content[oldsize], 0, clearsize);
        }
    }
  else
    {
      /* an empty memory can be allocated */
      bf_allot_memory (memory, newsize);
    }
}

void
bf_memory_dump (bf_memory *memory, FILE *file)
{
  char *addr  = (char *)memory->content;
  char field[sizeof(cell)];
  cell magic;

  /* writing endian check */
  magic.unsigned_value = BF_MEMORY_MAGIC;

  memset (field, 0, sizeof (field));
  memcpy (field, &magic, sizeof(magic));
  
  for (size_t i = 0; i < sizeof(field); i++)
    fputc(field[i], file);

  /* writing size field */
  memset (field, 0, sizeof (field));
  memcpy (field, &memory->size, sizeof(memory->size));

  for (size_t i = 0; i < sizeof(field); i++)
    fputc(field[i], file);

  /* writing bytes out */
  for (size_t i = 0; i < (memory->size * sizeof(cell)); i++)
    fputc(addr[i], file);
}

static void
inspect_memory (char *bytes, size_t size)
{
  for (int i = 1; i <= size; i++)
    {
      printf("%02x ", (unsigned char)bytes[i - 1]);

      if (0 == i % 8)
        fputc(32, stdout);

      if (0 == i % 16)
        fputc(10, stdout);
    }
}

static void
reverse_cell (char *field)
{
  char buffer[sizeof(cell)];

  for (int i = 0; i < sizeof(cell); i++)
    {
      buffer[sizeof(cell) - (i + 1)] = (char)field[i];
    }
  memcpy (field, buffer, sizeof(cell));
}

void
bf_memory_restore (bf_memory *memory, FILE *file)
{
  cell magic;
  cell value;

  char *field = (char *)&value;
  int reverse_mode = 0;
  
  /* writing endian check */
  magic.unsigned_value = BF_MEMORY_MAGIC;

  memset (field, 0, sizeof (cell));

  for (size_t i = 0; i < sizeof(cell); i++)
    field[i] = fgetc(file);

  /* check if the endian magic is the same */
  if (!!memcmp (&magic, &value, sizeof(magic)))
    {
      reverse_cell ((char *)&value);

      /* check if it's reversed, if it is then start reverse mode */
      if (0 == memcmp (&magic, &value, sizeof(magic)))
        reverse_mode = 1;
      else
        return; /* otherwise we have a wrong file */
    }
  
  /* the dump is in the endianess of the machine */
  for (size_t i = 0; i < sizeof(field); i++)
    field[i] = fgetc(file);

  if (reverse_mode)
    reverse_cell (field);

  bf_memory_resize (memory, value.unsigned_value);

  for (size_t i = 0; i < memory->size; i++)
    {
      for (size_t k = 0; k < sizeof (field); k++)
        field[k] = fgetc(file);

      if (reverse_mode)
        reverse_cell (field);

      memcpy (&memory->content[i], &value, sizeof(cell));
    }
}
