# vim: set sw=4 ts=8 :

AM_CPPFLAGS = -I $(top_srcdir)/src

lib_LTLIBRARIES = src/libace.la

src_libace_la_SOURCES = src/NSSConfiguration.cc \
			src/NSSConfiguration.hh \
			src/NSSDatabase.cc      \
			src/NSSDatabase.hh      \
			src/NSSService.cc       \
			src/NSSService.hh       \
			src/PAMControl.cc       \
			src/PAMControl.hh       \
			src/PAMEntry.cc         \
			src/PAMEntry.hh         \
			src/PAMFacility.cc      \
			src/PAMFacility.hh      \
			src/PAMPolicy.cc        \
			src/PAMPolicy.hh        \
			src/PAMStack.cc         \
			src/PAMStack.hh         \
			$(NULL)

MAINTAINERCLEANFILES = aclocal.m4 Makefile.in

