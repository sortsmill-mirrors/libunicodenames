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

ACLOCAL_AMFLAGS = -I m4 --install

SUBDIRS = lib . po tests

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA =

dist_pkgdata_DATA =
nodist_pkgdata_DATA =
lib_LTLIBRARIES =
include_HEADERS =
nodist_bin_SCRIPTS =
dist_noinst_SCRIPTS =
nodist_libexec_SCRIPTS =
nodist_EXTRA_DATA =
dist_man_MANS =
nodist_man_MANS =
EXTRA_DIST =
MOSTLYCLEANFILES =
CLEANFILES =
DISTCLEANFILES = Makefile
make_libunicodenames_db_reference =

AM_CPPFLAGS = 											\
	-I$(top_builddir)/lib -I$(top_srcdir)/lib			\
	-DPKGDATADIR=\"${pkgdatadir}/\"	 					\
	-DLOCALEDIR=\"${localedir}/\" 						\
	-DTEXTDOMAIN=\"${PACKAGE}\"
AM_CFLAGS = $(WARNING_CFLAGS) $(CFLAG_VISIBILITY)
AM_LDFLAGS = $(LTLIBINTL)

EXTRA_DIST += INSTALL.C++ examples/print_names.c	\
	examples/print_blocks.c

#--------------------------------------------------------------------------

nodist_pkgconfig_DATA += libunicodenames.pc

lib_LTLIBRARIES += libunicodenames.la
include_HEADERS += libunicodenames.h
dist_pkgdata_DATA += en.names-db fr.names-db en.blocks-db fr.blocks-db

libunicodenames_la_SOURCES = use_names_db.c use_blocks_db.c find_db.c	\
	common_code.c noinst_header.h libgettext.h
nodist_libunicodenames_la_SOURCES = config.h
libunicodenames_la_LDFLAGS = -version-info 1:3:0 $(AM_LDFLAGS)

nodist_man_MANS += doc/uninm_find_names_db.3
dist_man_MANS += doc/uninm_names_db_open.3
dist_man_MANS += doc/uninm_names_db_close.3
dist_man_MANS += doc/uninm_name.3
dist_man_MANS += doc/uninm_annotation.3

nodist_man_MANS += doc/uninm_find_blocks_db.3
dist_man_MANS += doc/uninm_blocks_db_open.3
dist_man_MANS += doc/uninm_blocks_db_close.3
dist_man_MANS += doc/uninm_num_blocks.3
dist_man_MANS += doc/uninm_block_start.3
dist_man_MANS += doc/uninm_block_end.3
dist_man_MANS += doc/uninm_block_name.3

%.3: %.3.in Makefile GNUmakefile
	$(SED) -e 's|%%pkgdatadir%%|$(pkgdatadir)|g' \
	       -e 's|%%make_libunicodenames_db_reference%%|$(make_libunicodenames_db_reference)|g' \
	       $< > $@-tmp
	mv $@-tmp $@

EXTRA_DIST += doc/uninm_find_names_db.3.in		\
	doc/uninm_find_blocks_db.3.in
MOSTLYCLEANFILES += doc/uninm_find_names_db.3 doc/uninm_find_blocks_db.3

#--------------------------------------------------------------------------

EXTRA_DIST += $(srcdir)/po/Rules-doc m4/gnulib-cache.m4 .indent.pro

#--------------------------------------------------------------------------

NAMESLISTS = NamesList.UTF-8 ListeDesNoms.UTF-8

nodist_libexec_SCRIPTS += make-names-db make-blocks-db
MOSTLYCLEANFILES += $(nodist_libexec_SCRIPTS)

if NAMESLIST_INSTALL
nodist_pkgdata_DATA += $(NAMESLISTS)
else !NAMESLIST_INSTALL
nodist_EXTRA_DATA += $(NAMESLISTS)
endif !NAMESLIST_INSTALL

if MAKE_LIBUNICODENAMES_DB_INSTALL #--------------

nodist_bin_SCRIPTS += make-libunicodenames-db
MOSTLYCLEANFILES += make-libunicodenames-db

make-libunicodenames-db: make-libunicodenames-db.in Makefile GNUmakefile
	$(SED) -e 's|%%libexecdir%%|$(libexecdir)|g' make-libunicodenames-db.in > $@-tmp
	mv $@-tmp $@
	chmod +x $@

if HAVE_HELP2MAN

nodist_man_MANS += make-libunicodenames-db.1
CLEANFILES += make-libunicodenames-db.1

# A reference for inclusion in the ‘SEE ALSO’ sections of mdoc
# manpages.
make_libunicodenames_db_reference += ,\n.Xr make-libunicodenames-db 1

MY_HELP2MAN = $(HELP2MAN) --no-info --output=$@				\
				--help-option='-h' --version-option='-V'	\
				--source='Sorts Mill'

make-libunicodenames-db.1: make-libunicodenames-db make-libunicodenames-db.h2m
	$(MY_HELP2MAN) --name='make-libunicodenames-db'			\
		--include='$(srcdir)/make-libunicodenames-db.h2m'	\
		./make-libunicodenames-db

EXTRA_DIST += make-libunicodenames-db.h2m

endif HAVE_HELP2MAN

endif MAKE_LIBUNICODENAMES_DB_INSTALL #-----------

MAKE_NAMES_DB = LC_ALL=C $(GAWK) -f make-names-db
MAKE_BLOCKS_DB = LC_ALL=C $(GAWK) -f make-blocks-db
CRLF_TO_LF = LC_ALL=C $(SED) -e 's/\r//g'

NamesList.UTF-8:
	$(WGET) $(NAMESLIST_EN_URL) -O - | $(CRLF_TO_LF) > $@

ListeDesNoms.UTF-8:
	$(WGET) $(NAMESLIST_FR_URL) -O - | $(CRLF_TO_LF) > $@

DISTCLEANFILES += NamesList.UTF-8 ListeDesNoms.UTF-8

# A target for package maintainers.
rebuild-db: rebuild-names-db rebuild-blocks-db

# A target for package maintainers.
rebuild-names-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_NAMES_DB) NamesList.UTF-8 > $(srcdir)/en.names-db
	$(MAKE_NAMES_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.names-db

# A target for package maintainers.
rebuild-blocks-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_BLOCKS_DB) NamesList.UTF-8 > $(srcdir)/en.blocks-db
	$(MAKE_BLOCKS_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.blocks-db

.PHONY: rebuild-db rebuild-names-db rebuild-blocks-db

#--------------------------------------------------------------------------

distclean-local:
	if test '$(top_srcdir)' -ef '$(top_builddir)'; then		\
		:; 													\
	else													\
		for dir in . tests; do								\
             rm -f "$(top_builddir)/$${dir}/.indent.pro";	\
		done;												\
	fi

#--------------------------------------------------------------------------
#
# Automatic ChangeLog generation at `make dist', if one has
# sortsmill-changelogger.

dist-hook: dist-changelog
@dist_changelog_rules@

#--------------------------------------------------------------------------

include indent.am

blacklist_for_indent += config.h libgettext.h

@ifGNUmake@indent: indent-recursive
@ifGNUmake@	$(call do_indent, $(libunicodenames_la_SOURCES))
@ifGNUmake@	$(call do_indent, $(include_HEADERS))
@ifGNUmake@
@ifGNUmake@indent-recursive:
@ifGNUmake@	$(MAKE) -C tests $(AM_MAKEFLAGS) indent

#--------------------------------------------------------------------------
