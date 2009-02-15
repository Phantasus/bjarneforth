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

#ifndef BF_VARIABLESH

#include <bf_types.h>

struct bf_variables
{
	/* -- used by words/primitives -- */

	cell base;   /* current number base */
	
	cell state;  /* compiler state */
	cell istate; /* interpreter state */

	cell eachword; /* XT which gets executed at each read word */
	cell lookup;  /* XT which gets executed if a word gets lookuped
			     ( str len -- ) */

	/* memory areas */
	cell *last;  /* adr of last defined word */
	cell *here;  /* adr of current free heap cell */
	cell *dhere; /* next free cell in the dictionary */
	cell *strs;  /* a memory area for strings */

	char *tib;         /* text input buffer adr */
	cell tibsize;      /* size of the tib */ 
	
	char def_ws[4];    /* default whitespaces */
	char *ws;          /* current whitespace string */

	cell *lastwt;      /* word token of last looked up word */

	struct {           /* internal variables don't touch them! */
	char *evaltib;     /* for bf_eval */
	} intern;


};

typedef struct bf_variables bf_variables;

int bf_init_variables(bf_variables *vars);
int bf_free_variables(bf_variables *vars);


#define BF_VARiABLESH
#endif
