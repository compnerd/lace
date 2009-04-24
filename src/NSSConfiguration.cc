/**
 * NSSConfiguration.cc
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

#include "NSSConfiguration.hh"
#include "NSSService.hh"

#include <sstream>
#include <iostream>

using namespace SystemConfiguration;

NSSConfiguration::NSSConfiguration(void)
{
}

NSSConfiguration::~NSSConfiguration(void)
{
}

std::deque< NSSService > &
NSSConfiguration::operator[](const NSSDatabase database)
{
   if (_configuration.find(database) == _configuration.end())
      _configuration[database] = std::deque< NSSService >();
   return _configuration[database];
}

std::ostream &
SystemConfiguration::operator<<(std::ostream & os, const NSSConfiguration & configuration)
{
   std::map< NSSDatabase, std::deque< NSSService > >::const_iterator iter;
   std::deque< NSSService >::const_iterator service;

   for (iter = configuration._configuration.begin(); iter != configuration._configuration.end(); ++iter) {
      os << std::string(iter->first) << ":";
      for (service = iter->second.begin(); service != iter->second.end(); ++service)
         os << " " << *service;
      os << std::endl;
   }
}

std::istream &
SystemConfiguration::operator>>(std::istream & is, NSSConfiguration & configuration)
{
   std::string buffer;

   while (is) {
      NSSDatabase database;

      /* skip comments */
      if (is.peek() == '#') {
         std::getline(is, buffer);
         continue;
      }

      /* skip whitespace */
      while (::isspace(is.peek()))
         is.get();

      /* ensure we still have data */
      if (is.peek() == -1)
         break;

      std::getline(is, buffer);
      if (! buffer.empty()) {
         std::stringstream stream(buffer);
         std::string db;

         /* database: module [params] module */

         /* database */
         stream >> db;
         database = NSSDatabase(db.substr(0, db.length() - 1));

         /* lookup order */
         while (stream) {
            std::string entry;
            stream >> entry;

            /* module */
            if (! entry.empty()) {
               NSSService module(entry);

               /* module parameters */
               if (stream.tellg() < stream.str().length()) {
                  size_t pos(stream.tellg());

                  if (buffer.at(pos + 1) == '[') {
                     /* pos + 2 for the space and [, pos - 2 for [ and ] */
                     std::stringstream parameters(buffer.substr(pos + 2, buffer.find_first_of(']', pos + 1) - pos - 2));

                     while (parameters) {
                        std::string parameter;
                        parameters >> parameter;

                        if (! parameter.empty())
                           module.parameters().push_back(parameter);
                     }

                     /* 3 for the space, [, and ] */
                     stream.seekg(pos + parameters.str().length() + 3);
                  }
               }

               configuration[database].push_back(module);
            }
         }
      }
   }
}

