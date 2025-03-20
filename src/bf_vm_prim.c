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

#include "bf_state.h"
#include "bf_dict.h"
#include "bf_prim.h"


/* DOC: initializes the VM related and the internal primitives */
void
bf_init_vm (bf_state *state)
{
  /*
  state->vmprims = bf_define_iprim (state, "pushliteral", &bf_prim_pushliteral);
  
  bf_define_iprim (state, "pushsliteral", &bf_prim_pushsliteral);
  bf_define_iprim (state, "jmp",          &bf_prim_jmp);
  bf_define_iprim (state, "jmpiftrue",    &bf_prim_jmpiftrue);
  bf_define_iprim (state, "jmpiffalse",   &bf_prim_jmpiffalse);
  bf_define_iprim (state, "eachword",     &bf_prim_eachword_classic);
  bf_define_iprim (state, "(does)",       &bf_prim_does);
  

  state->eachword = (cell) BF_VM_PRIM (state, BF_VM_EACHWORD);
  */
  state->last = 0;		/* put it into their own vocabulary */
}

/* DOC: executes the primitive */
void
bf_prim_doprim (bf_state *state)	/* ( -- ) */
{
  cell value   = state->W[1];
  bf_prim prim = value.prim_ptr;
    
  prim (state);
}

/* DOC: execute the literal word */
void
bf_prim_doliteral (bf_state *state)	/* ( -- ) */
{
  bf_push_dstack (state, (cell) state->W[1]);
}

/* DOC: just execute the link word */
void
bf_prim_dolink (bf_state *state)	/* ( -- ) */
{
  cell value;
  
  bf_push_rstack (state, (cell) state->IP);

  value = state->W[1];
  state->IP = value.cell_ptr;

  while (((*state->IP).cell_ptr) != NULL)
    {
      state->W = (*state->IP).cell_ptr;
      state->IP++;
      
      bf_push_dstack (state, (cell) state->W);
      bf_prim_execute (state);
    }
  state->IP = (cell *) bf_pop_rstack (state).cell_ptr;
}

/* fname: ] */
/* DOC: turns compilation on */
void
bf_prim_enable_compilation (bf_state *state)
{
  state->flags |= flag_compiling ;
}

/* fname: [ */
/* DOC: turns compilation mode off */
void
bf_prim_disable_compilation (bf_state *state)
{
  state->flags |= ~flag_compiling ;
}

/* DOC: (internal) pushes a literal value to dstack */
void
bf_prim_pushliteral (bf_state *state)	/* ( -- literal ) */
{
  bf_stack_push (&state->dstack, (cell) * (state->IP));
  state->IP++;
}

/* DOC: (internal) pushes a string literal to dstack */
void
bf_prim_pushsliteral (bf_state *state)	/* ( -- str strlen ) */
{
  cell value = *state->IP;
  char *str  = value.char_ptr;

  bf_push_dstack_char_ptr (state, &str[1]);
  bf_push_dstack_int (state, str[0]);

  state->IP++;
}

/* DOC: (internal) handles a does word */
void
bf_prim_dodoes (bf_state *state)
{
  cell value = state->W[1];
  cell *arg  = value.cell_ptr;
  
  bf_push_dstack (state, (cell) arg[0]);
  state->W = arg;
  
  bf_prim_dolink (state);
}

/* DOC: (internal) a relative jump emulation */
void
bf_prim_jmp (bf_state *state)	/* ( -- ) */
{
  int *adr = (int *) state->IP;
  int offset = (int) adr[0];
  adr += offset;
  state->IP = (cell *) adr;
}

/* DOC: sets the vm flag TRUE */
void
bf_prim_settrue (bf_state *state)	/* ( -- ) */
{
  state->flags = state->flags | flag_true;
}

/* DOC: unsets the vmflag TRUE */
void
bf_prim_setfalse (bf_state *state)	/* ( -- ) */
{
  state->flags = state->flags & (~flag_true);
}

/* DOC: (internal) perfrom a relative jmp if TRUE flag is set */
void
bf_prim_jmpiftrue (bf_state *state)	/* ( -- ) */
{
  if (state->flags & flag_true)
    bf_prim_jmp (state);
  else
    state->IP++;
}

/* DOC: (internal) perform a relative jmp if TRUE flag isn't set */
void
bf_prim_jmpiffalse (bf_state *state)	/* ( -- ) */
{
  if (!(state->flags & flag_true))
    bf_prim_jmp (state);
  else
    state->IP++;
}

/* DOC: exits the Forth System by unsetting the RUN Flag */
void
bf_prim_bye (bf_state *state)	/* ( -- ) */
{
  state->flags = state->flags & (~flag_running);
}

/* DOC: classical Forth way of evaluating a word
   using threaded code
 */
void
bf_prim_eachword_classic (bf_state *state)	/* ( str strlen -- ) */
{
  cell value;
  cell *buf;
  char *data;

  bf_prim_isnumber (state);
  if (state->flags & flag_true)
    {
      bf_prim_tonumber (state);
      if (state->flags & flag_compiling)
	{
	  bf_inlinecell (state, bf_get_vmprimitive (state, BF_VM_PUSHLIT));
	  bf_prim_inlinecell (state);
	}
    }
  else
    {
      
      /* adding new word code */
      bf_prim_lookup (state);
      bf_prim_dup (state);

      value = bf_pop_dstack (state);
      buf   = value.cell_ptr;

      if (buf)
	{
	  buf--;
          value = *buf;
	  data  = value.char_ptr;

	  if (data[0] & immediate_word)
	    bf_prim_execute (state);
	  else
	    {
	      if (state->flags & flag_compiling)
		bf_prim_inlinecell (state);
	      else
		bf_prim_execute (state);
	    }
	}
    }
}

/* DOC: exits the currently executed thread */
void
bf_prim_exitword (bf_state *state)
{
  return;
}
