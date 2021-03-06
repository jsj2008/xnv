###############################################################################
#
# xdm Makefile
#
# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

# Package name used in tarballs
MODULE_NAME=xdm

# pkg(5) name we deliver the files in (override default)
MODULE_PKGNAME=system/display-manager/xdm
MODULE_PKGNAME_SET=yes

# Version number (used in path names)
MODULE_VERSION=1.1.9

# Checksums for upstream tarball
TARBALL_MD5  = 030ae4bd9b8d428749d68bfdf56ce8a5
TARBALL_SHA1 = ea0ee2923999d54848dc8a165867ffa7c628fd7b

# Patches to apply to source after unpacking, in order
SOURCE_PATCHES = \
	mkdir.patch,-p1 \
	pam_tty.patch,-p1 \
	pam_user.patch,-p1 \
	bindir.patch,-p1 \
	terminateServer.patch \
	bug-6822636.patch \
	bug-6820612.patch,-p1 \
	Xsession.patch

# Need to rebuild configure/Makefile.in after applying bindir.patch
AUTORECONF=yes

# Man pages to apply Sun footer to & attributes to list
SUNTOUCHED_MANPAGES=xdm.man.cpp
MODULE_STABILITY=Committed
MODULE_SUNTOUCH_MAN_FLAGS= -p $(MODULE_PREFIX)/sbin/

# Where to install xdm files
MODULE_PREFIX=/usr
MODULE_PREFIX_SET=yes

# Additional configure script options
# Only build shared greeter module, not static
# Set various paths to better match Solaris
# Find xrdb & xterm in /usr/bin even with --bindir set to /usr/sbin
MODULE_CONFIG_OPTS= \
	--enable-shared=yes --enable-static=no \
	--with-xdmconfigdir=/etc/X11/xdm \
	--with-piddir=/var/run/xdm \
	--with-authdir=/var/run/xdm \
	--bindir=/usr/sbin \
	--with-xrdb='$(X11_BIN_DIR)/xrdb' \
	--with-default-session=command='$(X11_BIN_DIR)/xterm -ls' \
	DEF_SERVER='$(X11_BIN_DIR)/X' \
	DEF_USER_PATH=/usr/bin:/usr/sbin \
	DEF_SYSTEM_PATH=/usr/bin:/usr/sbin

# configure scripts add libraries like -lXt & -lXinerama to the global $(LIBS)
# when only some objects need them, so ignore them in the rest.
MODTYPE_LD_OPTIONS = -z ignore

# Additional build & install targets
MODULE_ADD_BUILD_TARGETS=build_xdm_configs
MODULE_ADD_INSTALL_TARGETS=install_xdmshell install_xdm_configs

# Need to fix libtool interference with our linker flags
DELIBTOOLIZE=yes

include ../Makefile.inc

# Move xdmshell from default location to the place we put in our packages
install_xdmshell: default_install
	-rm -f $(PROTODIR)/usr/lib/X11/xdm/xdmshell
	mv $(PROTODIR)/usr/sbin/xdmshell $(PROTODIR)/usr/lib/X11/xdm/xdmshell

# Copy xdm config files from /etc to /usr for use as prototypes
XDM_CONFIG_FILES=Xaccess Xresources Xservers xdm-config
XDM_ETC_CONFIGDIR=/etc/X11/xdm
XDM_USR_CONFIGDIR=/usr/lib/X11/xdm
XCF_USR_FILES=$(XDM_CONFIG_FILES:%=$(PROTODIR)/$(XDM_USR_CONFIGDIR)/%)
XCF_ETC_SRCDIR=$(SOURCE_DIR)/config
XCF_ETC_SRCFILES=$(XDM_CONFIG_FILES:%=$(XCF_ETC_SRCDIR)/%)
XCF_USR_SRCDIR=$(SOURCE_DIR)/config/annotated
XCF_USR_SRCFILES=$(XDM_CONFIG_FILES:%=$(XCF_USR_SRCDIR)/%)

build_xdm_configs: $(XCF_USR_SRCFILES)
install_xdm_configs: $(XCF_USR_FILES) $(PROTODIR)/$(XDM_USR_CONFIGDIR)/README
$(XCF_ETC_SRCFILES): default_build

XCF_HEADER = %1$$s----------------------------------------------------------------------------
XCF_HEADER += \n%1$$s NOTE: The file provided in $(XDM_USR_CONFIGDIR) is a sample %2$$s
XCF_HEADER += \n%1$$s configuration file provided for your reference.
XCF_HEADER += \n%1$$s
XCF_HEADER += \n%1$$s xdm reads the actual configuration from the copies located in $(XDM_ETC_CONFIGDIR)
XCF_HEADER += \n%1$$s (unless configured otherwise by $(XDM_ETC_CONFIGDIR)/xdm-config or
XCF_HEADER += \n%1$$s  a file specified via the -config command line option).
XCF_HEADER += \n%1$$s----------------------------------------------------------------------------\n

$(PROTODIR)/$(XDM_USR_CONFIGDIR) $(XCF_USR_SRCDIR):
	mkdir -p $@

$(XCF_USR_FILES): $(PROTODIR)/$(XDM_USR_CONFIGDIR) $(XCF_USR_SRCFILES)
	-rm -f $@
	mkdir -p $(PROTODIR)/$(XDM_USR_CONFIGDIR)
	cp -p $(XCF_USR_SRCDIR)/$(@F) $@

$(XCF_USR_SRCFILES): $(XCF_USR_SRCDIR) $(XCF_ETC_SRCFILES)
	-rm -f $@
	FILENAME=$(@F) ; \
	COMMENT_CHAR=$$(head -n 1 $(XCF_ETC_SRCDIR)/$${FILENAME}) ; \
	printf '$(XCF_HEADER)' $${COMMENT_CHAR} $${FILENAME} > $@ ; \
	cat $(XCF_ETC_SRCDIR)/$${FILENAME} >> $@

$(PROTODIR)/$(XDM_USR_CONFIGDIR)/README:$(PROTODIR)/$(XDM_USR_CONFIGDIR)  config-README.txt
	cp -p config-README.txt $@
