/**
 * PAMControl.hh
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

#ifndef __PAM_CONTROL_HH__
#define __PAM_CONTROL_HH__

#include <string>

namespace SystemConfiguration
{
   class PAMControl
   {
      public:
         enum Control
         {
            Invalid,
            Required,
            Requisite,
            Sufficient,
            Optional,
            Include,
            Substack,
         };

      private:
         Control _control;

      public:
         PAMControl(void);
         PAMControl(const Control control);
         PAMControl(const PAMControl& control);
         PAMControl(const std::string& control);

         ~PAMControl(void);

         PAMControl& operator=(const Control control);
         PAMControl& operator=(const std::string& control);

         bool operator==(const PAMControl& other);
         bool operator==(const std::string& other);

         operator std::string(void) const;
         operator Control(void) const;
   };
};

#endif
