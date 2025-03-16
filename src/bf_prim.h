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


#ifndef BF_PRIMH

#include <bf_state.h>
#include <bf_memory.h>

typedef void (*bf_prim) (bf_state * state);	/* pointer to primitives */

/* Bootforths convenient functions */
cell *bf_def_stub (bf_state * state, cell * prev, char *name, bf_prim dofield,
		   cell argfield);
cell *bf_def_word (bf_state * state, const char *name, unsigned char flags,
		   bf_prim dofield, cell argfield);
cell *bf_def_prim (bf_state * state, const char *name, bf_prim primitive);
cell *bf_def_literal (bf_state * state, const char *name, cell value);

cell *bf_def_iprim (bf_state * state, const char *name, bf_prim primitive);
cell *bf_def_iliteral (bf_state * state, const char *name, cell value);

void bf_eval (bf_state * state, char *string, ...);

/* virtual machine stuff */
void bf_init_vm (bf_state * state);

/* arithmetic and binary logic primitives */
void bf_prim_add (bf_state * state);
void bf_prim_sub (bf_state * state);
void bf_prim_mul (bf_state * state);
void bf_prim_div (bf_state * state);
void bf_prim_mod (bf_state * state);

void bf_prim_and (bf_state * state);
void bf_prim_or (bf_state * state);
void bf_prim_xor (bf_state * state);
void bf_prim_not (bf_state * state);
void bf_prim_lshift (bf_state * state);
void bf_prim_rshift (bf_state * state);

/* testing primitives */
void bf_prim_lower (bf_state * state);	  /*  <  */
void bf_prim_greater (bf_state * state);  /*  >  */
void bf_prim_equal (bf_state * state);	  /*  == */
void bf_prim_notequal (bf_state * state); /*  != */
void bf_prim_loweq (bf_state * state);	  /*  <= */
void bf_prim_greeq (bf_state * state);	  /*  >= */
void bf_prim_negate (bf_state * state);   /*  like in C the !  */

/* memory primitives */
void bf_prim_store (bf_state * state);
void bf_prim_fetch (bf_state * state);

void bf_prim_bstore (bf_state * state);
void bf_prim_bfetch (bf_state * state);

void bf_prim_allot (bf_state * state);
void bf_prim_align (bf_state * state);

void bf_prim_astore (bf_state * state);
void bf_prim_afetch (bf_state * state);
void bf_prim_ainc (bf_state * state);
void bf_prim_adec (bf_state * state);

void bf_prim_copy (bf_state * state);

/* dictionary */
void bf_prim_doprim (bf_state * state);
void bf_prim_doliteral (bf_state * state);
void bf_prim_dolink (bf_state * state);

void bf_prim_pushliteral (bf_state * state);
void bf_prim_pushsliteral (bf_state * state);

void bf_prim_dodoes (bf_state * state);

/* stack primitives */
void bf_prim_dup (bf_state * state);
void bf_prim_swap (bf_state * state);
void bf_prim_nip (bf_state * state);
void bf_prim_tuck (bf_state * state);
void bf_prim_drop (bf_state * state);
void bf_prim_over (bf_state * state);

void bf_prim_tor (bf_state * state);
void bf_prim_fromr (bf_state * state);
void bf_prim_tosr (bf_state * state);

/* I/O primitives */
void bf_prim_emit (bf_state * state);
void bf_prim_printtos (bf_state * state);

void bf_prim_type (bf_state * state);
void bf_prim_getkey (bf_state * state);

void bf_prim_write (bf_state * state);
void bf_prim_read (bf_state * state);

/* interpreter */
void bf_prim_execute (bf_state * state);
void bf_prim_lookup (bf_state * state);
void bf_prim_include (bf_state * state);
void bf_prim_towordtoken (bf_state * state);

void bf_prim_eval (bf_state * state);
void bf_prim_eachword_classic (bf_state * state);

/* parsing */
void bf_prim_parse (bf_state * state);
void bf_prim_sparse (bf_state * state);
void bf_prim_parse_name (bf_state * state);

/* compiler */
void bf_prim_inlinecell (bf_state * state);
void bf_prim_inlinebyte (bf_state * state);
void bf_prim_inlinestring (bf_state * state);
void bf_prim_inlineliteral (bf_state * state);
void bf_prim_inlinesliteral (bf_state * state);

void bf_prim_compile (bf_state * state);
void bf_prim_newword (bf_state * state);
void bf_prim_endcompile (bf_state * state);

void bf_prim_if (bf_state * state);
void bf_prim_else (bf_state * state);
void bf_prim_then (bf_state * state);

void bf_prim_repeat (bf_state * state);
void bf_prim_loop (bf_state * state);

void bf_prim_exitword (bf_state * state);
void bf_prim_does (bf_state * state);
void bf_prim_compdoes (bf_state * state);

void bf_prim_enable_compilation (bf_state * state);
void bf_prim_disable_compilation (bf_state * state);

/* literals */
void bf_prim_pushliteral (bf_state * state);
void bf_prim_pushsliteral (bf_state * state);

/* cpu emulation (internal use) */
void bf_prim_jmp (bf_state * state);
void bf_prim_jmpiftrue (bf_state * state);
void bf_prim_jmpiffalse (bf_state * state);

void bf_prim_settrue (bf_state * state);
void bf_prim_setfalse (bf_state * state);
void bf_prim_setnegative (bf_state * state);
void bf_prim_setpositive (bf_state * state);

/* strings */
void bf_prim_isnumber (bf_state * state);
void bf_prim_tonumber (bf_state * state);

/* system */
void bf_prim_bye (bf_state * state);

#define BF_PRIMH
#endif
