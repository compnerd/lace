/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * PAMPolicy.cc
 * Copyright 2007-2008 Saleem Abdulrasool <compnerd@compnerd.org>
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

#include "PAMPolicy.hh"

#include <sstream>

using namespace SystemConfiguration;

PAMPolicy::PAMPolicy(const std::string& name)
   : _Name(name)
{
}

PAMPolicy::~PAMPolicy(void)
{
}

PAMStack&
PAMPolicy::operator[](PAMFacility facility)
{
   if (_Policy.find(facility) == _Policy.end())
      _Policy[facility] = PAMStack(facility);
   return _Policy[facility];
}

std::ostream&
SystemConfiguration::operator<<(std::ostream& os, const PAMPolicy& policy)
{
   std::map< PAMFacility, PAMStack >::const_iterator iter;

   os << "#%PAM-1.0" << std::endl << std::endl;
   for (iter = policy._Policy.begin(); iter != policy._Policy.end(); ++iter)
      os << iter->second << std::endl;

   return os;
}

std::istream&
SystemConfiguration::operator>>(std::istream& is, PAMPolicy& policy)
{
   std::string buffer;

   while (is) {
      PAMStack stack;
      PAMFacility facility;
      PAMEntry entry;

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

      is >> facility;
      is >> entry;

      policy[facility].push_back(entry);
   }

   return is;
}

/* vim: set sw=3 sts=3 ts=3 et : */

