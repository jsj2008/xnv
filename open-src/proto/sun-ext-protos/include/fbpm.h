/*
 * Copyright (c) 1999-2000 by Sun Microsystems, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder
 * shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization
 * of the copyright holder.
 */

#pragma ident   "@(#)fbpm.h	1.10	06/08/09 SMI"

#define FBPMModeOn	0
#define FBPMModeStandby	1
#define FBPMModeSuspend	2
#define FBPMModeOff	3

#define DDXStatError 0
#define DDXStatFbOk  1
#define DDXStatMonOk 2
#define DDXStatOk	(DDXStatFbOk | DDXStatMonOk)

#ifndef DPMS_SERVER

Bool FBPMQueryExtension(
#if NeedFunctionPrototypes
Display *, 
int *, 
int *
#endif
);
Status FBPMGetVersion(
#if NeedFunctionPrototypes
Display *, 
int *, 
int *
#endif
);
Bool FBPMCapable(
#if NeedFunctionPrototypes
Display *
#endif
);
Bool FBPMEnable(
#if NeedFunctionPrototypes
Display *, 
int
#endif
);
Status FBPMDisable(
#if NeedFunctionPrototypes
Display *
#endif
);
Status FBPMForceLevel(
#if NeedFunctionPrototypes
Display *, 
CARD16
#endif
);
Status FBPMInfo(
#if NeedFunctionPrototypes
Display *, 
CARD16 *, 
BOOL *
#endif
);

#endif