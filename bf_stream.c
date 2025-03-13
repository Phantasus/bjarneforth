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

#include <bf_stream.h>

void
bf_clear_stream (bf_stream *stream)
{
  stream->type = bf_empty_stream;
  
  stream->length      = 0;
  stream->file_ptr    = NULL;
  stream->content_ptr = NULL;
  stream->pos         = 0;
}

void
bf_close_stream (bf_stream *stream)
{
  if (stream->type == bf_file_stream)
    fclose (stream->file_ptr);

  bf_clear_stream(stream);
}

/* DOC: associates a stdio stream(stdin, stdout, stderror) */
void
bf_open_stdstream (bf_stream *stream, FILE *file)
{
  stream->type = bf_stdio_stream;

  stream->file_ptr = file;
  stream->length   = -1;    /* these streams have an unknown size */
  stream->pos      = 0;
}

/* DOC: */
void
bf_open_memstream (bf_stream *stream, char *mem, size_t length)
{
  stream->type        = bf_memory_stream;
  stream->content_ptr = mem;
  stream->length      = length;
  stream->pos         = 0;
}

/* DOC: reads a value from stream and returns it as a cell */
cell
bf_getc (bf_stream *stream)
{
  int buf;
  cell read_char;

  read_char.signed_value = 0;
  
  switch (stream->type) {
  case bf_stdio_stream:
    buf = getc (stream->file_ptr);

    if (buf == EOF)
      stream->length = stream->pos;
    else
      stream->pos++;

    break;
  case bf_memory_stream:
    if (stream->pos < stream->length)
      buf = stream->content_ptr[stream->pos];
    else
      buf = EOF;
    
    if (stream->pos < stream->length)
      stream->pos++;
  }

  read_char.signed_value = buf;
  
  return read_char;
}

/* DOC: prints a value to the stream */
void
bf_putc (bf_stream *stream, cell value)
{
  switch (stream->type) {
  case bf_stdio_stream:
    putc (value.signed_value, stream->file_ptr);
    break;
  case  bf_memory_stream:
    stream->content_ptr[stream->pos] = (char) value.unsigned_value;
  }
  
  stream->pos++;
}
