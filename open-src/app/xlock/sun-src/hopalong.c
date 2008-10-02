/*
 * Copyright (c) 1988-91 by Patrick J. Naughton.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 */

/*
 * Copyright 1994 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
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

#ifndef lint
static char sccsid[] = "@(#)hopalong.c	35.3 08/09/18 XLOCK";
#endif
/*-
 * hopalong.c - Real Plane Fractals for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 29-Oct-90: fix bad (int) cast.
 * 29-Jul-90: support for multiple screens.
 * 08-Jul-90: new timing and colors and new algorithm for fractals.
 * 15-Dec-89: Fix for proper skipping of {White,Black}Pixel() in colors.
 * 08-Oct-89: Fixed long standing typo bug in RandomInitHop();
 *	      Fixed bug in memory allocation in inithop();
 *	      Moved seconds() to an extern.
 *	      Got rid of the % mod since .mod is slow on a sparc.
 * 20-Sep-89: Lint.
 * 31-Aug-88: Forked from xlock.c for modularity.
 * 23-Mar-88: Coded HOPALONG routines from Scientific American Sept. 86 p. 14.
 */

#include "xlock.h"
#include <math.h>

typedef struct {
    int         centerx;
    int         centery;	/* center of the screen */
    double      a;
    double      b;
    double      c;
    double      i;
    double      j;		/* hopalong parameters */
    int         inc;
    int         pix;
    long        startTime;
}           hopstruct;

extern XColor ssblack[];
extern XColor sswhite[];

static hopstruct hops[MAXSCREENS];
static XPoint *pointBuffer = 0;	/* pointer for XDrawPoints */

#define TIMEOUT 30

void
inithop(win)
    Window      win;
{
    double      range;
    XWindowAttributes xgwa;
    hopstruct  *hp = &hops[screen];


    XGetWindowAttributes(dsp, win, &xgwa);
    hp->centerx = xgwa.width / 2;
    hp->centery = xgwa.height / 2;
    range = sqrt((double) hp->centerx * hp->centerx +
		 (double) hp->centery * hp->centery) /
	(10.0 + random() % 10);

    hp->pix = 0;
    hp->inc = (int) ((random() / MAXRAND) * 200) - 100;
    hp->a = (random() / MAXRAND) * range - range / 2.0;
    hp->b = (random() / MAXRAND) * range - range / 2.0;
    hp->c = (random() / MAXRAND) * range - range / 2.0;
    if (!(random() % 2))
	hp->c = 0.0;

    hp->i = hp->j = 0.0;

    if (!pointBuffer)
	pointBuffer = (XPoint *) malloc(batchcount * sizeof(XPoint));

    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0,
		   hp->centerx * 2, hp->centery * 2);
    XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);
    hp->startTime = seconds();
}


void
drawhop(win)
    Window      win;
{
    double      oldj;
    int         k = batchcount;
    XPoint     *xp = pointBuffer;
    hopstruct  *hp = &hops[screen];

    hp->inc++;
    if (!mono && Scr[screen].npixels > 2) {
	XSetForeground(dsp, Scr[screen].gc, Scr[screen].pixels[hp->pix]);
	if (++hp->pix >= Scr[screen].npixels)
	    hp->pix = 0;
    }
    while (k--) {
	oldj = hp->j;
	hp->j = hp->a - hp->i;
	hp->i = oldj + (hp->i < 0
			? sqrt(fabs(hp->b * (hp->i + hp->inc) - hp->c))
			: -sqrt(fabs(hp->b * (hp->i + hp->inc) - hp->c)));
	xp->x = hp->centerx + (int) (hp->i + hp->j);
	xp->y = hp->centery - (int) (hp->i - hp->j);
	xp++;
    }
    XDrawPoints(dsp, win, Scr[screen].gc,
		pointBuffer, batchcount, CoordModeOrigin);
    if (seconds() - hp->startTime > TIMEOUT)
	inithop(win);
}