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
bf_init_stream (bf_stream *stream)
{
  stream->type = BF_STREAM_EMPTY;
  stream->length = 0;
  stream->stream = 0;
  stream->pos = 0;
}

void
bf_free_stream (bf_stream *stream)
{
  if (stream->type == BF_STREAM_FILE)
    fclose ((FILE *) stream->stream);
}

void
bf_filestream (bf_stream *stream, FILE *file)
{
  stream->type = BF_STREAM_FILE;
  stream->stream = (char *) file;
  stream->length = 0;
  stream->pos = 0;
}

/* DOC: associates a std stream(stdin, stdout, stderror) */
void
bf_stdstream (bf_stream *stream, FILE *file)
{
  stream->type = BF_STREAM_STD;

  if (file == stdout)
    stream->stream = (char *) file;

  if (file == stdin)
    stream->stream = (char *) file;

  if (file == stderr)
    stream->stream = (char *) file;

  stream->length = 0;
  stream->pos = 0;
}

/* DOC: */
void
bf_memstream (bf_stream *stream, char *mem, cell length)
{
  stream->type = BF_STREAM_MEM;
  stream->stream = mem;
  stream->length = length;
  stream->pos = 0;
}

/* DOC: reads a value from stream and returns it as a cell */
cell
bf_getc (bf_stream *stream)
{
  cell buf;

  if ((stream->type == BF_STREAM_FILE) || (stream->type == BF_STREAM_STD))
    buf = (cell) getc ((FILE *) stream->stream);

  if (stream->type == BF_STREAM_MEM)
    {
      if (stream->pos < stream->length)
	buf = (cell) (stream->stream[stream->pos]);
      else
	buf = (cell) EOF;
    }
  stream->pos++;

  return buf;
}

/* DOC: prints a value to the stream */
void
bf_putc (bf_stream *stream, cell value)
{
  if ((stream->type == BF_STREAM_FILE) || (stream->type == BF_STREAM_STD))
    putc ((int) value, (FILE *) stream->stream);

  if (stream->type == BF_STREAM_MEM)
    {
      if (stream->pos < stream->length)
	stream->stream[stream->pos] = (char) value;
    }
  stream->pos++;
}
