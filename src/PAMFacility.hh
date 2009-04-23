/**
 * PAMFacility.hh
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

#ifndef __PAM_FACILITY_HH__
#define __PAM_FACILITY_HH__

#include <string>
#include <exception>

namespace SystemConfiguration
{
   class InvalidFacilityException
      : public std::exception
   {
      private:
         std::string _message;

      public:
         InvalidFacilityException(const std::string & message);
         virtual ~InvalidFacilityException(void) throw ();

         const char *what(void) const throw ();
   };

   class PAMFacility
   {
      friend std::ostream& operator<<(std::ostream& os, const PAMFacility& facility);
      friend std::istream& operator>>(std::istream& is, PAMFacility& facility);

      public:
         enum Facility
         {
            Invalid,
            Account,
            Authorization,
            Password,
            Session,
         };

      private:
         Facility _facility;

      public:
         PAMFacility(void);
         PAMFacility(const Facility facility);
         PAMFacility(const PAMFacility& facility);
         PAMFacility(const std::string& facility);

         ~PAMFacility(void);

         bool operator==(const PAMFacility& other);
         bool operator==(const std::string& other);

         PAMFacility& operator=(const Facility facility);
         PAMFacility& operator=(const std::string& facility);

         operator std::string(void) const;
         operator Facility(void) const;
   };

   std::ostream&
   operator<<(std::ostream& os, const PAMFacility& facility);

   std::istream&
   operator>>(std::istream& is, PAMFacility& facility);
};

#endif
