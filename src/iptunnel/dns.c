/*
 * Copyright (C) 2002  Jean-Charles Salzeber <jc@varspool.net>
 *
 * This file is part of penggy.
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

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "gettext.h"
#include "log.h"
#include "iptunnel/dns.h"

int dns_set = 0;

int
set_dns (domain, dns)
     char *domain;
     struct in_addr dns;
{
  FILE *f;
  struct stat st;

  if (!stat ("/etc/resolv.peng", &st))
    log (LOG_WARNING, gettext ("/etc/resolv.peng exists\n"));
  else
    {
      if (rename ("/etc/resolv.conf", "/etc/resolv.peng"))
        {
          log (LOG_ERR, gettext ("Could not rename /etc/resolv.conf: %s (%d)\n"),
               strerror (errno), errno);
          exit (1);
        }
    }

  /* Now create a new resolv.conf from scratch */
  f = fopen ("/etc/resolv.conf", "w");
  if (f != NULL)
    {
      fprintf (f, "# This file has been automaticly generated by penggy\n");
      fprintf (f, "# A backup of your old configuration has been made in"
               " /etc/resolv.peng\n");
      fprintf (f, "# It will be restored when connection is down\n\n");
      fprintf (f, "domain %s\n", domain);
      fprintf (f, "search %s\n", domain);
      fprintf (f, "nameserver %s\n", inet_ntoa (dns));
      fclose (f);
    }
  else
    {
      log (LOG_ERR, gettext ("Could not create /etc/resolv.conf: %s (%d)\n"),
           strerror (errno), errno);
      exit (1);
    }
  dns_set = 1;

  return 1;
}

int
unset_dns ()
{
  struct stat st;

  if (!stat ("/etc/resolv.peng", &st))
    {
      if (unlink ("/etc/resolv.conf"))
        {
          log (LOG_WARNING, gettext ("Could not delete /etc/resov.conf: %s (%d)\n"),
               strerror (errno), errno);
          return 0;
        }

      if (rename ("/etc/resolv.peng", "/etc/resolv.conf"))
        {
          log (LOG_WARNING, gettext ("Could not rename /etc/resolv.peng: %s (%d)\n"),
               strerror (errno), errno);
          return 0;
        }
      dns_set = 0;
      return 1;
    }
  else
    {
      dns_set = 0;
      return 0;
    }
}
