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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bf_defines.h>
#include <bf_variables.h>

int bf_init_variables (bf_variables *vars)
{
	vars->last=0;
	vars->tib=0;
	vars->here=0;
	vars->state=0;
	vars->istate=BF_FLAG_RUN;
	vars->dhere=0;
	vars->tibsize=0;
	vars->strs=0;

	vars->def_ws[0]=(char)3;
	vars->def_ws[1]=' ';
	vars->def_ws[2]='\t';
	vars->def_ws[3]='\n';
	vars->ws=vars->def_ws;

	vars->base=BF_BASE_DEC;
	return 0;
}

int bf_free_variables (bf_variables *p_vars)
{
  memset ((void *)p_vars, 0, sizeof (bf_variables));

	return 0;
}
