/**
 * PAMFacility.cc
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

