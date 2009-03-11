/**
 * PAMFacility.cc
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

#include "PAMFacility.hh"

using namespace SystemConfiguration;

#define N_ELEMENTS(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef struct _FacilityMapEntry
{
   const PAMFacility::Facility facility;
   const std::string string;
} FacilityMapEntry;

static const FacilityMapEntry _facility_map[] =
{
   { PAMFacility::Authorization, "auth" },
   { PAMFacility::Account, "account" },
   { PAMFacility::Password, "password" },
   { PAMFacility::Session, "session" },
};

static PAMFacility::Facility
facility_from_string(const std::string& facility)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_facility_map); i++)
      if (_facility_map[i].string == facility)
         return _facility_map[i].facility;
   /* TODO implement exception */
   throw;
}

static std::string
string_from_facility(const PAMFacility::Facility facility)
{
   for (unsigned int i = 0; i < N_ELEMENTS(_facility_map); i++)
      if (_facility_map[i].facility == facility)
         return _facility_map[i].string;
   /* TODO implement exception */
   throw;
}

PAMFacility::PAMFacility(void)
   : _facility(Invalid)
{
}

PAMFacility::PAMFacility(const Facility facility)
   : _facility(facility)
{
}

PAMFacility::PAMFacility(const PAMFacility& facility)
   : _facility(facility._facility)
{
}

PAMFacility::PAMFacility(const std::string& facility)
   : _facility(facility_from_string(facility))
{
}

PAMFacility::~PAMFacility(void)
{
}

bool
PAMFacility::operator==(const PAMFacility& other)
{
   return _facility == other._facility;
}

bool
PAMFacility::operator==(const std::string& other)
{
   return _facility == facility_from_string(other);
}

PAMFacility&
PAMFacility::operator=(const Facility facility)
{
   _facility = _facility;
   return *this;
}

PAMFacility&
PAMFacility::operator=(const std::string& facility)
{
   _facility = facility_from_string(facility);
   return *this;
}

PAMFacility::operator std::string(void) const
{
   return string_from_facility(_facility);
}

PAMFacility::operator Facility(void) const
{
   return _facility;
}

std::ostream&
SystemConfiguration::operator<<(std::ostream& os, const PAMFacility& facility)
{
   os << std::string(facility);
   return os;
}

std::istream&
SystemConfiguration::operator>>(std::istream& is, PAMFacility& facility)
{
   std::string buffer;

   is >> buffer;
   facility = buffer;

   return is;
}

/* vim: set sw=3 sts=3 ts=3 et : */

