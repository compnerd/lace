/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * PAMEntry.hh
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

#ifndef __PAM_ENTRY_HH__
#define __PAM_ENTRY_HH__

#include <list>
#include <string>
#include <iostream>

#include "PAMControl.hh"

namespace SystemConfiguration
{
   class PAMEntry
   {
      friend std::ostream& operator<<(std::ostream&, const PAMEntry&);
      friend std::istream& operator>>(std::istream&, PAMEntry&);

      private:
         PAMControl _control;
         std::string _module;
         std::list< std::string > _parameters;

      public:
         PAMEntry(void);
         PAMEntry(PAMControl control, std::string module);
         ~PAMEntry(void);

         PAMEntry& operator=(const PAMEntry& other);

         const std::string& module(void) const;
         std::list< std::string >& parameters(void);
   };

   std::ostream&
   operator<<(std::ostream& os, const PAMEntry& entry);

   std::istream&
   operator>>(std::istream& is, PAMEntry& entry);
};

#endif

