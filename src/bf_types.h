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
  flag_debug      = 8,
  flag_compiling  = 32,
};

/* true/false values */
#define BF_VALUE_TRUE  1
#define BF_VALUE_FALSE 0

/* virtual machine indexes */
typedef enum
{
  BF_VM_NOP    = 0,
  BF_VM_PUSHLIT,
  BF_VM_PUSHSLIT,
  BF_VM_JMP,
  BF_VM_JMPIFTRUE,
  BF_VM_JMPIFFALSE,
  BF_VM_EACHWORD,
  BF_VM_DOES
} bf_opcode;

/* word offsets/indexes */
enum BF_WORD_INDEXES
{
  BF_WORD_PREV,
  BF_WORD_NAME,
  BF_WORD_DOF,
  BF_WORD_ARGF,
  BF_WORD_SIZE
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
typedef enum
{
  unknown_word = 0,
  normal_word = 1,
  hidden_word = 2,
  immediate_word = 4,
} bf_word_flag;

typedef intptr_t bf_int;
typedef uintptr_t bf_uint;
typedef bf_uint bf_offset;

struct bf_state;
typedef struct bf_state bf_state;
typedef void (*bf_prim) (bf_state * state);	/* pointer to primitives */

/* defined for 64bit on x86 */
typedef union cell {
  bf_int      signed_value;    /* 8 bytes */
  bf_uint     unsigned_value;  /* 8 bytes */
  double      float_value;     /* 8 bytes */
  void        *ptr_value;       /* 8 bytes */
  char        *char_ptr;        /* 8 bytes */
  union cell  *cell_ptr;        /* 8 bytes, a pointer to a cell*/
  bf_prim      prim_ptr;        /* 8 bytes, points to a prim */
} cell; /* a cel, should fit into 8 bytes on 64bit */

typedef unsigned char byte;	/* a byte */

/* defines the basic dictionary entry of a word
 * it's less efficiently defined as it could be, but in the age of
 * wasteful AI crap, some wastefulness for the sake of less errors
 * based on bit-fiddling, is acceptable.
 */
struct bf_word
{
  cell prev;
  cell flags;
  cell dofield;
  cell argfield;
};

typedef struct bf_word bf_word;

/* -------------------------- macros ----------------------------------------------- */

#define BF_CLEAR_CELL(cell_name) \
  memset(&cell_name, 0, sizeof(cell))

#define BF_TYPESH
#endif
