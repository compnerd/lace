/**
 * PAMControl.cc
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

#include "PAMControl.hh"

using namespace SystemConfiguration;

#define N_ELEMENTS(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef struct _ControlMapEntry
{
   const PAMControl::Control control;
   const std::string string;
} ControlMapEntry;

static const ControlMapEntry _control_map[] =
{
   { PAMControl::Required, "required" },
   { PAMControl::Requisite, "requisite" },
   { PAMControl::Sufficient, "sufficient" },
   { PAMControl::Optional, "optional" },
   { PAMControl::Include, "include" },
   { PAMControl::Substack, "substack" },
};

static PAMControl::Control
control_from_string(const std::string& control)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_control_map); i++)
      if (_control_map[i].string == control)
         return _control_map[i].control;
   /* TODO implement exception */
   throw;
}

static std::string
string_from_control(const PAMControl::Control control)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_control_map); i++)
      if (_control_map[i].control == control)
         return _control_map[i].string;
   /* TODO implement exception */
   throw;
}

PAMControl::PAMControl(void)
{
}

PAMControl::PAMControl(const Control control)
   : _control(control)
{
}

PAMControl::PAMControl(const PAMControl& control)
   : _control(control._control)
{
}

PAMControl::PAMControl(const std::string& control)
   : _control(control_from_string(control))
{
}

PAMControl::~PAMControl(void)
{
}

PAMControl&
PAMControl::operator=(const Control control)
{
   _control = control;
   return *this;
}

PAMControl&
PAMControl::operator=(const std::string& control)
{
   _control = control_from_string(control);
   return *this;
}

bool
PAMControl::operator==(const PAMControl& other)
{
   return _control == other._control;
}

bool
PAMControl::operator==(const std::string& other)
{
   return _control == control_from_string(other);
}

PAMControl::operator std::string(void) const
{
   return string_from_control(_control);
}

PAMControl::operator Control(void) const
{
   return _control;
}

/* vim: set sw=3 sts=3 ts=3 et : */

