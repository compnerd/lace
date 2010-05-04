# vim: set sw=4 ts=8 :

AM_CPPFLAGS = -I $(top_srcdir)/src

lib_LTLIBRARIES = src/lace/libace.la

src_libace_la_SOURCES = src/lace/NSSConfiguration.cc    \
			src/lace/NSSConfiguration.hh    \
			src/lace/NSSDatabase.cc         \
			src/lace/NSSDatabase.hh         \
			src/lace/NSSService.cc          \
			src/lace/NSSService.hh          \
			src/lace/PAMControl.cc          \
			src/lace/PAMControl.hh          \
			src/lace/PAMEntry.cc            \
			src/lace/PAMEntry.hh            \
			src/lace/PAMFacility.cc         \
			src/lace/PAMFacility.hh         \
			src/lace/PAMPolicy.cc           \
			src/lace/PAMPolicy.hh           \
			src/lace/PAMStack.cc            \
			src/lace/PAMStack.hh            \
			$(NULL)

MAINTAINERCLEANFILES = aclocal.m4 Makefile.in

