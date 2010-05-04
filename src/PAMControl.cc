/* vim: set et fdm=syntax sts=3 sw=3 ts=3 : */
/**
 * PAMControl.cc
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
   throw InvalidControlException("Invalid Control: " + control);
}

static std::string
string_from_control(const PAMControl::Control control)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_control_map); i++)
      if (_control_map[i].control == control)
         return _control_map[i].string;
   throw InvalidControlException("Invalid Control: " + control);
}

InvalidControlException::InvalidControlException(const std::string & message)
   : _message(message)
{
}

InvalidControlException::~InvalidControlException(void) throw ()
{
}

const char *
InvalidControlException::what(void) const throw ()
{
   return _message.c_str();
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

