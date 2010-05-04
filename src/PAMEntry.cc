/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * PAMEntry.cc
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

#include "PAMEntry.hh"

#include <sstream>
#include <iterator>

using namespace SystemConfiguration;

PAMEntry::PAMEntry(void)
{
}

PAMEntry::PAMEntry(PAMControl control, std::string module)
   : _control(control), _module(module)
{
}

PAMEntry::~PAMEntry(void)
{
}

PAMEntry&
PAMEntry::operator=(const PAMEntry& other)
{
   _control = other._control;
   _module = other._module;
   return *this;
}

const std::string&
PAMEntry::module(void) const
{
   return _module;
}

std::list< std::string >&
PAMEntry::parameters(void)
{
   return _parameters;
}

std::ostream&
SystemConfiguration::operator<<(std::ostream& os, const PAMEntry& entry)
{
   os << std::string(entry._control) << "\t" << entry._module << "\t";
   std::copy(entry._parameters.begin(), entry._parameters.end(), std::ostream_iterator< std::string >(os, " "));
   return os;
}

std::istream&
SystemConfiguration::operator>>(std::istream& is, PAMEntry& entry)
{
   std::string buffer;

   is >> buffer;
   entry._control = PAMControl(buffer);

   is >> buffer;
   entry._module = buffer;

   std::getline(is, buffer);
   if (! buffer.empty()) {
      std::stringstream stream(buffer);
      while (stream) {
         std::string parameter;
         stream >> parameter;
         if (! parameter.empty())
            entry._parameters.push_back(parameter);
      }
   }

   return is;
}

/* vim: set sw=3 sts=3 ts=3 et : */

