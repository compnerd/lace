/**
 * PAMPolicy.cc
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

