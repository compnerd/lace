/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
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

static std::string
trim(const std::string & str)
{
   size_t start(0), end(str.length());

   for (; start < str.length(); start++)
      if (! ::isspace(str[start]))
         break;

   for (; end > 0; end--)
      if (! ::isspace(str[end]))
         break;

   return str.substr(start, end);
}

std::istream &
SystemConfiguration::operator>>(std::istream & is, NSSConfiguration & configuration)
{
   std::string buffer;

   while (is) {
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
         NSSDatabase database;
         NSSService service;
         size_t pos(0);

         pos = buffer.find_first_of(':', pos);
         database = NSSDatabase(trim(buffer.substr(0, pos)));

         while (pos < buffer.length()) {
            size_t start(pos + 1), end;

            for (; start < buffer.length(); start++)
               if (! ::isspace(buffer[start]))
                  break;

            for (end = start + 1; end < buffer.length(); end++)
               if (::isspace(buffer[end]))
                  break;

            if (end - start == 0)
               break;

            service = NSSService(buffer.substr(start, end - start));

            pos = end;

            for (start = end; start < buffer.length(); start++)
               if (! ::isspace(buffer[start]))
                  break;

            if (buffer[start] != '[') {
               /* no module parameters */
               configuration[database].push_back(service);
               continue;
            }

            pos = end = buffer.find_first_of(']', start);
            if (end != std::string::npos && start - end > 0) {
               std::stringstream parameters(trim(buffer.substr(start + 1, end - start - 1)));

               while (parameters) {
                  std::string parameter;
                  parameters >> parameter;

                  if (! parameter.empty())
                     service.parameters().push_back(parameter);
               }
            }

            configuration[database].push_back(service);
         }
      }
   }
}

