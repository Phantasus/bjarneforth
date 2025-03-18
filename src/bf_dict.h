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

#ifndef BF_DICTH

#include "bf_state.h"

/* this header is solely here for describing
   the memory structure of a dictionary entry */

cell bf_get_vmprimitive (bf_state *state, bf_opcode opcode);

cell *bf_inline_word (bf_state *state, bf_word *word);
cell *bf_define_word (bf_state *state, const char *name, bf_word_flag flags,
                      bf_prim dofield, cell argfield);
cell *bf_define_literal (bf_state *state, const char *name, cell value);
cell *bf_define_iprim (bf_state *state, const char *name, bf_prim primitive);
cell *bf_define_iliteral (bf_state *state, const char *name, cell value);

/* convenient macros */
#define BF_STR_COUNT(string) string[0]
#define BF_STR_ADR(string) &string[1]

#define BF_WORD_XT(word_ptr) (char *)&(word_ptr->dofield)
#define BF_WORD_WT(word_ptr) (char *)&(word_ptr->prev)	/* yes, could be simpler, but then
						   it wouldn't comply with BF_WORD_XT */
#define BF_VM_PRIM(state, prim) &state->vmprims[(BF_WORD_SIZE*prim)+BF_WORD_DOF]


#define BF_DICTH
#endif
