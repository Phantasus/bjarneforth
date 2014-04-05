# ----------------------------------------------------------------------------
# Copyright 2007 -- 2014 Josef Philip Bernhart
#
# This file is part of BootForth.
#
# BootForth is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
# 
# BootForth is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with BootForth.  If not, see <http://www.gnu.org/licenses/>.
#                                                                            
# ----------------------------------------------------------------------------

SRC=src
LIB=lib

# GCC 4.8.2, C99 STD
CFLAGS=-I$(SRC) --ansi -pedantic -std=c99 -Wall -Wextra -Werror
CC=gcc $(CFLAGS)

.PHONY: all doc lib

all: lib doc

doc: Doxyfile src/*.c src/*.h
	doxygen

lib: src/*.c src/*.h 
	$(CC) src/*.c -shared -o $(LIB)
