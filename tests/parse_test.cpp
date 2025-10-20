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

#include <bf_state.h>
#include <bf_prim.h>
#include <stdio.h>

void
helloprim (bf_state *state)
{
  printf ("\nI'm a primitive, beware of me!\n");
}

int
main ()
{
  char str[] = " lovely";
  char astr[] = " barbie";
  char bstr[] = " link";
  astr[0] = 6;
  str[0] = 6;
  bstr[0] = 4;

  printf ("basic init\n");
  bf_state state;
  bf_init_state (&state);

  printf ("push: 1 2 3 \n");
  bf_init_state (&(state));
  newline (&state);
  bf_push (&state.dstack, 1);
  bf_push (&state.dstack, 2);
  bf_push (&state.dstack, 3);

  printf ("over; expected result: 1 2 3 2 \n");
  over (&state);
  dots (&state);
  newline (&state);
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));
  printf ("TOS: %d\n", bf_pop (&(state.dstack)));

  bf_allot (&state, 1024);
  state.vars.tib = (char *) &state.memory.content[512];
  state.vars.tibsize = 256;

  /* initing word tests */
  state.memory.content[0] = 0;	/* link ptr=0 */
  state.memory.content[1] = (cell) & str;	/* name lovely */
  state.memory.content[2] = (cell) & doliteral;	/* DO field */
  state.memory.content[3] = 45;	/* ARG field */
  state.vars.last = (cell *) & (state.memory.content[0]);

  state.memory.content[4] = (cell) & (state.memory.content[0]);	/* link -> lovely */
  state.memory.content[5] = (cell) & astr;	/* name barbie */
  state.memory.content[6] = (cell) & doprim;	/* DO field */
  state.memory.content[7] = (cell) & helloprim;	/* ARG field */
  state.vars.last = &(state.memory.content[4]);

  state.memory.content[8] = (cell) & (state.memory.content[4]);	/* link -> lovely */
  state.memory.content[9] = (cell) & bstr;	/* name link */
  state.memory.content[10] = (cell) & dolink;	/* DO field */
  state.memory.content[11] = (cell) & state.memory.content[12];	/* ARG field */
  state.vars.last = &(state.memory.content[8]);

  state.memory.content[12] = (cell) & state.memory.content[2];
  state.memory.content[13] = (cell) & state.memory.content[6];
  state.memory.content[14] = (cell) & state.memory.content[50];
  state.memory.content[15] = 2;
  state.memory.content[16] = (cell) & state.memory.content[6];
  state.memory.content[17] = (cell) & state.memory.content[52];
  state.memory.content[18] = (cell) 666;
  state.memory.content[19] = (cell) & state.memory.content[54];
  state.memory.content[20] = (cell) & astr;
  state.memory.content[21] = 0;

  printf ("XT: %d\n", state.memory.content[16]);
  state.memory.content[50] = (cell) & doprim;
  state.memory.content[51] = (cell) & jmpiftrue;

  state.memory.content[52] = (cell) & doprim;
  state.memory.content[53] = (cell) & pushliteral;

  state.memory.content[54] = (cell) & doprim;
  state.memory.content[55] = (cell) & pushsliteral;

  printf ("barbie -> lovely: %d %d\n", &(state.memory.content[0]),
	  state.memory.content[0]);

  printf ("\n --- Word tests  ---\n");
  printf ("XT should be: %d\n", &(state.memory.content[2]));
  bf_push (&state.dstack, (cell) & astr[1]);
  bf_push (&state.dstack, 6);
  lookup (&state);
  dots (&state);
  newline (&state);
  execute (&state);
  dots (&state);
  newline (&state);

  bf_init_stack (&state.dstack);


  printf ("\n--- parse number test --- \n");
  bf_push (&state.dstack, '\n');
  getline (&state);
  parse (&state);
  printf ("Ok I parsed it and?\n");
  dots (&state);
  newline (&state);

  remsign (&state);
  isnumber (&state);
  tonumber (&state);

  dot (&state);
  newline (&state);

  printf ("\n--- END OF PRIMITIVE TESTER ---\n");
  return 0;
}
