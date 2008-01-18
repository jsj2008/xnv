###############################################################################
#
# Xi 1.x Makefile
#
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use subject to license terms.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, and/or sell copies of the Software, and to permit persons
# to whom the Software is furnished to do so, provided that the above
# copyright notice(s) and this permission notice appear in all copies of
# the Software and that both the above copyright notice(s) and this
# permission notice appear in supporting documentation.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
# OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
# INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
# 
# Except as contained in this notice, the name of a copyright holder
# shall not be used in advertising or otherwise to promote the sale, use
# or other dealings in this Software without prior written authorization
# of the copyright holder.
#
# @(#)Makefile	1.1	07/12/11
#

# Package name used in tarballs
LIB_MODULE=libXi

# Version number (used in path names)
LIB_VERS=1.1.3

# Patches to apply to source after unpacking, in order
SOURCE_PATCHES = 6649171.patch

# Library name (used for specfiles/mapfiles)
LIBNAME=Xi

# Man pages to apply Sun footer to & attributes to list
SUNTOUCHED_MANPAGES=man/*.man
SUN_PACKAGE=SUNWxwplt
LIB_STABILITY=Committed
LIB_MAN_SUFFIX=3Xi

# Library built in tree
LIB_BUILT=$(SOURCE_DIR)/src/.libs/libXi.so.5.0.0

# Use specfile to make mapfile & link with it
LIB_ADD_BUILD_DEPS = $(BUILD_DIR)/$(SPECMAP)
LIB_ADD_LD_OPTIONS = -M $(PWD)/$(BUILD_DIR)/$(SPECMAP)

# pkg-config files that need to have -R added
FIX_PC_FILES=xi.pc.in

include ../Makefile.inc