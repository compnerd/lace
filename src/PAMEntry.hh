/**
 * PAMEntry.hh
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

