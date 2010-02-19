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
/*-
 * swarm.c - swarm of bees for xlock, the X Window System lockscreen.
 *
 * Copyright (c) 1991 by Patrick J. Naughton.
 *
 * Revision History:
 * 31-Aug-90: Adapted from xswarm by Jeff Butterworth. (butterwo@ncsc.org)
 */

#include "xlock.h"

#define TIMES	4		/* number of time positions recorded */
#define BEEACC	3		/* acceleration of bees */
#define WASPACC 5		/* maximum acceleration of wasp */
#define BEEVEL	11		/* maximum bee velocity */
#define WASPVEL 12		/* maximum wasp velocity */
#define BORDER	50		/* wasp won't go closer than this to the edge */

/* Macros */
#define X(t,b)	(sp->x[(t)*sp->beecount+(b)])
#define Y(t,b)	(sp->y[(t)*sp->beecount+(b)])
#define RAND(v)	((random()%(v))-((v)/2))	/* random number around 0 */

typedef struct {
    int         pix;
    long        startTime;
    int         width;
    int         height;
    int         beecount;	/* number of bees */
    XSegment   *segs;		/* bee lines */
    XSegment   *old_segs;	/* old bee lines */
    short      *x;
    short      *y;		/* bee positions x[time][bee#] */
    short      *xv;
    short      *yv;		/* bee velocities xv[bee#] */
    short       wx[3];
    short       wy[3];
    short       wxv;
    short       wyv;
}           swarmstruct;

extern XColor ssblack[];
extern XColor sswhite[];

static swarmstruct swarms[MAXSCREENS];

void
initswarm(win)
    Window      win;
{
    XWindowAttributes xgwa;
    swarmstruct *sp = &swarms[screen];
    int         b;

    sp->startTime = seconds();
    sp->beecount = batchcount;

    XGetWindowAttributes(dsp, win, &xgwa);
    sp->width = xgwa.width;
    sp->height = xgwa.height;

    /* Clear the background. */
    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XFillRectangle(dsp, win, Scr[screen].gc, 0, 0, sp->width, sp->height);

    /* Allocate memory. */

    if (!sp->segs) {
	sp->segs = (XSegment *) malloc(sizeof(XSegment) * sp->beecount);
	sp->old_segs = (XSegment *) malloc(sizeof(XSegment) * sp->beecount);
	sp->x = (short *) malloc(sizeof(short) * sp->beecount * TIMES);
	sp->y = (short *) malloc(sizeof(short) * sp->beecount * TIMES);
	sp->xv = (short *) malloc(sizeof(short) * sp->beecount);
	sp->yv = (short *) malloc(sizeof(short) * sp->beecount);
    }
    /* Initialize point positions, velocities, etc. */

    /* wasp */
    sp->wx[0] = BORDER + random() % (sp->width - 2 * BORDER);
    sp->wy[0] = BORDER + random() % (sp->height - 2 * BORDER);
    sp->wx[1] = sp->wx[0];
    sp->wy[1] = sp->wy[0];
    sp->wxv = 0;
    sp->wyv = 0;

    /* bees */
    for (b = 0; b < sp->beecount; b++) {
	X(0, b) = random() % sp->width;
	X(1, b) = X(0, b);
	Y(0, b) = random() % sp->height;
	Y(1, b) = Y(0, b);
	sp->xv[b] = RAND(7);
	sp->yv[b] = RAND(7);
    }
}



