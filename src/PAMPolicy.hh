/**
 * PAMPolicy.hh
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

#ifndef __PAM_POLICY_HH__
#define __PAM_POLICY_HH__

#include <map>
#include <string>

#include "PAMStack.hh"
#include "PAMFacility.hh"

namespace SystemConfiguration
{
   class PAMPolicy
   {
      friend std::ostream& operator<<(std::ostream&, const PAMPolicy&);
      friend std::istream& operator>>(std::istream&, PAMPolicy&);

      public:
         static const std::string PAMConfigurationDirectory;

      private:
         std::string _Name;
         std::map< PAMFacility, PAMStack > _Policy;

         PAMPolicy(void);

      public:
         PAMPolicy(const std::string& name);
         ~PAMPolicy(void);

         PAMStack& operator[](PAMFacility facility);
   };

   std::ostream&
   operator<<(std::ostream& os, const PAMPolicy& policy);

   std::istream&
   operator>>(std::istream& is, PAMPolicy& stack);
};

#endif

