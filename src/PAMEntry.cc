/**
 * PAMEntry.cc
 * Copyright 2007-2008 Saleem Abdulrasool <compnerd@compnerd.org>
 *
 * This file is part of the ace Library.  ace is free software; you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation.
 *
 * PC is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have recieved a copy of the GNU General Public License along with
 * PC; if not, write to the Free Software Foundation Inc., 59 Temple Place,
 * Suite 330, Boston, MA 02111-1307 USA
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

