/*
 * Copyright (C) 2002  Jean-Charles Salzeber <jc@varspool.net>
 *
 * This file is part of pengfork.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *                
 */

#include <stdio.h>
#include <stdlib.h>

#include "prot30.h"
#include "config.h"
#include "access.h"
#include "if.h"


int
main (argc, argv)
     int argc;
     char **argv;
{

  parse_config_file ("peng.cf");
  if (!config_set_functions ())
    {
      fprintf (stderr, "Fatal error, exiting.\n");
      exit (1);
    }

  if (if_connect () && access_connect ())
    prot30_start ();
  else
    {
      fprintf (stderr, "Fatal error, exiting.\n");
      exit (1);
    }

  return 0;
}