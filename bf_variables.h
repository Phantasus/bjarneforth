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

  size_t base;			/* current number base */

  int state;			/* compiler state */
  int istate;			/* interpreter state */
  cell eachword;		/* XT which gets executed at each read word */

  /* memory areas */
  cell *last;			/* address of last defined word */
  cell *here;			/* address of current free heap cell */
  cell *dhere;			/* next free cell in the dictionary */
  char *strs;			/* a memory area for strings */

  char *tib;			/* text input buffer adr */
  size_t tibsize;		/* size of the tib */

  char def_ws[4];		/* default whitespaces */
  char *ws;			/* current whitespace string */

  cell *lastwt;			/* word token of last looked up word */
};

typedef struct bf_variables bf_variables;

int bf_init_variables (bf_variables * vars);
int bf_free_variables (bf_variables * vars);


#define BF_VARiABLESH
#endif
