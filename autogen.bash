#!/bin/bash
# Copyright 2007-2010 Saleem Abdulrasool <compnerd@compnerd.org>

: ${AUTOCONF:=autoconf}
: ${AUTOMAKE:=automake}
: ${ACLOCAL:=aclocal}
: ${LIBTOOLIZE:=libtoolize}
: ${INTLTOOLIZE:=intltoolize}
: ${LIBTOOL:=libtool}

run()
{
   echo ">>> ${@}" 1>&2
   if ! ${@} ; then
      echo "failed to configure autotools" 1>&2
      exit 127
   fi
}

srcdir=$(dirname "${0}")
[[ -z "${srcdir}" ]] && srcdir="."

grep -q "^AC_PROG_INTLTOOL" "${srcdir}/configure.ac" && {
   ( "${INTLTOOLIZE}" --version ) < /dev/null > /dev/null 2>&1 || {
      echo
      echo "You must have intltoolize installed to compile ${PROJECT}."
      echo "Get ftp://ftp.gnome.org/pub/GNOME/stable/sources/intltool/intltool-0.40.tar.gz"
      echo "(or a newer version if it is available)"
      echo

      DIE=1
   }
}

grep -q "^AC_PROG_LIBTOOL" "${srcdir}/configure.ac" && {
   ( "${LIBTOOL}" --version ) < /dev/null > /dev/null 2>&1 || {
      echo
      echo "You must have libtool installed to compile ${PROJECT}."
      echo "Download the appropriate package for your distribution,"
      echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
      echo

      DIE=1
   }
}

( "${AUTOCONF}" --version ) < /dev/null > /dev/null 2>&1 || {
   echo
   echo "You must have autoconf installed to compile ${PROJECT}."
   echo "Download the appropriate package for your distribution,"
   echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
   echo

   DIE=1
}

( "${AUTOMAKE}" --version ) < /dev/null > /dev/null 2>&1 || {
   echo
   echo "You must have automake installed to compile ${PROJECT}."
   echo "Download the appropriate package for your distribution,"
   echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
   echo

   DIE=1
}

if [[ ${DIE} == 1 ]] ; then
   exit 127
fi

run mkdir -p "${srcdir}/config"

if grep -q "^AC_PROG_LIBTOOL" "${srcdir}/configure.ac" ; then
   run "${LIBTOOLIZE}" --copy --force --automake
fi

rm -f config.cache
run "${ACLOCAL}" --force
run "${AUTOCONF}" --force
run "${AUTOMAKE}" --add-missing --copy --force-missing --foreign

