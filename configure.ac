dnl vim: set sw=8 sts=8 ts=8 noet fdm=marker fmr={{{,}}} :

dnl {{{ program, version
AC_PREREQ(2.59)
AC_INIT(libace, 0.0, compnerd@compnerd.org)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
dnl }}}

dnl {{{ basic toolchain checks
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET
dnl }}}

dnl {{{ output
AM_CONFIG_HEADER(config/config.h)
AC_OUTPUT(
	  Makefile
	  src/Makefile
	 )
dnl }}}

dnl {{{ summary
echo
echo "Prefix                 : $prefix"
echo
dnl }}}

