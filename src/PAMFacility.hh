/**
 * PAMFacility.hh
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

#ifndef __PAM_FACILITY_HH__
#define __PAM_FACILITY_HH__

#include <string>

namespace SystemConfiguration
{
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
