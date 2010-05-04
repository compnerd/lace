/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * NSSService.cc
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

#include "NSSService.hh"

#include <sstream>

using namespace SystemConfiguration;

NSSService::NSSService(void)
   : _module("")
{
}

NSSService::NSSService(const std::string & module)
   : _module(module)
{
}

NSSService::~NSSService(void)
{
}

const std::string &
NSSService::module(void) const
{
   return _module;
}

std::list< std::string > &
NSSService::parameters(void)
{
   return _parameters;
}

std::ostream &
SystemConfiguration::operator<<(std::ostream & os, const NSSService & service)
{
   std::list< std::string >::const_iterator parameter;

   os << service._module;
   if (! service._parameters.empty()) {
      os << std::string(" [");
      for (parameter = service._parameters.begin(); parameter != service._parameters.end();) {
         os << *parameter;
         if (++parameter != service._parameters.end())
            os << std::string(" ");
      }
      os << std::string("]");
   }

   return os;
}

