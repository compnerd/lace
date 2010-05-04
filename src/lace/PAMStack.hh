/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * PAMStack.hh
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

#ifndef __PAM_STACK_HH__
#define __PAM_STACK_HH__

#include <deque>
#include <string>
#include <iterator>

#include "PAMEntry.hh"
#include "PAMFacility.hh"

namespace SystemConfiguration
{
   class PAMStack
      : public std::deque< PAMEntry >
   {
      friend std::ostream& operator<<(std::ostream&, const PAMStack&);

      private:
         PAMFacility _Facility;

      public:
         PAMStack(void);
         PAMStack(const PAMStack& stack);
         PAMStack(const PAMFacility& facility);

         ~PAMStack(void);

         PAMStack& operator=(const PAMStack& stack);

         const PAMFacility& Facility(void) const;

         iterator find(const std::string& module);
         const_iterator find(const std::string& module) const;
   };

   std::ostream&
   operator<<(std::ostream& os, const PAMStack& stack);
};

#endif
