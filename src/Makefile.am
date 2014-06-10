###
# This Makefile is a part of the genfib set intersection application.
# For full copyright and license information, please view the LICENSE file
# which should be distributed with this source code.
#
# @license MIT License
# @copyright Copyright (c) 2013, Steven Velozo
###

bin_PROGRAMS = genfib
genfib_SOURCES = mathoperations.h main.c intersect.c iterate.c statistics.c
genfib_CPPFLAGS = -I$(top_srcdir)/common -I$(top_srcdir)/rendering
genfib_LDADD = ../common/libdigmathcommon.a ../rendering/libdigmathrender.a ../lib/libgmp.a /usr/local/Cellar/libpng/1.6.10/lib/libpng.a
genfib_LDFLAGS = -Wl,-no_pie,-lz

check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './genfib 5 | grep "5"' > greptest.sh
	chmod +x greptest.sh

CLEANFILES = greptest.sh
