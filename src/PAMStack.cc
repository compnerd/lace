/**
 * PAMStack.cc
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

#include "PAMStack.hh"

using namespace SystemConfiguration;

PAMStack::PAMStack(void)
{
}

PAMStack::PAMStack(const PAMStack& stack)
   : std::deque< PAMEntry >(stack), _Facility(stack._Facility)
{
}

PAMStack::PAMStack(const PAMFacility& facility)
   : _Facility(facility)
{
}

PAMStack::~PAMStack(void)
{
}

PAMStack&
PAMStack::operator=(const PAMStack& stack)
{
   std::deque< PAMEntry >::operator=(stack);
   _Facility = stack._Facility;

   return *this;
}

const PAMFacility&
PAMStack::Facility(void) const
{
   return _Facility;
}

PAMStack::iterator
PAMStack::find(const std::string& module)
{
   PAMStack::iterator iter;

   for (iter = begin(); iter != end(); ++iter)
      if (iter->module() == module)
         return iter;

   return end();
}

PAMStack::const_iterator
PAMStack::find(const std::string& module) const
{
   PAMStack::const_iterator iter;

   for (iter = begin(); iter != end(); ++iter)
      if (iter->module() == module)
         return iter;

   return end();
}

std::ostream&
SystemConfiguration::operator<<(std::ostream& os, const PAMStack& stack)
{
   PAMStack::const_iterator iter;

   for (iter = stack.begin(); iter != stack.end(); ++iter)
      os << std::string(stack._Facility) << "\t" << *iter << std::endl;

   return os;
}

/* vim: set sw=3 sts=3 ts=3 et : */

