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

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <sys/types.h>

#include "config.h"

#include "buffer.h"
#include "access.h"

typedef struct
{
  void (*register_to_engine) (const access_t *);
  void (*put_data) (buffer_t *, char *, size_t);
  size_t max_data;
}
protocol_t;

extern const protocol_t *protocol;

#ifdef WITH_P3
extern const protocol_t p3_protocol;
#endif

#endif /* __PROTOCOL_H__ */