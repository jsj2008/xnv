###############################################################################
#
# xtrans 1.x Makefile
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
# @(#)Makefile	1.3	07/01/31
#

# IMPORTANT NOTE:  xtrans is not really a library, but shared source code
# compiled into other modules at build time.

PWD:sh=pwd
TOP=$(PWD)/../..
BUILD_TYPES=32 

# Version number (used in path names)
XTRANS_VERS=1.0.3

# Source tarball
SOURCE_TARBALL_NAME=xtrans-$(XTRANS_VERS).tar.bz2

# Download site for source
SOURCE_URL=$(XORG_RELEASES_URL)/lib/$(SOURCE_TARBALL_NAME)

# Patches to apply to source after unpacking, in order
SOURCE_PATCHES = inetv6.patch socket-perm.patch

# Directory created by unpacking source
SOURCE_DIR=$(BUILD_DIR)/xtrans-$(XTRANS_VERS)

# Library name (used for specfiles/mapfiles)
LIBNAME=xtrans

# Man pages to apply Sun footer to & attributes to list
# - Xtrans has none

include $(TOP)/common/Makefile.inc

# Where to install files
XTRANS_prefix=$(X11_DIR)

# Command line options to GNU autoconf configure script
CONFIG_OPTS = --enable-shared=yes --enable-static=no \
	--prefix=$(XTRANS_prefix) --libdir='$${exec_prefix}/lib$(LIBSUBDIR)' \
	--enable-xthreads --with-lint --enable-lint-library

# Environment variable options to GNU autoconf configure script
CONFIG_ENV = CC=$(CC) CFLAGS="$(LIB_CFLAGS)" \
	LD="$(LD) $(LDFLAGS)"  LDFLAGS="$(LIB_LDFLAGS)" \
	PKG_CONFIG_PATH=$(PROTODIR)/usr/lib/$(ARCHLIBSUBDIR)/pkgconfig \
	LIB_MAN_SUFFIX=3xtrans

# Run configure script
$(SOURCE_DIR)/Makefile: $(UNPACK_TARGET) $(XPROTO_DEP)
	(cd $(SOURCE_DIR) ; chmod a+x configure ; \
	 $(CONFIG_ENV) ./configure $(CONFIG_OPTS) )

# Library built in tree
# - Xtrans doesn't build a library, so we use the pkgconfig file it builds instead
XTRANS_LIB = xtrans.pc

build_gen: $(XTRANS_LIB)

$(XTRANS_LIB): $(SOURCE_DIR)/Makefile
	(cd $(SOURCE_DIR) ; LD_OPTIONS="$(LIB_REQUIRED_LDFLAGS) -M $(PWD)/$(BUILD_DIR)/$(SPECMAP)" $(MAKE) $(MFLAGS) )


install_gen: $(XTRANS_LIB)
	(cd $(SOURCE_DIR) ; $(LIBPATHS) LD_OPTIONS="$(LIB_REQUIRED_LDFLAGS)" $(MAKE) $(MFLAGS) -e DESTDIR=$(PROTODIR) libdir=$(XTRANS_prefix)/lib$(ARCHLIBSUBDIR) install pkgconfigdir=/usr/lib/$(ARCHLIBSUBDIR)/pkgconfig)
	-rm -f $(PROTODIR)/usr/lib/$(MACH64)/pkgconfig/xtrans.pc
	ln -s ../../pkgconfig/xtrans.pc $(PROTODIR)/usr/lib/$(MACH64)/pkgconfig/xtrans.pc