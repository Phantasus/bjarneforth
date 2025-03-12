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
 *
 * defines of bf 
 * */

#ifndef BF_DEFINESH

/* memory related constants */
#define BF_MEMORY_MIN_SIZE 512

/* stack related constants */
#define BF_STACK_ITEMS 64

/* character values */
#define BF_CHAR_SPACE   ' '
#define BF_CHAR_NEWLINE '\n'

/* virtual cpu flags */
#define BF_FLAG_TRUE 1
#define BF_FLAG_NULL 2
#define BF_FLAG_CARY 4
#define BF_FLAG_NEG  8
#define BF_FLAG_OVFL 16
#define BF_FLAG_COMP 32
#define BF_FLAG_UNDE 64

/* interpreter flags */
#define BF_FLAG_RUN  1		/* for bye */
#define BF_FLAG_MUL  2		/* multi line */
#define BF_FLAG_EOL  4		/* end of line */

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
enum BF_STREAM_TYPES
{
  BF_STREAM_EMPTY,
  BF_STREAM_FILE,
  BF_STREAM_MEM,
  BF_STREAM_STD
};

/* word flags */
enum BF_WORD_FLAGS
{
  BF_WORD_NORMAL = 0,
  BF_WORD_HIDDEN = 128,
  BF_WORD_ALLTIME = 64,
  BF_WORD_LENMASK = 63
};

/* convenient macros */
#define BF_STR_COUNT(string) string[0]
#define BF_STR_ADR(string) &string[1]

#define BF_WORD_XT(wptr) &wptr[BF_WORD_DOF]
#define BF_WORD_WT(wptr) &wptr[BF_WORD_PREV]	/* yes, could be simpler, but then
						   it wouldn't comply with BF_WORD_XT */
#define BF_VM_PRIM(state, prim) &state->vmprims[(BF_WORD_SIZE*prim)+BF_WORD_DOF]

#define BF_DEFINESH
#endif
