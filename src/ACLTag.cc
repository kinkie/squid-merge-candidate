
/*
 * $Id: ACLTag.cc,v 1.2 2008/02/11 22:44:50 rousskov Exp $
 *
 *
 * SQUID Web Proxy Cache          http://www.squid-cache.org/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from
 *  the Internet community; see the CONTRIBUTORS file for full
 *  details.   Many organizations have provided support for Squid's
 *  development; see the SPONSORS file for full details.  Squid is
 *  Copyrighted (C) 2001 by the Regents of the University of
 *  California; see the COPYRIGHT file for full details.  Squid
 *  incorporates software developed and/or copyrighted by other
 *  sources; see the CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 * Copyright (c) 2009, Henrik Nordstrom <henrik@henriknordstrom.net>
 */

#include "squid.h"
#include "ACLTag.h"
#include "ACLStringData.h"
#include "ACLChecklist.h"
#include "HttpRequest.h"

/* explicit template instantiation required for some systems */

ACL::Prototype ACLTag::RegistryProtoype(&ACLTag::RegistryEntry_, "myportname");

ACLStrategised<const char *> ACLTag::RegistryEntry_(new ACLStringData, ACLTagStrategy::Instance(), "myportname");

int
ACLTagStrategy::match (ACLData<MatchType> * &data, ACLChecklist *checklist)
{
    if (checklist->conn() != NULL)
	return data->match (checklist->request->tag.buf());
    return 0;
}

ACLTagStrategy *
ACLTagStrategy::Instance()
{
    return &Instance_;
}

ACLTagStrategy ACLTagStrategy::Instance_;
