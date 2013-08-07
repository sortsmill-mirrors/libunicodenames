#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#  Copyright (C) 2012, 2013 Khaled Hosny and Barry Schwartz
# 
#  This file is part of LibUnicodeNames.
#  
#  LibUnicodeNames is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation, either version 3 of
#  the License, or (at your option) any later version.
#  
#  LibUnicodeNames is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with LibUnicodeNames.  If not, see
#  <http://www.gnu.org/licenses/>.

#--------------------------------------------------------------------------

AC_PREREQ([2.68])
AC_INIT([LibUnicodeNames],
        [1.2.0_beta1],
        [http://bitbucket.org/sortsmill/libunicodenames/issues],
        [libunicodenames],
        [http://bitbucket.org/sortsmill/libunicodenames])

AC_CONFIG_SRCDIR([make-names-db.in])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])        dnl Where things like install-sh go.
AC_CANONICAL_BUILD                 dnl On what platform are we compiling?
AC_CANONICAL_HOST                  dnl For what platform are we compiling?
AC_USE_SYSTEM_EXTENSIONS           dnl Define such macros as _GNU_SOURCE.
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 dist-xz -Wall -Wno-portability])
AM_SILENT_RULES([yes])
AX_CHECK_GNU_MAKE
m4_ifdef([AM_PROG_AR],[AM_PROG_AR])
LT_INIT
AM_GNU_GETTEXT_VERSION([0.18.1])

AC_CONFIG_TESTDIR([tests])

StM_ANALYZE_PACKAGE_VERSION

AC_ARG_VAR([NAMESLIST_EN_URL],[URL for the Unicode names list in English
(default `http://www.unicode.org/Public/UNIDATA/NamesList.txt')])
AC_ARG_VAR([NAMESLIST_FR_URL],[URL for the Unicode names list in French
(default `http://hapax.qc.ca/ListeDesNoms-5.0.0.txt')])
test -z "${NAMESLIST_EN_URL}" && NAMESLIST_EN_URL="http://www.unicode.org/Public/UNIDATA/NamesList.txt"
test -z "${NAMESLIST_FR_URL}" && NAMESLIST_FR_URL="http://hapax.qc.ca/ListeDesNoms-5.0.0.txt"

AC_ARG_ENABLE([make-libunicodenames-db],
        [AS_HELP_STRING([--disable-make-libunicodenames-db],
                [do not install make-libunicodenames-db])])
test -z "${enable_make_libunicodenames_db}" && enable_make_libunicodenames_db=yes

AC_ARG_ENABLE([nameslist-install],
        [AS_HELP_STRING([--enable-nameslist-install],
                [install NamesList.UTF-8 and ListeDesNoms.UTF-8
                 for use in the testsuites of libunicodenames wrappers,
                 such as libunicodenames++])])

#--------------------------------------------------------------------------
#
# Checks for programs.

AC_PROG_CC
AC_PROG_CC_C99
gl_EARLY
gl_INIT
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_YACC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_SED
StM_PROG_GAWK
StM_PROG_GNU_INDENT
StM_PROG_WGET

StM_PROG_HELP2MAN
AM_CONDITIONAL([HAVE_HELP2MAN],[test x"${HELP2MAN}" != x])

if test -z "${GAWK}" -a x"${enable_make_libunicodenames_db}" = xyes; then
   AC_MSG_ERROR([gawk not found. Please install it or run configure again with --disable-make-libunicodenames-db
           Gawk website: http://www.gnu.org/software/gawk/])
fi

if test -z "${WGET}" -a x"${enable_make_libunicodenames_db}" = xyes; then
   AC_MSG_ERROR([wget not found. Please install it or run configure again with --disable-make-libunicodenames-db
           Wget website: http://www.gnu.org/software/wget/])
fi

test -z "${GAWK}" && GAWK=/bin/false
test -z "${GNU_INDENT}" && GNU_INDENT=/bin/false
test -z "${WGET}" && WGET=/bin/false

#--------------------------------------------------------------------------
#
# Checks for libraries.


#--------------------------------------------------------------------------
#
# Checks for header files.

AC_CHECK_HEADERS([argz.h fcntl.h float.h inttypes.h langinfo.h libintl.h limits.h locale.h malloc.h stddef.h stdint.h stdio_ext.h stdlib.h string.h sys/param.h unistd.h wchar.h])
AC_HEADER_STDBOOL
AC_FUNC_ALLOCA

#--------------------------------------------------------------------------
#
# Checks for typedefs, structures, and compiler characteristics.

AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

AC_SUBST([WARNING_CFLAGS],[])
StM_GNU_C_FLAGS([WARNING_CFLAGS],
   [-Wall -Wextra -Wcast-align -Wbad-function-cast -Wc++-compat
    -Wno-unused-result],
   [-Wl,--warn-common])

StM_DEFINE_ATTR_VISIBLE([VISIBLE])

#--------------------------------------------------------------------------
#
# Checks for library functions.

AC_FUNC_MALLOC
AM_GNU_GETTEXT([external])
AC_FUNC_MBRTOWC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify floor getcwd localeconv mblen mbrlen memchr mempcpy memset munmap nl_langinfo setlocale stpcpy strcasecmp strchr strcspn strdup strstr strtoul])

#--------------------------------------------------------------------------

AC_SUBST([LT_OBJDIR],["${lt_cv_objdir}"])

AM_CONDITIONAL([MAKE_LIBUNICODENAMES_DB_INSTALL],
               [test x"${enable_make_libunicodenames_db}" = xyes])
AM_CONDITIONAL([NAMESLIST_INSTALL],
               [test x"${enable_nameslist_install}" = xyes])

StM_CHANGELOGGERIZE

StM_CONFIG_MAKEFILES
StM_CONFIG_MAKEFILES([tests/Makefile],[tests/GNUmakefile])

AC_CONFIG_FILES([libunicodenames.pc])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([tests/atlocal])

AC_CONFIG_FILES([make-names-db],[chmod +x make-names-db])
AC_CONFIG_FILES([make-blocks-db],[chmod +x make-blocks-db])
AC_CONFIG_FILES([make-libunicodenames-db.in])

AC_CONFIG_COMMANDS([.indent.pro],[
   if test "${ac_srcdir}" -ef "${ac_builddir}"; then
      :
   else
      for dir in . tests; do
          rm -f "${ac_builddir}/${dir}/.indent.pro"
          (cd "${ac_builddir}/${dir}" && ${LN_S} "${ac_srcdir}"/.indent.pro .indent.pro)
      done
   fi
])

AC_OUTPUT

#--------------------------------------------------------------------------
