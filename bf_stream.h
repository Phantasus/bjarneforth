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
#include <bf_defines.h>

struct bf_stream
{
	cell type;        /* stream type */
	cell length;      /* length of stream */
	cell pos;         /* current position in stream */
	char *stream;     /* stream */
};

typedef struct bf_stream bf_stream;

void bf_init_stream(bf_stream *stream);
void bf_free_stream(bf_stream *stream);

void bf_filestream(bf_stream *stream, FILE *file);
void bf_memstream(bf_stream *stream, char *mem, cell length);
void bf_stdstream(bf_stream *stream, FILE *file);

cell bf_getc(bf_stream *stream);
void bf_putc(bf_stream *stream, cell value);

#define BF_STREAMH
#endif 
