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

#ifndef BF_STREAMH

#include <stdio.h>
#include <bf_types.h>

typedef struct
{
  enum bf_stream_type type;	/* stream type */
  int  length;		        /* length of stream */
  unsigned int pos;             /* current position in stream */
  
  char *content_ptr;		/* stream content for memory stream */
  FILE *file_ptr;		/* stream content for file stream */
} bf_stream;

void bf_clear_stream (bf_stream * stream);
void bf_close_stream (bf_stream * stream);

void bf_open_memstream (bf_stream * stream, char *mem, size_t length);
void bf_open_stdstream (bf_stream * stream, FILE * file);

cell bf_getc (bf_stream * stream);
void bf_putc (bf_stream * stream, cell value);

#define BF_STREAMH
#endif