void
drawswarm(win)
    Window      win;
{
    swarmstruct *sp = &swarms[screen];
    int         b;

    /* <=- Wasp -=> */
    /* Age the arrays. */
    sp->wx[2] = sp->wx[1];
    sp->wx[1] = sp->wx[0];
    sp->wy[2] = sp->wy[1];
    sp->wy[1] = sp->wy[0];
    /* Accelerate */
    sp->wxv += RAND(WASPACC);
    sp->wyv += RAND(WASPACC);

    /* Speed Limit Checks */
    if (sp->wxv > WASPVEL)
	sp->wxv = WASPVEL;
    if (sp->wxv < -WASPVEL)
	sp->wxv = -WASPVEL;
    if (sp->wyv > WASPVEL)
	sp->wyv = WASPVEL;
    if (sp->wyv < -WASPVEL)
	sp->wyv = -WASPVEL;

    /* Move */
    sp->wx[0] = sp->wx[1] + sp->wxv;
    sp->wy[0] = sp->wy[1] + sp->wyv;

    /* Bounce Checks */
    if ((sp->wx[0] < BORDER) || (sp->wx[0] > sp->width - BORDER - 1)) {
	sp->wxv = -sp->wxv;
	sp->wx[0] += sp->wxv;
    }
    if ((sp->wy[0] < BORDER) || (sp->wy[0] > sp->height - BORDER - 1)) {
	sp->wyv = -sp->wyv;
	sp->wy[0] += sp->wyv;
    }
    /* Don't let things settle down. */
    sp->xv[random() % sp->beecount] += RAND(3);
    sp->yv[random() % sp->beecount] += RAND(3);

    /* <=- Bees -=> */
    for (b = 0; b < sp->beecount; b++) {
	int         distance,
	            dx,
	            dy;
	/* Age the arrays. */
	X(2, b) = X(1, b);
	X(1, b) = X(0, b);
	Y(2, b) = Y(1, b);
	Y(1, b) = Y(0, b);

	/* Accelerate */
	dx = sp->wx[1] - X(1, b);
	dy = sp->wy[1] - Y(1, b);
	distance = abs(dx) + abs(dy);	/* approximation */
	if (distance == 0)
	    distance = 1;
	sp->xv[b] += (dx * BEEACC) / distance;
	sp->yv[b] += (dy * BEEACC) / distance;

	/* Speed Limit Checks */
	if (sp->xv[b] > BEEVEL)
	    sp->xv[b] = BEEVEL;
	if (sp->xv[b] < -BEEVEL)
	    sp->xv[b] = -BEEVEL;
	if (sp->yv[b] > BEEVEL)
	    sp->yv[b] = BEEVEL;
	if (sp->yv[b] < -BEEVEL)
	    sp->yv[b] = -BEEVEL;

	/* Move */
	X(0, b) = X(1, b) + sp->xv[b];
	Y(0, b) = Y(1, b) + sp->yv[b];

	/* Fill the segment lists. */
	sp->segs[b].x1 = X(0, b);
	sp->segs[b].y1 = Y(0, b);
	sp->segs[b].x2 = X(1, b);
	sp->segs[b].y2 = Y(1, b);
	sp->old_segs[b].x1 = X(1, b);
	sp->old_segs[b].y1 = Y(1, b);
	sp->old_segs[b].x2 = X(2, b);
	sp->old_segs[b].y2 = Y(2, b);
    }

    XSetForeground(dsp, Scr[screen].gc, ssblack[screen].pixel);
    XDrawLine(dsp, win, Scr[screen].gc,
	      sp->wx[1], sp->wy[1], sp->wx[2], sp->wy[2]);
    XDrawSegments(dsp, win, Scr[screen].gc, sp->old_segs, sp->beecount);

    XSetForeground(dsp, Scr[screen].gc, sswhite[screen].pixel);
    XDrawLine(dsp, win, Scr[screen].gc,
	      sp->wx[0], sp->wy[0], sp->wx[1], sp->wy[1]);
    if (!mono && Scr[screen].npixels > 2) {
	XSetForeground(dsp, Scr[screen].gc, Scr[screen].pixels[sp->pix]);
	if (++sp->pix >= Scr[screen].npixels)
	    sp->pix = 0;
    }
    XDrawSegments(dsp, win, Scr[screen].gc, sp->segs, sp->beecount);
}
