/*
* Copyright 1990 Sun Microsystems, Inc.  All rights reserved.
* Use subject to license terms.
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
*
*/

#ifndef lint
static char sccsid[] = "@(#)cmcdiscard.c 35.3 08/09/30";
#endif


#include <sys/fcntl.h>
#include <X11/Xlib.h>
#include "cmc.h"
#include "cmcutil.h"


/*
** Removes the file containing the shared workspace colors,
** if it exists.
*/

void
cmc_discard ()

{
	char	*filename = comp_colors_filename(basename);	

	if (unlink(filename) < 0)
		fatal_error("cannot remove file '%s'", filename);
}
