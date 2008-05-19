/*  Copyright 2007, 2008 Josef Philip Bernhart

    This file is part of BootForth.

    BootForth is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    BootForth is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BootForth.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BF_PRIMH

#include <bf_state.h>
#include <bf_memory.h>

typedef void (*bf_prim)(bf_state *state); /* pointer to primitives */

/* Bootforths convenient functions */
cell *bf_def_stub(bf_state *state, cell *prev, char *name, bf_prim dofield, cell argfield);
cell *bf_def_word(bf_state *state, const char *name, unsigned char flags, bf_prim dofield, cell argfield);
cell *bf_def_prim(bf_state *state, const char *name, bf_prim primitive);
cell *bf_def_literal(bf_state *state, const char *name, cell value);

cell *bf_def_iprim(bf_state *state, const char *name, bf_prim primitive);
cell *bf_def_iliteral(bf_state *state, const char *name, cell value);

void bf_eval(bf_state *state, char *string, ...);

/* virtual machine stuff */
void bf_init_vm(bf_state *state);

/* arithmetic and binary logic primitives */
void prim_add(bf_state *state);
void prim_sub(bf_state *state);
void prim_mul(bf_state *state);
void prim_div(bf_state *state);
void prim_mod(bf_state *state);

void prim_and(bf_state *state);
void prim_or(bf_state *state);
void prim_xor(bf_state *state);
void prim_not(bf_state *state);
void prim_lshift(bf_state *state);
void prim_rshift(bf_state *state);

/* testing primitives */
void prim_lower(bf_state *state);    /*  <  */
void prim_greater(bf_state *state);  /*  >  */
void prim_equal(bf_state *state);    /*  == */
void prim_notequal(bf_state *state); /*  != */
void prim_loweq(bf_state *state);    /*  <= */
void prim_greeq(bf_state *state);    /*  >= */
void prim_opposite(bf_state *state); /*  like in C the !  */

/* memory primitives */ 
void prim_store(bf_state *state);
void prim_fetch(bf_state *state);

void prim_bstore(bf_state *state);
void prim_bfetch(bf_state *state);

void prim_allot(bf_state *state);
void prim_align(bf_state *state);

void prim_astore(bf_state *state);
void prim_afetch(bf_state *state);
void prim_ainc(bf_state *state);
void prim_adec(bf_state *state);

void prim_copy(bf_state *state);

/* dictionary */
void prim_doprim(bf_state *state);
void prim_doliteral(bf_state *state);
void prim_dolink(bf_state *state);

void prim_pushliteral(bf_state *state);
void prim_pushsliteral(bf_state *state);

void prim_dodoes(bf_state *state);

/* stack primitives */
void prim_dup(bf_state *state);
void prim_swap(bf_state *state);
void prim_nip(bf_state *state);
void prim_tuck(bf_state *state);
void prim_drop(bf_state *state);
void prim_over(bf_state *state);

void prim_tor(bf_state *state);
void prim_fromr(bf_state *state);
void prim_tosr(bf_state *state);

/* I/O primitives */
void prim_space(bf_state *state);
void prim_newline(bf_state *state);
void prim_emit(bf_state *state);
void prim_dot(bf_state *state);
void prim_dots(bf_state *state);
void prim_printtos(bf_state *state);

void prim_type(bf_state *state);
void prim_getkey(bf_state *state);

void prim_write(bf_state *state);
void prim_read(bf_state *state);

/* interpreter */
void prim_execute(bf_state *state);
void prim_lookup(bf_state *state);
void prim_include(bf_state *state);
void prim_towordtoken(bf_state *state);

void prim_eval(bf_state *state);
void prim_eachword_classic(bf_state *state);

void prim_parse(bf_state *state);
void prim_sparse(bf_state *state);
void prim_wsparse(bf_state *state);

/* compiler */
void prim_inlinecell(bf_state *state);
void prim_inlinebyte(bf_state *state);
void prim_inlinestring(bf_state *state);
void prim_inlineliteral(bf_state *state);
void prim_inlinesliteral(bf_state *state);

void prim_compile(bf_state *state); 
void prim_newword(bf_state *state);
void prim_endcompile(bf_state *state);

void prim_if(bf_state *state);
void prim_else(bf_state *state);
void prim_then(bf_state *state);

void prim_repeat(bf_state *state);
void prim_loop(bf_state *state);

void prim_exitword(bf_state *state);
void prim_does(bf_state *state);
void prim_compdoes(bf_state *state);

void prim_setstate(bf_state *state);
void prim_unsetstate(bf_state *state);

/* literals */
void prim_pushliteral(bf_state *state);
void prim_pushsliteral(bf_state *state);

/* cpu emulation (internal use) */
void prim_jmp(bf_state *state);
void prim_jmpiftrue(bf_state *state);
void prim_jmpiffalse(bf_state *state);

void prim_settrue(bf_state *state);
void prim_setfalse(bf_state *state);
void prim_setnegative(bf_state *state);
void prim_setpositive(bf_state *state);

/* strings */
void prim_isnumber(bf_state *state);
void prim_tonumber(bf_state *state);

/* system */
void prim_bye(bf_state *state);

#define BF_PRIMH
#endif
