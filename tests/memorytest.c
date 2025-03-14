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

/**
 * This unittest does check the memory functions of bootforth
 */


#include <bf_state.h>
#include <stdio.h>
#include "unittest.h"

void
test_init_memory()
{
  bf_memory mymemory;

  BEGIN_TEST;

  bf_init_memory(&mymemory);
  ASSERT_EQUAL (mymemory.size, 0,    "Should be zero");
  ASSERT_EQUAL (mymemory.content, 0, "Should be zero");
  ASSERT_EQUAL (mymemory.last_useable, 0,     "Should be zero");
  
  END_TEST;
}

void
test_allocating_memory()
{
  bf_memory mem;
  size_t diff;
  unsigned int count = 0;

  BEGIN_TEST;

  bf_init_memory (&mem);
  bf_allot_memory (&mem, 10);
  
  ASSERT_EQUAL (mem.size, 10, "Should have a size of 10 cells");
  
  diff = (uintptr_t)mem.last_useable - (uintptr_t)mem.content;
  ASSERT_EQUAL (diff, sizeof(cell) * 9, "The end and start of memory should have the actual size of cells");

  for (int i = 0; i < 10; i++)
    {
      if (mem.content[i].signed_value == 0)
        count++;
    }
  ASSERT_EQUAL (count, 10, "All cells should be initialized to zero");

  END_TEST;
}

void
test_inlining_cells_into_memory()
{
  bf_memory mem;
  char *bytes;
  cell *myhere;
  cell value;
 
  bf_init_memory (&mem);
  bf_allot_memory (&mem, 2);
  
  BEGIN_TEST;

  myhere = mem.content;
  bytes = (char *)mem.content;

  /* we assume that we are on 64bit */
  ASSERT_EQUAL (sizeof(cell), 8, "The test runs on 64bit machine");
  ASSERT_EQUAL (sizeof(unsigned long long), 8, "long long are at least 8 bytes long here");
  ASSERT_EQUAL (sizeof(long long), 8, "long long are at least 8 bytes long here");
  ASSERT_EQUAL (sizeof(double), 8, "double are at least 8 bytes long");
  ASSERT_EQUAL (sizeof(void *), 8, "void* are at least 8 bytes long");
  ASSERT_EQUAL (sizeof(char *), 8, "char* are at least 8 bytes long");

  /* we assume here, that we are on little-endian */
  BF_CLEAR_CELL(value);
  
  value.unsigned_value = 13;
  bf_memory_inlinecell (&mem, &myhere, value);

  ASSERT_EQUAL (bytes[0], 13, "Little-endian Byte[0] = 13");
  ASSERT_EQUAL (bytes[1], 0, "Little-endian Byte[1] = 0");
  ASSERT_EQUAL (bytes[2], 0, "Little-endian Byte[2] = 0");
  ASSERT_EQUAL (bytes[3], 0, "Little-endian Byte[3] = 0");
  ASSERT_EQUAL (bytes[4], 0, "Little-endian Byte[4] = 0");
  ASSERT_EQUAL (bytes[5], 0, "Little-endian Byte[5] = 0");
  ASSERT_EQUAL (bytes[6], 0, "Little-endian Byte[6] = 0");
  ASSERT_EQUAL (bytes[7], 0, "Little-endian Byte[7] = 0");

  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, sizeof(cell), "After inline one cell should differ");
  
  BF_CLEAR_CELL(value);
  value.unsigned_value = 0x08090a0b0c0d0e0fLL;
  bf_memory_inlinecell (&mem, &myhere, value);

  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, sizeof(cell) * 2, "After inline should moved two cells");
  
  ASSERT_EQUAL (bytes[8],  0x0f, "Little-endian Byte[8] = 0x0f");
  ASSERT_EQUAL (bytes[9],  0x0e, "Little-endian Byte[9] = 0x0e");
  ASSERT_EQUAL (bytes[10], 0x0d, "Little-endian Byte[10] = 0x0d");
  ASSERT_EQUAL (bytes[11], 0x0c, "Little-endian Byte[11] = 0x0c");
  ASSERT_EQUAL (bytes[12], 0x0b, "Little-endian Byte[12] = 0x0b");
  ASSERT_EQUAL (bytes[13], 0x0a, "Little-endian Byte[13] = 0x0a");
  ASSERT_EQUAL (bytes[14], 0x09, "Little-endian Byte[14] = 0x09");
  ASSERT_EQUAL (bytes[15], 0x08, "Little-endian Byte[15] = 0x08");

  value.unsigned_value = 20;
  bf_memory_inlinecell (&mem, &myhere, value);

  value.unsigned_value = 45;
  bf_memory_inlinecell (&mem, &myhere, value);

  value.unsigned_value = 50;
  bf_memory_inlinecell (&mem, &myhere, value);

  /* bytes should stay the same */
  ASSERT_EQUAL (bytes[0], 13, "Little-endian Byte[0] = 13");
  ASSERT_EQUAL (bytes[1], 0, "Little-endian Byte[1] = 0");
  ASSERT_EQUAL (bytes[2], 0, "Little-endian Byte[2] = 0");
  ASSERT_EQUAL (bytes[3], 0, "Little-endian Byte[3] = 0");
  ASSERT_EQUAL (bytes[4], 0, "Little-endian Byte[4] = 0");
  ASSERT_EQUAL (bytes[5], 0, "Little-endian Byte[5] = 0");
  ASSERT_EQUAL (bytes[6], 0, "Little-endian Byte[6] = 0");
  ASSERT_EQUAL (bytes[7], 0, "Little-endian Byte[7] = 0");
  
  ASSERT_EQUAL (bytes[8],  0x0f, "Little-endian Byte[8] = 0x0f");
  ASSERT_EQUAL (bytes[9],  0x0e, "Little-endian Byte[9] = 0x0e");
  ASSERT_EQUAL (bytes[10], 0x0d, "Little-endian Byte[10] = 0x0d");
  ASSERT_EQUAL (bytes[11], 0x0c, "Little-endian Byte[11] = 0x0c");
  ASSERT_EQUAL (bytes[12], 0x0b, "Little-endian Byte[12] = 0x0b");
  ASSERT_EQUAL (bytes[13], 0x0a, "Little-endian Byte[13] = 0x0a");
  ASSERT_EQUAL (bytes[14], 0x09, "Little-endian Byte[14] = 0x09");
  ASSERT_EQUAL (bytes[15], 0x08, "Little-endian Byte[15] = 0x08");

  
  /* nothing should be moved */
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, sizeof(cell) * 2, "here should not move");
  END_TEST;
}

