/**
 * PAMStack.hh
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
