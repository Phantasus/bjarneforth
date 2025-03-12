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

#include <stdio.h>
#include <bf_debug.h>


/* DOC: dumps the memory of the given state to the file */
void
bf_dump_memory (bf_state *state, const char *filename)
{
  FILE *file = fopen ((char *) filename, "w");
  if (file != 0)
    {
      fwrite ((void *) state->memory.content, sizeof (cell),
	      state->memory.size, file);
      fclose (file);
    }
}
