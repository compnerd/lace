/**
 * PAMStack.cc
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

