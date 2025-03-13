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
 **/

#ifndef BF_TYPESH
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* virtual cpu flags */
enum bf_vm_flag {
  flag_unset      = 0,
  flag_true       = 1,
  flag_negative   = 2,
  flag_running    = 4,
  flag_eol        = 8 /* end of line */
};

/* true/false values */
#define BF_VALUE_TRUE  1
#define BF_VALUE_FALSE 0

/* virtual machine indexes */
enum BF_VM_PRIMS
{
  BF_VM_PUSHLIT,
  BF_VM_PUSHSLIT,
  BF_VM_JMP,
  BF_VM_JMPIFTRUE,
  BF_VM_JMPIFFALSE,
  BF_VM_EACHWORD,
  BF_VM_DOES
};

/* word offsets/indexes */
enum BF_WORD_INDEXES
{
  BF_WORD_PREV,
  BF_WORD_NAME,
  BF_WORD_DOF,
  BF_WORD_ARGF,
  BF_WORD_SIZE
};

/* base values */
enum BF_BASE_VALUES
{
  BF_BASE_DEC = 10,
  BF_BASE_HEX = 16,
  BF_BASE_BIN = 2,
  BF_BASE_OCT = 8
};

/* stream types */
enum bf_stream_type
{
  bf_empty_stream,
  bf_file_stream,
  bf_memory_stream,
  bf_stdio_stream
};

/* word flags */
enum bf_word_flag
{
  BF_WORD_NORMAL = 0,
  BF_WORD_HIDDEN = 128,
  BF_WORD_ALLTIME = 64,
  BF_WORD_LENMASK = 63
};

typedef union {
  signed int    signed_value;
  unsigned int  unsigned_value;
  float         float_value;
  void         *ptr_value;
  char         *char_ptr;
} cell; /* a cell */

typedef unsigned char byte;	/* a byte */

/* -------------------------- macros ----------------------------------------------- */

#define BF_CLEAR_CELL(cell_name) \
  memset(&cell_name, 0, sizeof(cell))

/* memory related constants */
#define BF_MEMORY_MIN_SIZE 512

/* stack related constants */
#define BF_STACK_ITEMS 64

/* character values */
#define BF_CHAR_SPACE   ' '
#define BF_CHAR_NEWLINE '\n'

/* convenient macros */
#define BF_STR_COUNT(string) string[0]
#define BF_STR_ADR(string) &string[1]

#define BF_WORD_XT(wptr) &wptr[BF_WORD_DOF]
#define BF_WORD_WT(wptr) &wptr[BF_WORD_PREV]	/* yes, could be simpler, but then
						   it wouldn't comply with BF_WORD_XT */
#define BF_VM_PRIM(state, prim) &state->vmprims[(BF_WORD_SIZE*prim)+BF_WORD_DOF]

#define BF_TYPESH
#endif