void
test_inlining_bytes_into_memory()
{
  bf_memory mem;
  char *bytes;
  cell *myhere;
 
  bf_init_memory (&mem);
  bf_allot_memory (&mem, 1);
  
  BEGIN_TEST;

  myhere = mem.content;
  bytes = (char *)mem.content;

  bf_memory_inlinebyte (&mem, &myhere, 13);
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 1, "After inline one byte should differ");

  bf_memory_inlinebyte (&mem, &myhere, 100);
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 2, "After inline two bytes should differ");

  bf_memory_inlinebyte (&mem, &myhere, 90);
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 3, "After inline three bytes should differ");

  bf_memory_inlinebyte (&mem, &myhere, 20);
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 4, "After inline four bytes should differ");

  bf_memory_inlinebyte (&mem, &myhere, 40);
  bf_memory_inlinebyte (&mem, &myhere, 50);
  bf_memory_inlinebyte (&mem, &myhere, 30);
  bf_memory_inlinebyte (&mem, &myhere, 14);

  ASSERT_EQUAL (bytes[0], 13, "Little-endian Byte[0] = 13");
  ASSERT_EQUAL (bytes[1], 100, "Little-endian Byte[1] = 0");
  ASSERT_EQUAL (bytes[2], 90, "Little-endian Byte[2] = 0");
  ASSERT_EQUAL (bytes[3], 20, "Little-endian Byte[3] = 0");
  ASSERT_EQUAL (bytes[4], 40, "Little-endian Byte[4] = 0");
  ASSERT_EQUAL (bytes[5], 50, "Little-endian Byte[5] = 0");
  ASSERT_EQUAL (bytes[6], 30, "Little-endian Byte[6] = 0");
  ASSERT_EQUAL (bytes[7], 14, "Little-endian Byte[7] = 0");

  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 8, "Inlines should differ by 8 bytes");
  
  bf_memory_inlinebyte (&mem, &myhere, 20);
  bf_memory_inlinebyte (&mem, &myhere, 21);
  bf_memory_inlinebyte (&mem, &myhere, 22);

  /* nothing should be moved */
  ASSERT_EQUAL ((uintptr_t)myhere - (uintptr_t)mem.content, 8, "Inlines beyond end should not be possible");

  /* nothing should be changed */
  ASSERT_EQUAL (bytes[0], 13, "Little-endian Byte[0] = 13");
  ASSERT_EQUAL (bytes[1], 100, "Little-endian Byte[1] = 0");
  ASSERT_EQUAL (bytes[2], 90, "Little-endian Byte[2] = 0");
  ASSERT_EQUAL (bytes[3], 20, "Little-endian Byte[3] = 0");
  ASSERT_EQUAL (bytes[4], 40, "Little-endian Byte[4] = 0");
  ASSERT_EQUAL (bytes[5], 50, "Little-endian Byte[5] = 0");
  ASSERT_EQUAL (bytes[6], 30, "Little-endian Byte[6] = 0");
  ASSERT_EQUAL (bytes[7], 14, "Little-endian Byte[7] = 0");
  END_TEST;
}


int
main ()
{
  test_init_memory();
  test_allocating_memory();
  test_inlining_cells_into_memory();
  test_inlining_bytes_into_memory();
  
  return 0;
}
