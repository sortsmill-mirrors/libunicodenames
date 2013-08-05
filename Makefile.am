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

ACLOCAL_AMFLAGS = -I m4 -I m4_ax --install

SUBDIRS = lib . po tests

#--------------------------------------------------------------------------

NAMESLIST_EN = "http://www.unicode.org/Public/UNIDATA/NamesList.txt"
NAMESLIST_FR = "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt"

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA =

dist_pkgdata_DATA =
nodist_pkgdata_DATA =

lib_LTLIBRARIES =
include_HEADERS =

AM_CPPFLAGS = 											\
	-I$(top_builddir)/lib -I$(top_srcdir)/lib			\
	-DPKGDATADIR=\"${pkgdatadir}/\"	 					\
	-DLOCALEDIR=\"${localedir}/\" 						\
	-DTEXTDOMAIN=\"${PACKAGE}\"

AM_CFLAGS = $(WARNING_CFLAGS) $(CFLAG_VISIBILITY)
AM_LDFLAGS = $(LTLIBINTL)

#--------------------------------------------------------------------------

nodist_pkgconfig_DATA += libunicodenames.pc

if NAMESLIST_INSTALL
nodist_pkgdata_DATA += NamesList.UTF-8 ListeDesNoms.UTF-8
endif NAMESLIST_INSTALL

lib_LTLIBRARIES += libunicodenames.la
include_HEADERS += libunicodenames.h
dist_pkgdata_DATA += en.names-db fr.names-db en.blocks-db fr.blocks-db
info_TEXINFOS = libunicodenames.texi

libunicodenames_la_SOURCES = use_names_db.c use_blocks_db.c find_db.c	\
	common_code.c noinst_header.h libgettext.h
nodist_libunicodenames_la_SOURCES = config.h
libunicodenames_la_LDFLAGS = -version-info 1:2:0 $(AM_LDFLAGS)

#--------------------------------------------------------------------------

EXTRA_DIST = $(srcdir)/po/Rules-doc m4/gnulib-cache.m4 .indent.pro

#--------------------------------------------------------------------------

extract_text = $(GAWK) ' \
BEGIN { pattern = "^[[:space:]]*(//|*)[[:space:]]*$1--[[:space:]]*(.*)[[:space:]]*" } \
$$0 ~ pattern { match($$0, pattern, matches); print matches[2] }'

$(srcdir)/%.type.texi: %.h
	$(call extract_text,t) $< > $@

$(srcdir)/%.func.texi: %.h
	$(call extract_text,f) $< > $@

extract-text: extract-libunicodenames-text

extract-libunicodenames-text: $(LIBUNICODENAMES_H_TEXI)

LIBUNICODENAMES_H_TEXI = $(srcdir)/libunicodenames.type.texi	\
	$(srcdir)/libunicodenames.func.texi

EXTRA_DIST += $(LIBUNICODENAMES_H_TEXI)

$(srcdir)/README: $(srcdir)/libunicodenames.texi $(LIBUNICODENAMES_H_TEXI)
	$(MAKEINFO) --plaintext --no-split $< > $@

#--------------------------------------------------------------------------

dist_noinst_SCRIPTS = make-names-db.awk make-blocks-db.awk

MAKE_NAMES_DB = LC_ALL=C $(GAWK) -f $(srcdir)/make-names-db.awk
MAKE_BLOCKS_DB = LC_ALL=C $(GAWK) -f $(srcdir)/make-blocks-db.awk

nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt
nodist_EXTRA_DATA += NamesList.UTF-8 ListeDesNoms.UTF-8

rebuild-db: rebuild-names-db rebuild-blocks-db

rebuild-names-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_NAMES_DB) NamesList.UTF-8 > $(srcdir)/en.names-db
	$(MAKE_NAMES_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.names-db

rebuild-blocks-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_BLOCKS_DB) NamesList.UTF-8 > $(srcdir)/en.blocks-db
	$(MAKE_BLOCKS_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.blocks-db

CRLF_TO_LF = $(SED) -e 's/\r//g'

NamesList.UTF-8: NamesList.txt
	$(CRLF_TO_LF) < $< > $@

ListeDesNoms.UTF-8: ListeDesNoms.txt
	$(CRLF_TO_LF) < $< > $@

NamesList.txt:
	$(WGET) $(NAMESLIST_EN) -O $@

ListeDesNoms.txt:
	$(WGET) $(NAMESLIST_FR) -O $@

#--------------------------------------------------------------------------
#
# Use Mercurial to make a ChangeLog automatically.

dist-hook: make-changelog

make-changelog:
	@if hg log -r tip > /dev/null 2> /dev/null; then \
		hg log --style=changelog > $(distdir)/ChangeLog; \
		echo; \
		echo "----------------------------------------------------------------"; \
		echo "hg log --style=changelog > $(distdir)/ChangeLog"; \
		echo "----------------------------------------------------------------"; \
		echo; \
	else \
		echo "If you do not mind, please report that the ChangeLog is missing." > $(distdir)/ChangeLog; \
		echo "Report at: https://bitbucket.org/sortsmill/libunicodenames/issues" >> $(distdir)/ChangeLog; \
		echo; \
		echo "----------------------------------------------------------------"; \
		echo "The ChangeLog was not made! You need Mercurial to make it."; \
		echo "If you are making a real release, please do it from within"; \
		echo "a Mercurial repository. Consider using Mercurial with hg-git."; \
		echo "----------------------------------------------------------------"; \
		echo; \
	fi

#--------------------------------------------------------------------------

DISTCLEANFILES = NamesList.txt ListeDesNoms.txt
DISTCLEANFILES += NamesList.UTF-8 ListeDesNoms.UTF-8

distclean-local:
	if test '$(top_srcdir)' -ef '$(top_builddir)'; then		\
		:; 													\
	else													\
		for dir in . tests; do								\
             rm -f "$(top_builddir)/$${dir}/.indent.pro";	\
		done;												\
	fi

#--------------------------------------------------------------------------

include indent.mk

blacklist_for_indent += config.h libgettext.h

indent: indent-recursive
	$(call do_indent, $(libunicodenames_la_SOURCES))
	$(call do_indent, $(include_HEADERS))

indent-recursive:
	$(MAKE) -C tests $(AM_MAKEFLAGS) indent

#--------------------------------------------------------------------------
