/**
 * NSSDatabase.cc
 * Copyright 2009 Saleem Abdulrasool <compnerd@compnerd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

#include "NSSDatabase.hh"

using namespace SystemConfiguration;

#define N_ELEMENTS(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef struct _DatabaseMapEntry
{
   const NSSDatabase::Database database;
   const std::string string;
} DatabaseMapEntry;

static const DatabaseMapEntry _database_map[] =
{
   { NSSDatabase::passwd, "passwd" },
   { NSSDatabase::group, "group" },
   { NSSDatabase::shadow, "shadow" },
   { NSSDatabase::hosts, "hosts" },
   { NSSDatabase::networks, "networks" },
   { NSSDatabase::protocols, "protocols" },
   { NSSDatabase::services, "services" },
   { NSSDatabase::ethers, "ethers" },
   { NSSDatabase::RPC, "rpc" },
   { NSSDatabase::netgroup, "netgroup" },
};

static NSSDatabase::Database
database_from_string(const std::string & database)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_database_map); i++)
      if (_database_map[i].string == database)
         return _database_map[i].database;
   throw InvalidDatabaseException("Invalid Database: " + database);
}

static std::string
string_from_database(const NSSDatabase::Database database)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_database_map); i++)
      if (_database_map[i].database == database)
         return _database_map[i].string;
   throw InvalidDatabaseException("Invalid Database: " + database);
}

InvalidDatabaseException::InvalidDatabaseException(const std::string & message)
   : _message(message)
{
}

InvalidDatabaseException::~InvalidDatabaseException(void) throw ()
{
}

const char *
InvalidDatabaseException::what(void) throw ()
{
   return _message.c_str();
}

NSSDatabase::NSSDatabase(void)
{
}

NSSDatabase::NSSDatabase(const Database database)
   : _database(database)
{
}

NSSDatabase::NSSDatabase(const NSSDatabase & database)
   : _database(database._database)
{
}

NSSDatabase::NSSDatabase(const std::string & database)
   : _database(database_from_string(database))
{
}

NSSDatabase::~NSSDatabase(void)
{
}

NSSDatabase &
NSSDatabase::operator=(const Database database)
{
   _database = database;
   return *this;
}

NSSDatabase &
NSSDatabase::operator=(const std::string & database)
{
   _database = database_from_string(database);
   return *this;
}

bool
NSSDatabase::operator==(const NSSDatabase & other)
{
   return _database == other._database;
}

bool
NSSDatabase::operator==(const std::string & other)
{
   return _database == database_from_string(other);
}

NSSDatabase::operator std::string(void) const
{
   return string_from_database(_database);
}

NSSDatabase::operator Database(void) const
{
   return _database;
}

