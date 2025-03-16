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
#include "bf_prim.h"


/* DOC: initializes the VM related and the internal primitives */
void
bf_init_vm (bf_state *state)
{
  state->vmprims = bf_def_iprim (state, "pushliteral", &bf_prim_pushliteral);
  bf_def_iprim (state, "pushsliteral", &bf_prim_pushsliteral);
  bf_def_iprim (state, "jmp", &bf_prim_jmp);
  bf_def_iprim (state, "jmpiftrue", &bf_prim_jmpiftrue);
  bf_def_iprim (state, "jmpiffalse", &bf_prim_jmpiffalse);
  bf_def_iprim (state, "eachword", &bf_prim_eachword_classic);
  bf_def_iprim (state, "(does)", &bf_prim_does);

  state->vars.eachword = (cell) BF_VM_PRIM (state, BF_VM_EACHWORD);
  state->vars.last = 0;		/* put it into their own vocabulary */
}

/* DOC: executes the primitive */
void
bf_prim_doprim (bf_state *state)	/* ( -- ) */
{
  bf_prim prim = (bf_prim) state->W[1];
  prim (state);
}

/* DOC: execute the literal word */
void
bf_prim_doliteral (bf_state *state)	/* ( -- ) */
{
  bf_stack_push (&(state->dstack), (cell) state->W[1]);
}

/* DOC: just execute the link word */
void
bf_prim_dolink (bf_state *state)	/* ( -- ) */
{
  bf_stack_push (&(state->rstack), (cell) state->IP);
  state->IP = (cell *) state->W[1];

  while ((*state->IP) != 0)
    {
      state->W = (cell *) state->IP[0];
      state->IP++;
      bf_stack_push (&(state->dstack), (cell) state->W);
      bf_prim_execute (state);
    }
  state->IP = (cell *) bf_stack_pop (&(state->rstack));
}

/* fname: ] */
/* DOC: turns compilation on */
void
bf_prim_enable_compilation (bf_state *state)
{
  state->vars.state = 1;
}

/* fname: [ */
/* DOC: turns compilation mode off */
void
bf_prim_disable_compilation (bf_state *state)
{
  state->vars.state = 0;
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
  char *str = (char *) *(state->IP);
  bf_stack_push (&state->dstack, (cell) & str[1]);
  bf_stack_push (&state->dstack, (cell) str[0]);

  state->IP++;
}

/* DOC: (internal) handles a does word */
void
bf_prim_dodoes (bf_state *state)
{
#ifdef DEBUG
  printf ("DODOES\n");
#endif

  cell *arg = (cell *) state->W[1];
  bf_stack_push (&(state->dstack), (cell) arg[0]);
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

#ifdef DEBUG
  printf ("JMP to: %d\n", offset);
#endif
}

/* DOC: sets the vm flag TRUE */
void
bf_prim_settrue (bf_state *state)	/* ( -- ) */
{
#ifdef DEBUG
  printf ("->true\n");
#endif
  state->flags = state->flags | BF_FLAG_TRUE;
}

/* DOC: unsets the vmflag TRUE */
void
bf_prim_setfalse (bf_state *state)	/* ( -- ) */
{
#ifdef DEBUG
  printf ("->false\n");
#endif

  state->flags = state->flags & (~BF_FLAG_TRUE);
}

/* DOC: sets the vm flag NEG */
void
bf_prim_setnegative (bf_state *state)	/* ( -- ) */
{
  state->flags = state->flags | BF_FLAG_NEG;
}

/* DOC: unsets the vm flag NEG */
void
bf_prim_setpositive (bf_state *state)	/* ( -- ) */
{
  state->flags = state->flags & (~BF_FLAG_NEG);
}

/* DOC: (internal) perfrom a relative jmp if TRUE flag is set */
void
bf_prim_jmpiftrue (bf_state *state)	/* ( -- ) */
{
  if (state->flags & BF_FLAG_TRUE)
    bf_prim_jmp (state);
  else
    state->IP++;
}

/* DOC: (internal) perform a relative jmp if TRUE flag isn't set */
void
bf_prim_jmpiffalse (bf_state *state)	/* ( -- ) */
{
  if (!(state->flags & BF_FLAG_TRUE))
    bf_prim_jmp (state);
  else
    state->IP++;
}

/* DOC: exits the Forth System by unsetting the RUN Flag */
void
bf_prim_bye (bf_state *state)	/* ( -- ) */
{
  state->vars.istate = state->vars.istate & (~BF_FLAG_RUN);
}

/* DOC: classical Forth way of evaluating a word */
void
bf_prim_eachword_classic (bf_state *state)	/* ( str strlen -- ) */
{
  cell *buf;
  char *data;

  bf_prim_isnumber (state);
  if (state->flags & BF_FLAG_TRUE)
    {
      bf_prim_tonumber (state);
      if (state->vars.state)
	{
#ifdef DEBUG
	  printf (",pshlit\n");
#endif
	  bf_inlinecell (state, (cell) BF_VM_PRIM (state, BF_VM_PUSHLIT));
	  bf_prim_inlinecell (state);
	}
    }
  else
    {
#ifdef DEBUG
      printf ("STATE: %d\n", state->vars.state);
#endif

      /* adding new word code */
      bf_prim_lookup (state);
      bf_prim_dup (state);
      buf = (cell *) bf_stack_pop (&(state->dstack));

      if (buf != 0)
	{
	  buf--;
	  data = (char *) *buf;

	  if (data[0] & BF_WORD_ALLTIME)
	    bf_prim_execute (state);
	  else
	    {
	      if (state->vars.state)
		bf_prim_inlinecell (state);
	      else
		bf_prim_execute (state);
	    }
	}
    }
}
